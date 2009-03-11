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


#include "vpassword.h"
#include "clienteargentum.h"
#include "helpers.h"
#include "verror.h"

vpassword::vpassword()
{
	Boton_OK = new gcn::Button("OK");
	Text_Password = new gcn::TextField("123");
	setCaption("Elegí tu password");

	setDimension(gcn::Rectangle(800/2-250/2,600/2-100/2,250,100));
	Boton_OK->setDimension(gcn::Rectangle(250/2-80/2,55,80,20));
	Text_Password->setDimension(gcn::Rectangle(250/2-180/2,15,180,20));

	setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
	Boton_OK->setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
	Text_Password->setBackgroundColor(gcn::Color(0x20,0x20,0xFF,127));

	add(Text_Password);
	add(Boton_OK);

	Boton_OK->addActionListener(this);
	Boton_OK->setActionEventId("PASSWORDOK");
}

void vpassword::action(const gcn::ActionEvent& actionEvent)
{
	if(ValidateCommon(Text_Password->getText().c_str()))
	{
		ClienteArgentum::instancia()->action(actionEvent);
	}else
	{
		ErrorMessage::ShowError("El password solo puede contener A-Z a-z 0-9 '.' '_' '-' '@' y espacios");
	}
}

void vpassword::reset()
{
	Text_Password->setText("");
}

vpassword::~vpassword()
{
	remove(Boton_OK);
	remove(Text_Password);
	delete Boton_OK;
	delete Text_Password;
}
