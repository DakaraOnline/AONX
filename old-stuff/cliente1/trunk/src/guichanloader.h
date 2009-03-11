/***************************************************************************
 *   Copyright (C) 2007 by alejandro santos                                *
 *   alejolp@gmail.com                                                     *
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
#ifndef GUICHANLOADER_H
#define GUICHANLOADER_H

#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <guichan/opengl.hpp>
#include <guichan/opengl/openglsdlimageloader.hpp>
#include "SDL.h"

/**
	@author alejandro santos <alejolp@gmail.com>
*/
class GuichanLoader
{
public:
	GuichanLoader();
	~GuichanLoader();

	void loadOpenGL( int width, int height );
	
	void pushInput( SDL_Event & event ) {
		input->pushInput( event );
	}
	
	void logic() {
		gui->logic();
	}
	
	void draw() {
		gui->draw();
	}
	gcn::Container* get_top() { return top; }
	gcn::Graphics* graphics;
private:
	void loadTopContainer();
	
	int _width;
	int _height;
	
	gcn::SDLInput* input;
	
	gcn::ImageLoader* imageLoader;
	gcn::ImageFont* font;
	
	gcn::Gui* gui;
	gcn::Container* top;
	
	gcn::Window *window;
};

#endif
