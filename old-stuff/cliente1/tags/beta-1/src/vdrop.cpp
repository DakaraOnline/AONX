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

#include "vdrop.h"
#include "clienteargentum.h"
#include "customwidgets.h"

#include <sstream>

vdrop::vdrop(int _slot,Inventory* _inventario, std::string evento, std::string titulo) : slot(_slot),
		 inventario(_inventario), Window(titulo)
{
	setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));
	setSize(125,80);

	ok = new gcn::Button("OK");
	cancel = new gcn::Button("Minga!");
	amount = new gcn::TextField("");
	dibujito = new Dibujito(*((*inventario)[slot]->grh_img));
	dibujito->setSize(32,32);

	ok->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));
	cancel->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));

	ok->setActionEventId(evento);
	cancel->setActionEventId("DROP_CLOSE");

	ok->addActionListener(ClienteArgentum::instancia());
	cancel->addActionListener(ClienteArgentum::instancia());
	
	amount->setSize(60,15);
	add(dibujito,2,2);
	add(amount,47,12);
	add(ok,20,33);
	add(cancel,50,33);
	
}

vdrop::~vdrop()
{
	delete ok;
	delete cancel;
	delete amount;
	delete dibujito;
}

Uint32 vdrop::get_amount(){
	std::stringstream tmp;
	tmp.str(amount->getText());
	Uint32 a=0;
	tmp >> a;
	if(a > (*inventario)[slot]->objamount){
		a=(*inventario)[slot]->objamount;
	}
	return a;
}
