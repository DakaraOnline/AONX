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

#ifndef _inventory_h
#define _inventory_h

#include <SDL.h>
#include <guichan.hpp>

#include <string>
#include <vector>
#include <list>

class InventorySlot : public gcn::Button{
	public:
		//InventorySlot() : grhindex(0),grh_img(NULL),Button("-"){}
		void draw (gcn::Graphics *graphics);
		void drawBorder (gcn::Graphics *graphics){ if(visible) gcn::Button::drawBorder(graphics);}
		void set_grhindex(Sint16 grhindex);
		Sint16	objindex;
		std::string objname;	
		Sint32	objamount;
		bool	isequipped;
		Sint32	valor;
		Sint16	objtype;
		Sint16	objdef;
		Sint16	maxhit;
		Sint16	minhit;
		gcn::Image* grh_img;//fixme
		bool visible;
		bool show_prices;
		
	private:
		Sint16	grhindex;
		
};

class Inventory : public gcn::Window, public gcn::ActionListener{
	public:
		Inventory(int _size, std::string hide_event,gcn::ActionListener* el_coso);
		~Inventory();
		void set_visibility(bool a);
		bool is_visible() { return visible; }
		int get_size() { return size; }
		int get_active() { return active; }
		void draw (gcn::Graphics *graphics);
		gcn::Rectangle getChildrenArea();
		void drawBorder (gcn::Graphics *graphics){}
		InventorySlot* operator [] (int param);
		void show_prices(bool si_o_no);
		void clear();
		void action(const gcn::ActionEvent& actionEvent);
	private:
		std::vector<InventorySlot*> _slots;
		int size;
		gcn::Label *label;
		int active;
		gcn::Image* img;
		gcn::Button* up;
		gcn::Button* down;
		gcn::Button* hide;
		int first_item;
		bool visible;
		int l_x;
		int l_y;
};

#endif

