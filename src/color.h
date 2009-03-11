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

#ifndef GACOLOR_H
#define GACOLOR_H


namespace ga
{

	/**
	* @brief Clase para representar un color, usada en las funciones de %GraphicsAdapter
	*
	 */
	class Color
	{
	public:
		/**
		* en SDL 0xff es 0% transparente, 100% opaco.
		 */
		Color( Uint8 rr, Uint8 gg, Uint8 bb, Uint8 aa = 0xff )
			: r(rr), g(gg), b(bb), a(aa)
		{}

		Uint8 r, g, b, a;
	};
	
}

#endif

