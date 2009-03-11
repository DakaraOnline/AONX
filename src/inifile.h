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
#ifndef INIFILE_H
#define INIFILE_H

#include <string>
#include <map>

/**
	@author alejandro santos <alejolp@gmail.com>
*/
class IniFile
{
public:
	typedef std::map<std::string, std::string> mapa_key_val;
	typedef std::map<std::string, mapa_key_val > mapa_sec_keys;
	
	class Seccion
	{
	public:
		Seccion( mapa_key_val * kv )
			: _kv( kv )
		{}
		
		std::string operator[]( std::string key ) {
			return (*_kv)[key];
		}
		
	private:
		mapa_key_val * _kv;
	};
	
	IniFile( std::string fileName, bool lowerCase = false );

	~IniFile();

	Seccion operator[]( std::string sec ) {
		return Seccion( & _data[sec] );
	}
	
private:
	
	void asignar( std::string sec, std::string key, std::string valor );
	
	mapa_sec_keys _data;
	std::string _fileName;
	bool _lowerCase;
};

#endif
