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

#include <string>
#include <sstream>

#include "configdata.h"
#include "class_types.h"

#include "imagemanager.h"
#include "graphicsadapter.h"

ImageManager::ImageManager( ga::GraphicsAdapter_ptr graphic )
	: _graphic( graphic ), _imgs( 300 )
{
}


ImageManager::~ImageManager()
{
}

ga::Image* ImageManager::getImage( Uint32 num )
{
	if ( num >= _imgs.size() )
		_imgs.resize( ( num * 3 ) / 2 + 1 );
	
	if ( _imgs[num].img.get() )
	{
		// Por ahora no se usa _imgs[num].hit();
	}
	else
	{
		std::stringstream imgPath;
		imgPath << ConfigData::GetPath("graficos") << num << ".png";
		
		ga::Image_ptr img = _graphic->loadImage( imgPath.str() );

		_imgs[num].img = img;
		_imgs[num].init();
		
		// Guardo el orden en el que se piden las imagenes para
		// despues eliminar las mas viejas -> Estrategia FIFO
		_history.push( num );
	}
	
	return _imgs[num].img.get();
}
