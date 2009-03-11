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




#ifndef _maingui_h
#define _maingui_h

#include "SDL.h"
#include <guichan.hpp>
#include "customwidgets.h"
#include <string>
#include <vector>
#include "bar.h"

class MainGui : public gcn::Window{
	public:
		MainGui();
		~MainGui();

		void set_visibility(bool a);
		bool is_visible() { return visible; }
		void draw (gcn::Graphics *graphics);
		gcn::Rectangle getChildrenArea();
		void drawBorder (gcn::Graphics *graphics){}



		void toggleMiniMapRender(){ render_minimap= !render_minimap; }

		void setMaxExp(const Uint32 x){ exp->setMax(x); }
		void setExp(const Uint32 x){ exp->setValue(x); }
		void setMaxVida(const Uint32 x){ vida->setMax(x); }
		void setVida(const Uint32 x){ vida->setValue(x); }
		void setMaxStamina(const Uint32 x){ stamina->setMax(x); 
}
		void setStamina(const Uint32 x){ stamina->setValue(x); }
		void setMaxMana(const Uint32 x){ mana->setMax(x); }
		void setMana(const Uint32 x){ mana->setValue(x); }
		void setMaxHambre(const Uint32 x){ hambre->setMax(x); }
		void setHambre(const Uint32 x){ hambre->setValue(x); }
		void setMaxSed(const Uint32 x){ sed->setMax(x); }
		void setSed(const Uint32 x){ sed->setValue(x);}
		void setLevel(const Uint32 x);
		void setOro(const Uint32 x);
		void setNombre(std::string s){ name->setCaption(s);}

		
	private:
		

		bool render_minimap;

		gcn::Image* img;
		bool visible;
		void drawMiniMap(gcn::Graphics *graphics);

		gcn::Label* name;
		gcn::Label* lvl;
		gcn::Label* oro;
		bar* exp;
		bar* vida;
		bar* stamina;
		bar* mana;
		bar* hambre;
		bar* sed;

};

#endif



