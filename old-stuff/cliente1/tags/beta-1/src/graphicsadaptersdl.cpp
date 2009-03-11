/***************************************************************************
 *   Copyright (C) 2006 by alejandro santos   *
 *   alejolp@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>

#include "graphicsadaptersdl.h"
#include "guichanloader.h"

namespace ga
{

	///////////////
	
	/**
	@author alejandro santos <alejolp@gmail.com>
	 */
	class ImageSDL : public Image
	{
		public:
			ImageSDL();
			virtual ~ImageSDL();
		
		
			virtual void setColorKey( const Color & c, bool active = true );
		
			/** 
			 *
			 * @see SDL_SetAlpha
			 */
			virtual void setAlpha( unsigned int alpha, bool active = true );

		
			void loadImage(std::string path);
		
		/**
			 * Optimiza la imagen para que se dibuje mas rapido en la pantalla. Antes de llamar
			 * a esta funcion, si es que se desea, es conveniente llamar a setColorKey y setAlpha.
		 */
			virtual void displayFormat();
		
		/**
			 * Establece el color de transparencia de la imagen. Para desactivarlo, indicar cero
			 * en el segundo parametro.
			 * @see SDL_SetColorKey
		 */
			void setColorKey( Uint32 color, Uint32 flag = SDL_SRCCOLORKEY );
			
			SDL_Surface* getSDLSurface() { return _surface; }
		
		private:
			void unloadImage();
		
			void checkSurface() 
			{
				if ( ! _surface )
					throw GraphicsAdapterException("ImageSDL::checkSurface -> _surface == NULL ! ");
			}
		
			SDL_Surface* _surface;
	};
	
	ImageSDL::ImageSDL()
	: _surface(0)
	{
	}
	
	ImageSDL::~ImageSDL()
	{
		unloadImage();
	}
	
	void ImageSDL::unloadImage()
	{
		if ( _surface )
		{
			SDL_FreeSurface( _surface );
			_surface = 0;
		}
	}
	
	void ImageSDL::loadImage( std::string path )
	{
		SDL_Surface* tmp;
		
		// Just In Case (TM)
		unloadImage();
		
		tmp = IMG_Load( path.c_str() );
		if ( ! tmp )
			throw GraphicsAdapterException(std::string("ImageSDL::loadImage -> IMG_Load ") +
					std::string(SDL_GetError()) );
		
		_surface = tmp;
		_rect = Rect(0, 0, _surface->w, _surface->h);
		
		displayFormat();
	}
	
	void ImageSDL::displayFormat()
	{
		SDL_Surface* tmp;
		
		// if ...
		checkSurface();
		
		tmp = SDL_DisplayFormat( _surface );
		if ( ! tmp )
			throw GraphicsAdapterException(std::string("ImageSDL::displayFormat -> SDL_DisplayFormat ! ") +
					std::string(SDL_GetError()) );
		
		SDL_FreeSurface(_surface);
		_surface = tmp;
	}
	
	void ImageSDL::setColorKey( Uint32 key, Uint32 flag )
	{
		checkSurface();
		
		if ( SDL_SetColorKey( _surface, flag, key ) < 0 )
			throw GraphicsAdapterException(std::string("ImageSDL::setColorKey -> SDL_SetColorKey ! ") +
					std::string(SDL_GetError()) );
	}
		
	void ImageSDL::setColorKey( const Color & c, bool active )
	{
		if ( active )
			ImageSDL::setColorKey( GraphicsAdapterSDL::MapColor( _surface, c ) );
		else
			ImageSDL::setColorKey( GraphicsAdapterSDL::MapColor( _surface, c ), 0 );
	}
	
	void ImageSDL::setAlpha( unsigned int alpha, bool active )
	{
		Uint32 flag = active ? SDL_SRCALPHA : 0;
		
		checkSurface();
		
		if ( SDL_SetAlpha( _surface, flag, (Uint8) alpha ) < 0 )
			throw GraphicsAdapterException(std::string("ImageSDL::setAlpha -> SDL_SetAlpha ! ") +
					std::string(SDL_GetError()) );
	}
	
	//////////////////////////////////////////////////////////////
	
	/**
	 * Obtiene el color una surface, la cual ya debe estar bloqueada con SDL_LockSurface. 
	 * Solamente las texturas de 32 bits tienen canal alpha.
	 * Funcion extraida del ejemplo del manual de SDL.
	 */
	static inline Uint32 SDL_GetPixelBasic( SDL_Surface * surface, int x, int y )
	{
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to retrieve */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		
		switch(bpp) {
			case 1:
				return *p;
				break;

			case 2:
				return *(Uint16 *)p;
				break;

			case 3:
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
					return p[0] << 16 | p[1] << 8 | p[2];
#else
					return p[0] | p[1] << 8 | p[2] << 16;
#endif
				break;

			case 4:
				return *(Uint32 *)p;
				break;

			default:
				return 0;       /* shouldn't happen, but avoids warnings */
				break;
		}
		
	}
	
	/**
	 * Obtiene el color de un pixel de la surface, la cual ya debe estar bloqueada con SDL_LockSurface. 
	 */
	static inline Color SDL_GetPixel( SDL_Surface * surface, int x, int y )
	{
		Uint8 r, g, b, a;
		SDL_GetRGBA( SDL_GetPixelBasic( surface, x, y), surface->format, &r, &g, &b, &a );
		return Color( r, g, b, a );
	}
	
	static inline void SDL_PutPixel8( Uint8 *p, Uint32 pixel )
	{
		*p = pixel;
	}
	
	static inline void SDL_PutPixel16( Uint8 *p, Uint32 pixel )
	{
		*(Uint16 *)p = pixel;
	}
	
	static inline void SDL_PutPixel24( Uint8 *p, Uint32 pixel )
	{
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN) 
		p[0] = (pixel >> 16) & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = pixel & 0xff;
