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

#include "vlogin.h"
#include "clienteargentum.h"

vlogin::vlogin() : Window("Login"){
	luser = new gcn::Label("Usuario:");
	lpass = new gcn::Label("Password:");
	tuser = new gcn::TextField("             ");
	tuser->adjustSize();
	tuser->setText("");
	tpass = new gcn::TextField("             ");
	tpass->adjustSize();
	tpass->setText("");
	boton = new gcn::Button("OK");
	boton->setActionEventId("LOGIN");
	boton->addActionListener(ClienteArgentum::instancia());
	boton->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));
	boton->setDimension(gcn::Rectangle(70,68,45,25));
	add(luser,10,10);
	add(lpass,10,40);
	add(tuser,90,10);
	add(tpass,90,40);
	add(boton);
	setSize(180,115);
	setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));
}

vlogin::~vlogin(){
	///no muy seguro.
	delete luser;
	delete lpass;
	delete boton;
	delete tuser;
	delete tpass;
}

const std::string& vlogin::get_user(){
	return tuser->getText();
}

const std::string& vlogin::get_pass(){
	return tpass->getText();
}
