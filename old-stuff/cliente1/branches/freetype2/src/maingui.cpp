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



#include "maingui.h"
#include "configdata.h"
#include "entity.h"
#include <sstream>
#include "clienteargentum.h"

MainGui::MainGui() : img(NULL), visible(false)
{

	name=new gcn::Label("XXXXXXXXXXXXX");
	name->setAlignment(gcn::Graphics::CENTER);
	name->setWidth(180);
	add(name,300,14);

	lvl=new gcn::Label("XX");
	lvl->setWidth(30);
	lvl->setAlignment(gcn::Graphics::CENTER);
	add(lvl,520,14);

	oro=new gcn::Label("XXXXXXXX");
	add(oro,621,40);

	exp= new bar(300,150,true);
	exp->setForegroundColor(gcn::Color(0xFA,0xFA,0xFA,210));
	exp->setSize(96+48,12);
	exp->showPercent(true);
	add(exp,370-30,47);

	vida= new graphicBar("vida_gui.png",20,20,true);
	vida->setForegroundColor(gcn::Color(255,0,0,127));
	vida->setSize(89,88);
	add(vida,247,47);

	stamina = new bar(50,40,true);
	stamina->setForegroundColor(gcn::Color(255,255,0,127));
	stamina->setSize(96,12);
	add(stamina,364,74);

	mana = new graphicBar("mana_gui.png",20,20,true);
	mana->setForegroundColor(gcn::Color(0x0C,0xFF,0xFF,127));
	mana->setSize(89,88);
	add(mana,483,47);

	hambre = new bar(100,80,true);
	hambre->setForegroundColor(gcn::Color(10,200,10,127));
	hambre->setSize(96,12);
	add(hambre,364,97);

	sed= new bar(100,35,true);
	sed->setForegroundColor(gcn::Color(0,0,230,127));
	sed->setSize(96,12);
	add(sed,364,120);

	setSize(800,141);
	setPosition(0,600-141);
}

MainGui::~MainGui()
{
	if(img)
		delete img;
	delete oro;
	delete lvl;
	delete name;
	delete exp;
	delete vida;
	delete stamina;
	delete mana;
	delete hambre;
	delete sed;
}

void MainGui::set_visibility(bool a)
{
	visible=a;
}

void MainGui::draw (gcn::Graphics *graphics){
	if(!visible) return;
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "guidown.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawMiniMap(graphics);
	drawChildren(graphics);
}

gcn::Rectangle MainGui::getChildrenArea(){
	return gcn::Rectangle(1,1,getWidth(),getHeight());
}

void MainGui::setLevel(const Uint32 x){
	std::stringstream tmp;
	tmp.str(std::string(""));
	tmp  << x;
	lvl->setCaption(tmp.str());
}

void MainGui::setOro(const Uint32 x){
	std::stringstream tmp;
	tmp.str(std::string(""));
	tmp << x;
	oro->setCaption(tmp.str());
}


void MainGui::drawMiniMap(gcn::Graphics *graphics)
{
	if(!render_minimap) return;
	int base_x=681;
	int base_y=36;
	ao::MapFile_ptr _map = ClienteArgentum::instancia()->ActualMap();
	for(int y=1;y<100;y++)
	{
		for(int x=1;x<100;x++)
		{
			ao::MapTile & tile = _map->getTile(ao::Pos(x,y));
			if(tile.ent)
			{
				//graphics->setColor(gcn::Color(0xFF,0,0,0xFF)); RADAR MWHAHAH
			}else if(tile.blocked)
			{
				graphics->setColor(gcn::Color(0,0,0,0xFF));
			}else
			{
				graphics->setColor(gcn::Color(0,0xBB,0,0xFF));
			}
			graphics->drawPoint(x+base_x,y+base_y);
		}
	}
	int x=ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->getPos().x;
	int y=ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->getPos().y;
	graphics->setColor(gcn::Color(0xDD,0,0,0xFF));
	graphics->drawPoint(x+base_x,y+base_y);
	graphics->drawPoint(x+base_x+1,y+base_y);
	graphics->drawPoint(x+base_x,y+base_y+1);
	graphics->drawPoint(x+base_x-1,y+base_y);
	graphics->drawPoint(x+base_x,y+base_y-1);
}


