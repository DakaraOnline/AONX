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

#ifndef _vdrop_h
#define _vdrop_h

class Dibujito;

#include <guichan.hpp>

#include "SDL.h"

class Inventory;
/// @remarks: hice un poco m�s flexible el funcionamiento del widget para que sirva para todo tipo de dialogo que pregunte sobre una cantidad de un inventario.
class vdrop : public gcn::Window
{
	public:
		vdrop(int _slot,Inventory* _inventario, std::string evento, std::string titulo);
		~vdrop();
		int get_slot(){ return slot;}
		Uint32 get_amount();
		void focus(){ 	amount->requestFocus (); } //FIXME esto no es lo mejor pero es lo que logr�.
	private:
		int slot;
		gcn::TextField* amount;
		gcn::Button* ok;
		gcn::Button* cancel;
		Dibujito* dibujito;
		Inventory* inventario;
};

#endif
