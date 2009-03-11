/***************************************************************************
 *   Copyright (C) 2007 by alejandro santos                                *
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
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

#include "inifile.h"

std::string left_trim( const std::string & str )
{
	std::string::size_type pos1 = str.find_first_not_of(' ');
	return ( pos1 == std::string::npos ) ? str : str.substr( pos1 );
}

std::string trim( const std::string & str )
{
	std::string::size_type pos1 = str.find_first_not_of(' ');
	std::string::size_type pos2 = str.find_last_not_of(' ');
	return str.substr(pos1 == std::string::npos ? 0 : pos1, 
			 pos2 == std::string::npos ? str.length() - 1 : pos2 - pos1 + 1);
}

void to_lower( std::string & str )
{
	std::transform(str.begin(), str.end(), str.begin(),
		       (int(*)(int)) std::tolower);
}

IniFile::IniFile( std::string fileName, bool lowerCase )
	: _fileName( fileName ), _lowerCase( lowerCase )
{
	std::ifstream in;
	bool run = true;
	
	in.exceptions( std::ios::eofbit | std::ios::failbit | std::ios::badbit );
	in.open( fileName.c_str(), std::ios::in );
	
	std::string cur_sec;
	
	while (run)
	{
		std::string all_line, data;
		
		try
		{
			std::getline(in, all_line);
			if ( in.eof() )
				run = false;
		}
		catch(...)
		{
			run = false;
		}
		
		data = left_trim(all_line);
				
		if ( data.length() < 2 )
		{
			continue;
		}
		else if ( data[0] == ';' || data[0] == '#' )
		{
			continue;
		}
		else if ( data[0] == '[' )
		{
			size_t cerrar_pos = data.find_first_of( ']' );
			
			if (cerrar_pos != std::string::npos)
				cur_sec = data.substr( 1, cerrar_pos - 1 );
		}
		else if ( cur_sec.length() > 0 )
		{
			size_t igual_pos = data.find_first_of( '=' );
			
			if ( igual_pos != std::string::npos )
			{
				asignar( cur_sec, 
					 data.substr( 0, igual_pos ), 
					 left_trim( data.substr( igual_pos + 1 ) ) );
			}
		}
	}

}

IniFile::~IniFile()
{
}

void IniFile::asignar( std::string sec, std::string key, std::string valor )
{
	if ( _lowerCase )
	{
		to_lower( sec );
		to_lower( key );
	}
	
	std::pair<mapa_sec_keys::iterator, bool> i = 
			_data.insert( mapa_sec_keys::value_type( sec, mapa_key_val() ) );
	
	i.first->second[key] = valor;
}



