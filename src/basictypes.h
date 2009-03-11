/***************************************************************************
 *   Copyright (C) 2007 by Alejandro Santos                                *
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

#ifndef AOBASICTYPES_H
#define AOBASICTYPES_H

#include "SDL.h"

namespace ao 
{
/**
	@brief Representa una coordenada en un mapa
	@author alejandro santos <alejolp@gmail.com>
 */
	class Pos
	{
	public:
		Pos( Uint16 xx = 0, Uint16 yy = 0 )
			: x(xx), y(yy)
		{}
				
		Uint16 x, y;
	};

};

class Offset
{
public:
	Offset( int xx = 0, int yy = 0) 
		: x(xx), y(yy)
	{}
	
	Offset operator+(const Offset & o) const {
		return Offset( x + o.x, y + o.y );
	}
	
	int x;
	int y;
};


#endif

