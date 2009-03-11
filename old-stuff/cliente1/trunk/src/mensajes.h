/***************************************************************************
 *   Copyright (C) 2008 by Esteban Torre                                   *
 *   esteban.torre@gmail.com                                               *
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

#ifndef _mensajes_h
#define _mensajes_h

#include <string>
#include <vector>

class Msgs
{
public:
	Msgs(){};
	~Msgs(){};

	std::string get(unsigned int n);
	std::string get(unsigned int n, const std::string &params);

	void cargarDatos();

private:
	std::vector<std::string> data;
};

#endif //#ifndef _mensajes_h
