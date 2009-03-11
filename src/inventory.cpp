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
		unsigned int losk = objamount / 1000;
		unsigned int resto = objamount % 1000;
		if(losk>9)
		{
			tmp << losk << "K";
			if(resto>0)
				tmp << "+";
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
	setSize(195,210);
	setBaseColor(gcn::Color(255, 150, 200, 127));
	int colsPerRow=5;
	int actX,actY;
	int baseX=9;
	int baseY=24;
	for(int i=0 ;i<size; i++){
		_slots[i]= new InventorySlot;
		_slots[i]->grh_img=0;
		if(i<20){
			_slots[i]->visible=true;
		}else{
			_slots[i]->visible=false;
		}
		_slots[i]->set_grhindex(0);
		_slots[i]->valor = 0;
		actX=baseX + (i%colsPerRow) * 36;
		actY=baseY + (i/colsPerRow) * 35;
		_slots[i]->setSize(32,32);
		//_slots[i]->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 65));
		_slots[i]->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 0));
		///Esto tendr�a que tener un patron base que se pase x el constructor (y agregar action listeners) o hacer virtual la funcion de action, nose, REVISAR. =). :D
		std::stringstream bid;
		bid.str(std::string());
		bid << "boton " << i;
		_slots[i]->setActionEventId(bid.str());
		_slots[i]->addActionListener((gcn::ActionListener*)this);
		add(_slots[i],actX,actY);
	}
	label= new gcn::TextBox("Nada");
	label->setSize(177,34);
	label->setOpaque(false);
	label->setEditable(false);
	label->setBorderSize(0);
//	label->setAlignment(gcn::Graphics::CENTER);
	
	up=new gcn::Button(" ");
	down= new gcn::Button(" ");
	up->setActionEventId("UP");
	up->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 0));
	down->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 0));
	down->setActionEventId("DOWN");
	up->addActionListener(this);
	up->setBorderSize(0);
	down->addActionListener(this);
	down->setBorderSize(0);
	add(label,8,169);
	add(up,7,4);
	add(down,28,4);
	hide = new gcn::Button(" ");
	hide->setBaseColor(gcn::Color(0x99, 0xDF, 0xF5, 0));
	hide->setBorderSize(0);
	add(hide,170,5);
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
		std::string what= _slots[a]->objname;
		std::stringstream amount;
		
		
		if(_slots[a]->show_prices)
		{
			std::stringstream precio;
			precio << "\n$";
			precio << _slots[a]->valor;
			what.append(precio.str());
		}
		amount << what << " - " << _slots[a]->objamount;
		label->setText(amount.str());
		label->setSize(177,34);
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

