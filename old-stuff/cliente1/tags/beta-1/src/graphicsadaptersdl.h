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
#ifndef GAGRAPHICSADAPTERSDL_H
#define GAGRAPHICSADAPTERSDL_H

#include "SDL_image.h"
#include "class_types.h"
#include "graphicsadapter.h"


namespace ga {


	/**
	@brief Adaptador para graficos en SDL
	@author alejandro santos <alejolp@gmail.com>
	 */
	class GraphicsAdapterSDL : public GraphicsAdapter
	{
		public:
			GraphicsAdapterSDL( SDL_Surface* surface, GuichanLoader_ptr _guichan);	
			virtual ~GraphicsAdapterSDL();
	
			virtual void drawPoint( int x, int y, const Color & c );
			virtual void drawLine( int x1, int y1, int x2, int y2, const Color & c );
			virtual void drawRect( const Rect & r, const Color & c );
	
			virtual Image_ptr loadImage(std::string imagePath);
			virtual void drawImage(Image_ptr img, const Rect & src, const Point & dest);
			virtual void drawImage(Image_ptr img, const Point & dest);

			virtual void drawText( gcn::ImageFont* font, const std::string txt, const Point & dest);
			virtual void drawText( const std::wstring txt, const Point & dest);

			virtual void beginFrame();
			virtual void endFrame();

			// /////////////////////////
			// Privado del Adaptador SDL

			/// Convierte un Color al formato de color de la Surface SDL
			static Uint32 MapColor( SDL_Surface * surface, const Color & c ) {
				Uint32 col = SDL_MapRGB( surface->format, c.r, c.g, c.b );
//				std::cout << "col: " << col << std::endl;

				return col;
			}
			
			/// Convierte un Color al formato de color de la Surface SDL
			Uint32 MapColor( const Color & c ) {
				return MapColor( _surface, c );
			}
			
			
		private:
		
			SDL_Surface* _surface;
			GuichanLoader_ptr guichan;
	};
	
}

#endif
