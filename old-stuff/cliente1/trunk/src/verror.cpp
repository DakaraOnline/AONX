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

#include "verror.h"
#include "clienteargentum.h"
#include "guichanloader.h"

ErrorMessage* ErrorMessage::_instancia = 0;

ErrorMessage::ErrorMessage()
{
	ventana = new gcn::Window("Error");
	error = new gcn::Label;
	boton = new gcn::Button("OK");
	ventana->setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
	boton->setBaseColor(gcn::Color(0x20,0x20,0xFF,127));
	ventana->setDimension(gcn::Rectangle(800/2-400/2,600/2-150/2,400,100));
	boton->setDimension(gcn::Rectangle(145,60,90,27));
	ventana->add(boton);
	error->setDimension(gcn::Rectangle(10,10,375,45));
	ventana->add(error);
	boton->setActionEventId("ERROR_OK");
	boton->addActionListener(ClienteArgentum::instancia());
	showing=false;
}

ErrorMessage::~ErrorMessage()
{
	ventana->remove(error);
	ventana->remove(boton);
	delete error;
	delete boton;
	delete ventana;
}

void ErrorMessage::ShowError(std::string que)
{
	if(!_instancia)
		_instancia = new ErrorMessage;
	_instancia->error->setCaption(que);
	if(!_instancia->showing)
	{
		_instancia->showing=true;
		ClienteArgentum::instancia()->_guichan->get_top()->add(_instancia->ventana);
		
	}
	ClienteArgentum::instancia()->_guichan->get_top()->moveToTop(_instancia->ventana);
}

void ErrorMessage::off()
{
	if(_instancia->showing)
	{
		ClienteArgentum::instancia()->_guichan->get_top()->remove(_instancia->ventana);
		_instancia->showing=false;
	}
}
