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
#ifndef GAGRAPHICSADAPTEROGL_H
#define GAGRAPHICSADAPTEROGL_H

#include "graphicsadapter.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

namespace ga
{
	
	class ImageOGL;

	/**
		@author alejandro santos <alejolp@gmail.com>
	*/
	class GraphicsAdapterOGL : public ga::GraphicsAdapter
	{
	public:
		GraphicsAdapterOGL( SDL_Surface* surface , GuichanLoader_ptr guichan);

		virtual ~GraphicsAdapterOGL();
		
		virtual void drawPoint( int x, int y, const Color & c );
		virtual void drawLine( int x1, int y1, int x2, int y2, const Color & c );
		virtual void drawRect( const Rect & r, const Color & c );
	
		virtual Image_ptr loadImage(std::string imagePath);
		virtual void drawImage(Image_ptr img, const Rect & src, const Point & dest);
		virtual void drawImage(Image_ptr img, const Point & dest);

		virtual void drawText(gcn::ImageFont* font, const std::string txt, const Point & dest);
		virtual void drawText(const std::wstring txt, const Point & dest);

		virtual void beginFrame();
		virtual void endFrame();
		
	private:
		
		void enter2dMode();
		void leave2dMode();
		
		void drawImageLow(ImageOGL *imgogl, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, int w, int h, const Point & dest);
		
	private:
		
		SDL_Surface* _surface;
		GuichanLoader_ptr guichan;
	};

}
#endif
