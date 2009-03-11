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
#ifndef GARECT_H
#define GARECT_H

namespace ga {

	/**
	 * @brief Clase para representar un rectangulo, usada en las funciones de %GraphicsAdapter
	 *
	 */
	class Rect 
	{
		public:
			Rect (int x, int y, int w, int h )
			: _x(x), _y(y), _w(w), _h(h)
			{}
			
			/**
			 * Dado otro Rect devuelve true si los dos rects
			 * intersectan entre si
			 */
			inline bool interseca( const Rect & r )
			{
				if ( r._x + r._w < _x || r._x > _x + _w )
					return false;
				if ( r._y + r._h < _y || r._y > _y + _h )
					return false;
				return true;
			}
			
			/**
			 * devuelve la interseccion entre dos Rects
			 */
			Rect interseccion ( const Rect & r );

			
			int _x, _y, _w, _h;
	};

}

#endif
