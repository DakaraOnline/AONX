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
#include "rect.h"

namespace ga
{

	Rect Rect::interseccion( const Rect & r )
	{
		Rect dest(0,0,0,0);
				
		if ( interseca( r ) )
		{
			if ( r._x < _x ) {
				dest._x = _x;
				dest._w = r._x + r._w - _x; 
			} else {
				dest._x = r._x;
				dest._w = _x + _w - r._x;
			}
					
			if ( r._y < _y ) {
				dest._y = _y;
				dest._h = r._y + r._h - _y;
			} else {
				dest._y = r._y;
				dest._h = _y + _h - r._y;
			}
		}
				
		return dest;
	}


}
