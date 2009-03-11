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
#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <map>
#include <vector>
#include <list>
#include <queue>
#include <SDL.h>




/**
 * @author alejandro santos <alejolp@gmail.com>
 */
class ImageManager
{
public:
	ImageManager( ga::GraphicsAdapter_ptr graphic );

	~ImageManager();

	/// Dado un ID de imagen, devuelve la imagen
	ga::Image* getImage( Uint32 num);
	
protected:
	
	class ImageMetaData 
	{
	public:
		ImageMetaData()
			: mark(false)
		{
		}
		
		void init()
		{
			// TODO: Inicializar las estadisticas !
			mark = false;
		}
		
		inline void hit() 
		{
			// TODO: Informacion estadistica de imagenes !
			mark = true;
		}
		
		bool mark;
		ga::Image_ptr img;
	};
	
	/// La uso para guardar el historial en el que se crearon imagenes
	std::queue<int> _history;
	
	/// Vector para guardar las imagenes
	std::vector<ImageMetaData> _imgs;
	
	/// La fabrica de imagenes
	ga::GraphicsAdapter_ptr _graphic;
};

#endif
