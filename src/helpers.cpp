/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre   *
 *   esteban.torre@gmail.com   *
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

#include "helpers.h"

#include <cstdlib>
#include <cstring>
#include <sstream>

int GetRandomNumber(int min, int max)
{
	if(max>min)
	{
		int temp = max;
		max = min;
		min = temp;
	}else if(max==min){
		return max;
	}
	unsigned int random = rand();
	random = (unsigned int)((random/(RAND_MAX*1.0))*(max-min));
	random += min;
	return random;
}


bool ValidateAlpha(const char* what)
{
	unsigned int a = strlen(what);
	for(unsigned int i=0;i<a; i++)
	{
		char c = what[i];
		if((c!=' ')&&((c<'A')||((c>'Z')&&(c<'a'))||(c>'z')))
		{
			return false;
		}
	}
	return true;
}

bool ValidateAlphaNum(const char* what)
{
	unsigned int a = strlen(what);
	for(unsigned int i=0;i<a; i++)
	{
		char c = what[i];
		if((c!=' ')&&((c<'0')||((c>'9')&&(c<'A'))||((c>'Z')&&(c<'a'))||(c>'z')))
		{
			return false;
		}
	}
	return true;
}

bool ValidateCommon(const char* what)
{
	unsigned int a = strlen(what);
	for(unsigned int i=0;i<a; i++)
	{
		char c = what[i];
		//TODO hacer un acl de caracteres esto apesta xD
		if((c!='.') && (c!='-') && (c!='_') && (c!='@') && (c!=' ')&&((c<'0')||((c>'9')&&(c<'A'))||((c>'Z')&&(c<'a'))||(c>'z')))
		{
			return false;
		}
	}
	return true;
}


int to_number(const std::string &s)
{
	std::stringstream ss;
	ss << s;
	int ret;
	ss >> ret;
	return ret;
}

std::string to_string(int n)
{
	std::stringstream ss;
	ss << n;
	return ss.str();
}


