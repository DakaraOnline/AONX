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

#include "inventory.h"
#include <sstream>
#include "configdata.h"
#include "clienteargentum.h"
#include <iostream> //para debug.


void InventorySlot::set_grhindex(Sint16 num){
	if(grhindex==num) return;
	grhindex=num;
	std::stringstream imgPath;
	if(num>0){
		if(grh_img) delete grh_img;
		imgPath << ConfigData::GetPath("graficos") << ClienteArgentum::instancia()->get_grhData()->getGrhData(grhindex).fileNum << ".png";
		grh_img = gcn::Image::load(imgPath.str());
	}else{
		if(grh_img) delete grh_img;
		grh_img=NULL;
	}
}
void InventorySlot::draw (gcn::Graphics *graphics){
	if(!visible) return;
	gcn::Button::draw(graphics);
	std::stringstream tmp;
	tmp.str(std::string());
	if(grh_img){
		graphics->drawImage(grh_img,0,0);
		if(show_prices)
		{
			tmp << "$" << valor;
		}else
		{
			tmp << objamount;
		}
		graphics->drawText(tmp.str(),1,19);
		if(isequipped){
			graphics->drawText("+",25,-2);
		}
	}
	
	
}

InventorySlot* Inventory::operator [] (int param){
	if((param>=size)||(param<0)){
		// FIXME: Exception??
	}
	return _slots[param];
}

Inventory::Inventory(int _size, std::string hide_event, gcn::ActionListener* el_coso) : _slots(_size),size(_size),gcn::Window("Inventario"),active(0),first_item(0),visible(true)
{

	img=0;//revisame
	setSize(180,180);
	setBaseColor(gcn::Color(255, 150, 200, 127));
	int colsPerRow=5;
	int actX,actY;
	int baseX=5;
	int baseY=22;
	for(int i=0 ;i<size; i++){
		_slots[i]= new InventorySlot;
		_slots[i]->grh_img=0;
		if(i<20){
			_slots[i]->visible=true;
		}else{
			_slots[i]->visible=false;
		}
		_slots[i]->set_grhindex(0);
		actX=baseX + (i%colsPerRow) * 34;
		actY=baseY + (i/colsPerRow) * 34;
		_slots[i]->setSize(32,32);
		_slots[i]->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 65));
		///Esto tendría que tener un patron base que se pase x el constructor (y agregar action listeners) o hacer virtual la funcion de action, nose, REVISAR. =). :D
		std::stringstream bid;
		bid.str(std::string());
		bid << "boton " << i;
		_slots[i]->setActionEventId(bid.str());
		_slots[i]->addActionListener((gcn::ActionListener*)this);
		add(_slots[i],actX,actY);
	}
	label= new gcn::Label("Nada");
	label->setSize(160,15);
	label->setAlignment(gcn::Graphics::CENTER);
	up=new gcn::Button("u");
	down= new gcn::Button("d");
	up->setActionEventId("UP");
	up->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));
	down->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 127));
	down->setActionEventId("DOWN");
	up->addActionListener(this);
	down->addActionListener(this);
	add(label,5,162);
	add(up,2,162);
	add(down,159,162);
	hide = new gcn::Button("x");
	hide->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 80));
	add(hide,158,1);
	hide->setHeight(14);
	hide->setActionEventId(hide_event);
	hide->addActionListener(el_coso);
	//add(label,5,146);
	l_x=l_y=0;
	show_prices(false);
}

Inventory::~Inventory(){
	for(int i=0; i< size; i++){
		delete _slots[i];
	}
	delete label;
	delete img;
}
void Inventory::draw (gcn::Graphics *graphics){
	if(!visible) return;
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "inventario.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawChildren(graphics);
}
void Inventory::action(const gcn::ActionEvent& actionEvent){
	std::string temp;
	if(actionEvent.getId()==std::string("UP")){
		if(first_item<5) return;
		for(int i = 0;i<size;i++){
			if(i>=(first_item+15)){
				_slots[i]->visible=false;
			}else if(i>=(first_item-5)){
				_slots[i]->visible=true;
			}
			_slots[i]->setY(_slots[i]->getY()+34);
		}
		first_item-=5;
	}else if(actionEvent.getId()==std::string("DOWN")){
		if(first_item>=(size-5)) return;
		for(int i = 0;i<size;i++){
			if(i<(first_item+5)){
				_slots[i]->visible=false;
			}else if(i<first_item+25){
				_slots[i]->visible=true;
			}
			_slots[i]->setY(_slots[i]->getY()-34);
		}
		first_item+=5;
	}else{
		std::stringstream ev(actionEvent.getId());
		ev >> temp;
		int a;
		ev >> a;
		label->setCaption(_slots[a]->objname);
		active=a;
	}
}

gcn::Rectangle Inventory::getChildrenArea(){
	return gcn::Rectangle(1,1,getWidth(),getHeight());
}

void Inventory::set_visibility(bool a){
	if((visible==true)&&(a==false)){
		l_x=getX();
		l_y=getY();
		setX(800);//FIXME: FEO FEO pero no veo como sacarmelas de encima sin borrarlas
		setY(600);// y si las borro es un quilombo.
	}else if((visible==false)&&(a==true)){
		if(l_x) setX(l_x);
		if(l_y) setY(l_y);
	}
	visible=a;
}

void Inventory::clear()
{
	for(int i=0;i<size;i++)
	{
		_slots[i]->set_grhindex(0);
		_slots[i]->objindex=0;
		_slots[i]->objname="";
		_slots[i]->objamount=0;
	}
}

void Inventory::show_prices(bool si_o_no)
{
	for(int i=0;i<size;i++)
	{
		_slots[i]->show_prices=si_o_no;
	}
}

