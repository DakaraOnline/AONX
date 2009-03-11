/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre                                   *
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
#ifndef _console_h
#define _console_h

#include <guichan.hpp>
#include <string>
#include <sstream>
#include <list>

class Consola : public gcn::Window{
	public:
		Consola();
		~Consola();
		gcn::Window* getWindow(){ return this;};
		void draw (gcn::Graphics *graphics);
		void drawBorder (gcn::Graphics *graphics){}
		static std::stringstream buffer;
		static Consola* instancia();
		void update();
		std::list<std::string>* get_last_5() { return &last_5; }
	private:
		static Consola* _instancia;
		std::string texto;
		gcn::Window* window;
		gcn::ScrollArea* scroll;
		gcn::TextBox* text;
		gcn::Image* img;
		std::list<std::string> last_5;
};

#endif
