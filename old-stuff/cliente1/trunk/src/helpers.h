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
#ifndef _helpers_h
#define _helpers_h
#include "SDL.h"
#include <string>

int GetRandomNumber(int min, int max);
bool ValidateAlpha(const char* what);//WARNING what SHOULD BE A NULL ENDED STRING
bool ValidateAlphaNum(const char* what);//WARNING what SHOULD BE A NULL ENDED STRING
bool ValidateCommon(const char* what);//WARNING what SHOULD BE A NULL ENDED STRING

int to_number(const std::string &s);
std::string to_string(int n);

#endif
