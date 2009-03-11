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

#include "graphicsadaptersdl.h"
#include "rendererenginesdl.h"

#include "imagemanager.h"
#include "configdata.h"
#include "grhdata.h"
#include "grhmanager.h"

using namespace std;

RendererEngineSDL::RendererEngineSDL()
: RendererEngine()
{
	cout <<"Initializing SDL." << endl;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout <<"Could not initialize SDL: " << SDL_GetError() << endl;
		SDL_Quit();
	}

	int width = 800;
	int height = 600;
	
	//  | SDL_FULLSCREEN
//	_screen = SDL_SetVideoMode( 800, 600, 16, SDL_HWSURFACE | SDL_DOUBLEBUF );
	int flags = SDL_SWSURFACE;
	if(ConfigData::Fullscreen)
		flags|=SDL_FULLSCREEN;

	_screen = SDL_SetVideoMode( width, height, 0, flags );
	if ( ! _screen )
		throw std::exception();

	SDL_EnableUNICODE(1);
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	GuichanLoader_ptr guichan(new GuichanLoader());
	guichan->loadSDL( _screen );

	RendererEngine::initializeGA( ga::GraphicsAdapter_ptr( new ga::GraphicsAdapterSDL ( _screen ) ) );
	RendererEngine::initializeGuichan( guichan );
}


RendererEngineSDL::~RendererEngineSDL()
{
}

void RendererEngineSDL::beginFrame()
{
	// La version SDL dibuja un rectangulo negro en toda la pantalla para 
	// borrar lo anterior.
	RendererEngine::beginFrame();
}
void RendererEngineSDL::endFrame()
{
	RendererEngine::endFrame();
	SDL_Flip(_screen);
}

void RendererEngineSDL::initFont() 
{
	
}

