/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre  				   *
 *   esteban.torre@gmail.com  						   *
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

#ifndef _bar_h
#define _bar_h

#include <guichan.hpp>
#include <string>
#include <SDL.h>

class bar : public gcn::Widget{
	public:	
		bar(Uint32 _max=0, Uint32 _val=0, bool _text=true);
		~bar(){};
		virtual void draw (gcn::Graphics *graphics);
		void drawBorder (gcn::Graphics *graphics) {}
		void showText(bool b) { draw_text=b; }
		void setMax(const Uint32 _max);
		void setSize(int w, int h);
		void setValue(const Uint32 _val);
		void showPercent(bool b) { show_percent=b; update(); }
	private:
		void update();
		Uint32 max;
		Uint32 value;
		
	protected:
		Uint32 bar_lenght;
		bool draw_text;
	private:
		bool show_percent;
	protected:
		std::string text;
};

class graphicBar : public bar
{
	public:
		graphicBar(std::string _img, Uint32 _max=0, Uint32 _val=0, bool _text=true);
		~graphicBar(){};
		void draw (gcn::Graphics *graphics);
	private:
		gcn::Image* img;
		std::string img_path;
};


#endif

