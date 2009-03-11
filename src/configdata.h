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
#ifndef CONFIG_H
#define CONFIG_H

#include <string>

/**
	@author alejandro santos <alejolp@alejolp.com>
*/
class ConfigData
{
	
public:
	static void SetBasePath(std::string path);
	static std::string GetStdBasePath();
	static std::string GetPath(std::string dirName);
	static bool Fullscreen;
	static bool Sdl;
	static bool Mute;
	
	static std::string GetTTFontFileName() { 
		return std::string("SansSerif.ttf");
	}
private:
	static std::string BasePath;

	ConfigData();

	~ConfigData();

};

#endif
