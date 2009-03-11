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

#ifndef fonts_h
#define fonts_h
#include <guichan.hpp>
#include "configdata.h"
#include <sstream>
#include <string>


class Fonts
{
	public:
		
		static Fonts* instancia(){
			if(_instancia==0){
				_instancia=new Fonts();
			}
			return _instancia;
		}

		Fonts(){}

		~Fonts(){}

		static gcn::ImageFont* sans_12_white()
		{
			if(!_sans_12_white)
			{
				_sans_12_white = new gcn::ImageFont(
					(ConfigData::GetPath("guifonts") + std::string("sans_12_white.png")).c_str(), 
					"abcdefghijklmnopqrstuvwxyz Z"
					"ABCDEFGHIJKLMNOPQRSTUVWXY"
					"|1234567890'ø∞!\"#$%&/()=?°¨@"
					"∑\\¥+{},.-®*[];:_<>~^`·ÈÌÛ˙¡…");//Õ”");
				//	"·ÈÌÛ˙¡…Õ”");
			}
			return _sans_12_white;
		}
		static gcn::ImageFont* sans_12_blue()
		{
			if(!_sans_12_blue)
			{
				_sans_12_blue = new gcn::ImageFont(
					(ConfigData::GetPath("guifonts") + std::string("sans_12_blue.png")).c_str(), 
					"abcdefghijklmnopqrstuvwxyz Z"
					"ABCDEFGHIJKLMNOPQRSTUVWXY"
					"|1234567890'ø∞!\"#$%&/()=?°¨@"
					"∑\\¥+{},.-®*[];:_<>~^`·ÈÌÛ˙¡…");//Õ”");
				//	"·ÈÌÛ˙¡…Õ”");
			}
			return _sans_12_blue;
		}

		static gcn::ImageFont* sans_12_red()
		{
			if(!_sans_12_red)
			{
				_sans_12_red = new gcn::ImageFont(
					(ConfigData::GetPath("guifonts") + std::string("sans_12_red.png")).c_str(), 
					"abcdefghijklmnopqrstuvwxyz Z"
					"ABCDEFGHIJKLMNOPQRSTUVWXY"
					"|1234567890'ø∞!\"#$%&/()=?°¨@"
					"∑\\¥+{},.-®*[];:_<>~^`·ÈÌÛ˙¡…");//Õ”");
				//	"·ÈÌÛ˙¡…Õ”");
			}
			return _sans_12_red;
		}


	private:

		static Fonts* _instancia;

		static gcn::ImageFont* _sans_12_white;
		static gcn::ImageFont* _sans_12_blue;
		static gcn::ImageFont* _sans_12_red;
};

#endif
