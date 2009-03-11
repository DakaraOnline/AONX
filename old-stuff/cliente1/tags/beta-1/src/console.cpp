/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre                                   *
 *   esteban.torre@gmail.com                                               *
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
#include "console.h"
#include <sstream>
#include "configdata.h"

Consola* Consola::_instancia = 0;
std::stringstream Consola::buffer;

Consola* Consola::instancia(){
	if(_instancia==0){
		_instancia = new Consola();
	}
	return _instancia;
}

Consola::Consola(){
	//window= new gcn::Window("AONX - First steps to the heaven");
	img=NULL;
	scroll= new gcn::ScrollArea();
	scroll->setDimension(gcn::Rectangle(0, 0, 790, 100));
	scroll->setBaseColor(gcn::Color(255, 255, 255, 127));
	scroll->setBackgroundColor(gcn::Color(255, 255, 255, 0));//NOTE: tendría que sobrecargar scroll y así no dibujaría su background.

	text= new gcn::TextBox();
	text->setDimension(gcn::Rectangle(0, 0, 790, 100));
	text->setBackgroundColor(gcn::Color(255, 255, 255, 127));
	text->setOpaque(false);
	text->setBorderSize(0);
	//text->setBaseColor(gcn::Color(255, 255, 255, 127));

	scroll->setContent(text);

	add(scroll);
	setBaseColor(gcn::Color(255, 150, 200, 127));
	resizeToContent();
	setOpaque(false);
	update();
}

Consola::~Consola(){
}
#include <iostream>
void Consola::update(){
	if(buffer.str().size()){
		texto+=buffer.str();
		text->setText(texto);
		buffer.seekg(0,std::ios_base::beg);
		char line[1024];
		while(!buffer.eof())
		{
			if(last_5.size()==5)
			{
				last_5.pop_front();
			}
			buffer.getline(line,1024);
			if(strlen(line)>2)
				last_5.push_back(line);
		}
		buffer.clear();
		buffer.str(std::string());
		text->setCaretRow(text->getNumberOfRows());
		text->scrollToCaret();
	}
}

void Consola::draw (gcn::Graphics *graphics){
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "consola.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawChildren(graphics);
}
