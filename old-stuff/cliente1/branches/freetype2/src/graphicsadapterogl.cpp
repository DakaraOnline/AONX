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
#include <string>



#include <SDL.h>
#include <SDL_image.h>

#include "graphicsadapterogl.h"
#include "helpers_graphics.h"

using namespace std;

namespace ga
{
	
	/**
	@author alejandro santos <alejolp@gmail.com>
	 */
	class ImageOGL : public Image
	{
	public:
		ImageOGL();
		virtual ~ImageOGL();
	
		virtual void setColorKey( const Color & c, bool active = true );
	
		virtual void setAlpha( unsigned int alpha, bool active = true );
		
		/**
			* Optimiza la imagen para que se dibuje mas rapido en la pantalla. Antes de llamar
			* a esta funcion, si es que se desea, es conveniente llamar a setColorKey y setAlpha.
		*/
		virtual void displayFormat();
	
		/**
		 * Carga la textura desde el archivo 
		 */
		void loadImage(std::string path);
		
		/**
		 * Devuelve si la textura es valida
		 */
		bool textureHandleValid() const { return _valid; }
		
		/**
		 * Devuelve el handle de OpenGL de la textura
		 */
		GLuint getTextureHandle() const { return _texture; }
		
		/**
		 * Devuelve las coordenadas reales para dibujar la textura
		 */
		const GLfloat* getTexCoords() const { return _texcoord; }
		
	private:
		void unloadImage();
	
		void checkSurface()
		{
			if ( ! _valid )
				throw GraphicsAdapterException("ImageSDL::checkSurface -> _surface == NULL ! ");
		}
	
		GLuint _texture;
		bool _valid;
		GLfloat _texcoord[4];
	};
	
	ImageOGL::ImageOGL()
	: _texture(0), _valid(false)
	{
	}
	
	ImageOGL::~ImageOGL()
	{
		unloadImage();
	}
	
	void ImageOGL::setColorKey( const Color & c, bool active )
	{
		// TODO: El color key lo toma desde la transparencia de los PNG !
	}
	
	void ImageOGL::setAlpha( unsigned int alpha, bool active )
	{
		// TODO: y aca que meto ?
	}
	
	void ImageOGL::loadImage(std::string path)
	{
		SDL_Surface* tmp;
		
		unloadImage();
		
		tmp = IMG_Load( path.c_str() );
		if ( ! tmp )
		{
			throw GraphicsAdapterException(std::string("ImageOGL::loadImage -> IMG_Load ") +
					std::string(SDL_GetError()) );
		}
		
		_rect = Rect(0, 0, tmp->w, tmp->h);
		
		_texture = SDL_GL_LoadTexture( tmp, _texcoord );
		
		SDL_FreeSurface( tmp );
		
		if ( ! _texture )
		{
			throw GraphicsAdapterException(std::string("ImageOGL::loadImage -> SDL_GL_LoadTexture ") +
					std::string(SDL_GetError()) );
		}

		_valid = true;
	}
	
	void ImageOGL::displayFormat()
	{
		// TODO: la imagen se convierte automaticamente en el formato de
		//       la pantalla cuando se llama a loadImage. Que hago ?
	}
	
	void ImageOGL::unloadImage()
	{
		if ( ! _valid )
			return;
		
		glDeleteTextures(1, & _texture );
		_texture = 0;
		
		_valid = false;
	}
	
	
	
	
	GraphicsAdapterOGL::GraphicsAdapterOGL( SDL_Surface* surface )
			: ga::GraphicsAdapter(), _surface( surface )
	{
		enter2dMode();
	}

	GraphicsAdapterOGL::~GraphicsAdapterOGL()
	{
		leave2dMode();
	}
	
	void GraphicsAdapterOGL::enter2dMode()
	{
		//
		// Extraido del Guichan ^^ 
		//
		
		glPushAttrib(
			     GL_COLOR_BUFFER_BIT |
				GL_CURRENT_BIT |
				GL_DEPTH_BUFFER_BIT |
				GL_ENABLE_BIT |
				GL_FOG_BIT |
				GL_LIGHTING_BIT |
				GL_LINE_BIT |
				GL_POINT_BIT |
				GL_POLYGON_BIT |
				GL_SCISSOR_BIT |
				GL_STENCIL_BUFFER_BIT |
				GL_TEXTURE_BIT |
				GL_TRANSFORM_BIT |
				GL_POINT_BIT |
				GL_LINE_BIT
			    );

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glOrtho(0, _surface->w, _surface->h, 0, -1, 1);

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		glEnable(GL_SCISSOR_TEST);

		glPointSize(1.0);
		glLineWidth(1.0);

		glDisable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}

	void GraphicsAdapterOGL::leave2dMode()
	{
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glPopAttrib();
	}
	
	void GraphicsAdapterOGL::drawPoint( int x, int y, const Color & c )
	{
	}

