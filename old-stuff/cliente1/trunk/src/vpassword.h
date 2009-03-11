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

#ifndef _vpassword_h
#define _vpassword_h


#include "SDL.h"
#include <guichan.hpp>
#include <string>


class vpassword : public gcn::Window, public gcn::ActionListener
{
public:
	vpassword();
	~vpassword();

	void action(const gcn::ActionEvent& actionEvent);
	void reset();
	const std::string getPassword() { return Text_Password->getText(); }

private:

	gcn::TextField* Text_Password;
	gcn::Button* Boton_OK;
};


#endif

