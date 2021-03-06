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

#ifndef _vmain_h
#define _vmain_h

#include <guichan.hpp>
#include "customwidgets.h"

class vmain : public gcn::Window
{
public:
	vmain();
	~vmain();
	void draw (gcn::Graphics *graphics);
	void drawBorder (gcn::Graphics *graphics) {}
	void setLoginWindow(gcn::Window* w){ login=w; }
	std::string getHost(){ return "testserver.aonx.com.ar"; }
	int getPort();
private:
	gcn::Image* img;
	gcn::Window* login;
	NoDrawButton* blogin;
	NoDrawButton* bcreate;
	bool login_added;
	_TextField* puerto;
	_TextField* host;

	ImageButton* login_button;
	ImageButton* create_button;
	ImageButton* servers_button;
	ImageButton* options_button;
	ImageButton* exit_button;
};

#endif