	void GraphicsAdapterOGL::drawLine( int x1, int y1, int x2, int y2, const Color & c )
	{
	}

	void GraphicsAdapterOGL::drawRect( const Rect & r, const Color & c )
	{
	}

	Image_ptr GraphicsAdapterOGL::loadImage(std::string imagePath)
	{
		ImageOGL* img = 0;
		
		try
		{
			img = new ImageOGL();
			
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

	void GraphicsAdapterOGL::drawImage(Image_ptr img, const Rect & src, const Point & dest, bool ck , unsigned char alpha )
	{
		ImageOGL *imgogl = static_cast<ImageOGL*>(img.get());
		const GLfloat *texcoord = imgogl->getTexCoords();
		GLfloat srccoords[4];
		
		/*
		GLfloat x1 = (GLfloat)src._x;
		GLfloat y1 = (GLfloat)src._y; 
		
		GLfloat x2 = (GLfloat)(src._x + src._w - 1);
		GLfloat y2 = (GLfloat)(src._y + src._h - 1); 
		
		int w = src._w ;
		int h = src._h ;
		
		const Rect& img_r = img->getRect();
		
		GLfloat min_x = (x1 / img_r._w) * texcoord[2];
		GLfloat min_y = (y1 / img_r._h) * texcoord[3];
		
		GLfloat max_x = (x2 / img_r._w) * texcoord[2];
		GLfloat max_y = (y2 / img_r._h) * texcoord[3];
		*/
		const Rect& img_r = img->getRect();
		
		SDL_GL_convertCoords( srccoords, src._x, src._y, src._w, src._h, texcoord, img_r._w, img_r._h );
		
		SDL_GL_drawImageLow( imgogl->getTextureHandle(), srccoords[0], srccoords[1], srccoords[2], srccoords[3], src._w, src._h, dest._x, dest._y, ck, alpha );
	}

	void GraphicsAdapterOGL::drawImage(Image_ptr img, const Point & dest, bool ck , unsigned char alpha)
	{
		ImageOGL *imgogl = static_cast<ImageOGL*>(img.get());
		const GLfloat *texcoord = imgogl->getTexCoords();
		const Rect& img_r = img->getRect();
		
		int w = img_r._w ;
		int h = img_r._h ;
		
		GLfloat min_x = texcoord[0];
		GLfloat min_y = texcoord[1];
		GLfloat max_x = texcoord[2];
		GLfloat max_y = texcoord[3];
		
		SDL_GL_drawImageLow( imgogl->getTextureHandle(), min_x, min_y, max_x, max_y, w, h, dest._x, dest._y, ck, alpha );
	}

	/*
	void GraphicsAdapterOGL::drawImageLow(ImageOGL *imgogl, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, int w, int h, const Point & dest, bool ck , unsigned char alpha)
	{
		glBindTexture( GL_TEXTURE_2D, imgogl->getTextureHandle() );
		glEnable( GL_TEXTURE_2D );
		if(ck)
			glEnable(GL_BLEND);
		glBegin(GL_QUADS);
			if(ck)
				glColor4ub(255,255,255,alpha);
			glTexCoord2f(min_x, min_y);
			glVertex3i(dest._x, dest._y, 0);
			
			glTexCoord2f(min_x, max_y);
			glVertex3i(dest._x, dest._y + h, 0);
			
			glTexCoord2f(max_x, max_y);
			glVertex3i(dest._x + w, dest._y + h, 0);
			
			glTexCoord2f(max_x, min_y);
			glVertex3i(dest._x + w, dest._y, 0);
			
		glEnd();
		glDisable(GL_TEXTURE_2D);
		if(ck)
			glDisable(GL_BLEND);
	}
	*/
	
	void GraphicsAdapterOGL::drawText(TextRenderer_ptr tr, const std::string txt, const Point & dest)
	{
	}
	
	void GraphicsAdapterOGL::drawText(TextRenderer_ptr tr, const std::wstring txt, const Point & dest)
	{
	}


	void GraphicsAdapterOGL::beginFrame()
	{
#if 0
		static float LightAmbient[] = {0.4, 1.0, 1.0, 1.0};
		static float LightDiffuse[] = {0.4, 1.0, 1.0, 1.0};
		static float LightPosition[] = {0.0, 0.0, -0.4, 1.0};
		
		/* Setup The Ambient Light */
		glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );

		/* Setup The Diffuse Light */
		glLightfv( GL_LIGHT1, GL_DIFFUSE, LightDiffuse );

		/* Position The Light */
		glLightfv( GL_LIGHT1, GL_POSITION, LightPosition );

		/* Enable Light One */
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHTING);
		// glEnable(GL_COLOR_MATERIAL);
#endif
	}

	void GraphicsAdapterOGL::endFrame()
	{
	}
	
}


