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

#include "mensajes.h"
#include "configdata.h"

#include <fstream>
#include <sstream>
#include <list>

std::string Msgs::get(unsigned int n)
{
	if(n<data.size())
		return data[n];
	else
		return std::string("");
}

std::string Msgs::get(unsigned int n, const std::string &params)
{
	if(n>=data.size())
		return std::string("");
	std::string base = data[n];
	std::list<std::string> paramsl;
	std::size_t pos = params.find("|");
	paramsl.push_back(params.substr(0, pos));
	while(pos != std::string::npos)
	{
		std::size_t start_pos = pos + 1;
		pos = params.find("|",start_pos + 1);
		paramsl.push_back(params.substr(start_pos,pos));
	}
	unsigned int actual_param = 1;
	while(!paramsl.empty())
	{
		std::string actual = paramsl.front();
		paramsl.pop_front();
		std::stringstream paramMark;
		paramMark << "&" << actual_param;
		pos = base.find(paramMark.str());
		if(pos!=std::string::npos)
		{
			base.replace(pos,2,actual);//TODO hardcoded 2... puede haber mas de 9 params
		}
		actual_param++;
	}
	return base;
}

void Msgs::cargarDatos()
{
	std::ifstream file((ConfigData::GetPath("init") + std::string("mensajes.txt")).c_str());
	std::string line;
	while(!file.eof())
	{
		std::getline(file,line);
		if(line.size()>0)
		{
			data.push_back(line);
		}
	}
}




