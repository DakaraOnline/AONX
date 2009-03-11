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
#include "configdata.h"

#include <sstream>
#include <stdlib.h>

std::string ConfigData::BasePath;
bool ConfigData::Fullscreen = false;
bool ConfigData::Sdl = false;
bool ConfigData::Mute = false;

ConfigData::ConfigData()
{
}


ConfigData::~ConfigData()
{
}

void ConfigData::SetBasePath(std::string path)
{
	BasePath = path;
	
	if (BasePath.size() > 0) {
#ifdef WIN32
		char sep = '\\';
#else
		char sep = '/';
#endif
		if (BasePath[BasePath.size()-1] == sep)
			BasePath = BasePath.substr(0, BasePath.size()-1);
	}
}

std::string ConfigData::GetStdBasePath()
{
	if (BasePath.length() > 0) {
		return BasePath;
	} else {
#ifdef WIN32
		return std::string("..");
#else
		return std::string(getenv("HOME"));
#endif
	}
}

std::string ConfigData::GetPath(std::string dirName)
{
	std::stringstream strPath;
#ifdef WIN32
	strPath << GetStdBasePath() << "\\" << dirName << "\\";
	return strPath.str();
#else
	strPath << GetStdBasePath() << "/aonx-data/" << dirName << "/";
	return strPath.str();
#endif
}

