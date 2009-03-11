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
#ifndef RENDERERENGINESDL_H
#define RENDERERENGINESDL_H

#include "rendererengine.h"

#include "SDL.h"



/**
	@author alejandro santos <alejolp@gmail.com>
*/
class RendererEngineSDL : public RendererEngine
{
public:
	RendererEngineSDL();

	virtual ~RendererEngineSDL();

	// virtual void render( int incX, int incY );
	virtual void beginFrame();
	virtual void endFrame();
		
protected:
	
	virtual void initFont();
	
	SDL_Surface* _screen;
	
};


#endif