#else 
		p[0] = pixel & 0xff;
		p[1] = (pixel >> 8) & 0xff;
		p[2] = (pixel >> 16) & 0xff;
#endif
	}
	
	static inline void SDL_PutPixel32( Uint8 *p, Uint32 pixel )
	{
		*(Uint32 *)p = pixel;
	}
	
	/**
	 * Dibuja un pixel en una surface, la cual ya debe estar bloqueada con SDL_LockSurface
	 * Funcion extraida del ejemplo del manual de SDL
	 */
	static inline void SDL_PutPixel( SDL_Surface * surface, int x, int y, const Color & c )
	{
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to set */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		Uint32 pixel;
		
		pixel = GraphicsAdapterSDL::MapColor( surface, c );
		
		switch(bpp) {
			case 1:
				SDL_PutPixel8( p, pixel );
				break;

			case 2:
				SDL_PutPixel16( p, pixel );
				break;

			case 3:
				SDL_PutPixel24( p, pixel );
				break;

			case 4:
				SDL_PutPixel32( p, pixel );
				break;
		}
	}

	static inline void SDL_PutPixelAlphaFast16()
	{
	}
	
	/**
	 * Dibuja un pixel considerando el canal alpha del color. La Surface debe estar bloqueada con SDL_LockSurface.
	 */
	static inline void SDL_PutPixelAlpha( SDL_Surface * surface, int x, int y, const Color & c )
	{
		//
		// Formula:
		//   Value = Value0 * (1.0 - Alpha) + Value1 * Alpha
		// donde:
		//   Alpha[float] esta en el rango [ 0.0 , 1.0 ]
		//
		// Tambien conocida como:
		//   "Quemate La Cabeza (TM)"
		//
		if ( c.a == 255 )
		{
			SDL_PutPixel( surface, x, y, c );
		}
		else if ( c.a == 128 )
		{
			// La version "fast" de Alpha Blending usa mezclas de 50/50 
			// En vez de hacer (valor * 0.5) se hace (valor >> 1)
			
			// TODO SDL_PutPixelAlphaFastNN
		}
		else
		{
			// TODO SDL_PutPixelAlphaNN
		}
	}
	
	static inline void SDL_DrawLine( SDL_Surface * surface, int x, int y, int x2, int y2, const Color & c )
	{
		/*
		* Algoritmo extraido de un libro de graficos 2D/3D que
		* le preste a pablo y nunca mas me devolvio ^^ 
		*
		* Se supone que es un metodo rapido y eficiente de dibujar
		* lineas porque en el loop principal solamente utiliza sumas y
		* utiliza pocas variables que deberian entrar en la cache
		* 
		* TODO: Verificar limites en la imagen: 0,0 <= x,y <= w,h
		*
		*/
		Sint32 dx, dy, long_d, short_d ;
		Sint32 d, add_dh, add_dl ;
		Sint32 inc_xh, inc_yh , inc_x1  , inc_y1 ;
		Sint32 i ;
		Sint32 XI , YI ;
	
		XI = x;
		YI = y;
	
		dx = x2 - x; dy = y2 - y;
		if (dx < 0) {
			dx = -dx; 
			inc_xh = -1; 
			inc_x1 = -1;
		} else {
			inc_xh = 1; 
			inc_x1 = 1;
		}
		
		if (dy < 0) {
			dy = -dy; 
			inc_yh = -1; 
			inc_y1 = -1;
		} else {
			inc_yh = 1; 
			inc_y1 = 1;
		}
	
		if (dx > dy) {
			long_d = dx; 
			short_d = dy; 
			inc_y1 = 0;
		} else {
			long_d = dy; 
			short_d = dx; 
			inc_x1 = 0;
		}
	
		d = 2 * short_d - long_d;
		add_dl = 2 * short_d;
		add_dh = 2 * short_d - 2 * long_d;
	
		if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
	
		for (i = 0; i<=long_d; i++)
		{
			// La funcion verifica si c.a != 0xff
			SDL_PutPixelAlpha( surface, x, y, c );
	
			if (d >= 0)
			{
				x = x + inc_xh;
				y = y + inc_yh;
				d = d + add_dh;
			}
			else
			{
				x = x + inc_x1;
				y = y + inc_y1;
				d = d + add_dl;
			}
		}
	
		if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
	}
	
	//////////////////////////////////////////////////////////////
	
	GraphicsAdapterSDL::GraphicsAdapterSDL( SDL_Surface* surface, GuichanLoader_ptr _guichan )
	: _surface( surface ), guichan( _guichan )
	{}


	GraphicsAdapterSDL::~GraphicsAdapterSDL()
	{}
	
	void GraphicsAdapterSDL::drawPoint( int x, int y, const Color & c )
	{
		if (SDL_MUSTLOCK(_surface)) SDL_LockSurface(_surface);
		
		if ( c.a != 0xff )
		{
			SDL_PutPixelAlpha( _surface, x, y, c );
		}
		else
		{
			SDL_PutPixel( _surface, x, y, c );
		}
		
		if (SDL_MUSTLOCK(_surface)) SDL_UnlockSurface(_surface);
	
	}
	
	void GraphicsAdapterSDL::drawLine( int x, int y, int x2, int y2, const Color & c )
	{
		SDL_DrawLine( _surface, x, y, x2, y2, c );
	}
	
	void GraphicsAdapterSDL::drawRect( const Rect & r, const Color & c )
	{
		SDL_Rect sdl_r;
		Uint32 col = MapColor( c );
		
		// TODO : RECTANGULOS ALPHA !!
		 
		asignar( sdl_r, r );
		
		if ( SDL_FillRect( _surface, & sdl_r, col ) < 0 )
			throw GraphicsAdapterException( std::string("GraphicsAdapterSDL::drawRect -> SDL_FillRect ") +
					std::string(SDL_GetError()) );
	}
	
	Image_ptr GraphicsAdapterSDL::loadImage(std::string imagePath)
	{
		ImageSDL* img = 0;
		try
		{
			img = new ImageSDL();
			
			img->loadImage( imagePath );
			
			return Image_ptr( img );
		}
		catch (...)
		{
			if ( img )
				delete(img);
			throw;
		}
	}
	
	void GraphicsAdapterSDL::drawImage(Image_ptr img, const Rect & src, const Point & dest)
	{
		ImageSDL* imgSdl = static_cast<ImageSDL*> (img.get());
		SDL_Rect src_rect, dst_rect;
		
		/*
		src_rect.x = src._x;
		src_rect.y = src._y;
		src_rect.w = src._w;
		src_rect.h = src._h;
		*/
		
		asignar(src_rect, src);
		
		dst_rect.x = dest._x;
		dst_rect.y = dest._y;
		dst_rect.w = dst_rect.h = 0;
		
		SDL_BlitSurface( imgSdl->getSDLSurface(), & src_rect, _surface, & dst_rect );
	}
	
	void GraphicsAdapterSDL::drawImage(Image_ptr img, const Point & dest)
	{
		// Espero que no acceda a la vtable ! sino es un compilador malo malo (se porta mal)
		GraphicsAdapterSDL::drawImage( img, img->getRect(), dest );
	}

	void GraphicsAdapterSDL::drawText( gcn::ImageFont* font, const std::string txt, const Point & dest)
	{
		guichan->graphics->_beginDraw();//TODO poner begin en el inicio del frame y end respectivamente en el final
		if(font)
		{
			font->drawString(guichan->graphics,txt,dest._x,dest._y);
		}else{
			guichan->graphics->drawText(txt,dest._x,dest._y);
		}
		guichan->graphics->_endDraw();
	}
	
	void GraphicsAdapterSDL::drawText( const std::wstring txt, const Point & dest)
	{
		//Unicaca TODO
	}

	void GraphicsAdapterSDL::beginFrame()
	{
		// GraphicsAdapterSDL::drawRect( Rect( 0, 0, _surface->w, _surface->h ), Color( 0, 0, 0 ) );
	}
	
	void GraphicsAdapterSDL::endFrame()
	{
		// Nada. El SDL_FLip esta en el Renderer
	}
	

}
