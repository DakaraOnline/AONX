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
#include <exception>

#include "class_types.h"

#include "graphicsadapterogl.h"
#include "rendererengineogl.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "console.h"

#include "clienteargentum.h"
#include "configdata.h"

// #include "imagemanager.h"
// #include "grhdata.h"
// #include "grhmanager.h"

using namespace std;

RendererEngineOGL::RendererEngineOGL()
	: RendererEngine()
{
	const SDL_VideoInfo* info = NULL;
	int width = 0;
	int height = 0;
	int bpp = 0;
	int flags = 0;
	
	cout <<"Initializing SDL + OpenGL." << endl;
	
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout <<"Could not initialize SDL: " << SDL_GetError() << endl;
		SDL_Quit();
	}
	
	cout << "Obteniendo informacion de video..." << endl;
	info = SDL_GetVideoInfo( );

	if( !info ) {
		/* This should probably never happen. */
		cout << "SDL_GetVideoInfo: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	width = 800;
	height = 600;
	bpp = info->vfmt->BitsPerPixel;

    /*
	* Now, we want to setup our requested
	* window attributes for our OpenGL window.
	* We want *at least* 5 bits of red, green
	* and blue. We also want at least a 16-bit
	* depth buffer.
	*
	* The last thing we do is request a double
	* buffered window. '1' turns on double
	* buffering, '0' turns it off.
	*
	* Note that we do not use SDL_DOUBLEBUF in
	* the flags to SDL_SetVideoMode. That does
	* not affect the GL attribute state, only
	* the standard 2D blitting setup.
    */
	
	cout << "Configurando OpenGL..." << endl;

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
	flags = SDL_HWSURFACE | SDL_OPENGL | SDL_HWACCEL;// | SDL_FULLSCREEN; // | SDL_HWSURFACE | SDL_FULLSCREEN;

	if(ConfigData::Fullscreen)
		flags|=SDL_FULLSCREEN;

	cout << "Iniciando modo de video..." ;

	_screen = SDL_SetVideoMode( width, height, bpp, flags);
	if( ! _screen ) {
		cout << "SDL_SetVideoMode: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	int dummy;
	SDL_GL_GetAttribute( SDL_GL_RED_SIZE, &dummy );
	cout << " red_size: " << dummy << " # OK!" << endl;

	GuichanLoader_ptr guichan(new GuichanLoader());
	guichan->loadOpenGL( width, height );
	
	RendererEngine::initializeGA( ga::GraphicsAdapter_ptr( new ga::GraphicsAdapterOGL ( _screen ) ) );
	RendererEngine::initializeGuichan( guichan );

}


RendererEngineOGL::~RendererEngineOGL()
{
}

void RendererEngineOGL::beginFrame()
{
	RendererEngine::beginFrame();
}

void RendererEngineOGL::endFrame()
{
	RendererEngine::endFrame();
	SDL_GL_SwapBuffers();
}

void RendererEngineOGL::initFont() 
{
	_tr->init_opengl();
}

