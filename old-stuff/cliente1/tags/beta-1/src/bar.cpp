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

#include "bar.h"
#include <sstream>
#include "configdata.h"

bar::bar(Uint32 _max, Uint32 _val, bool _text) 
 : max(_max),value(_val),draw_text(_text)
{
	show_percent=false;
	update();
}

void bar::setSize(int w, int h){
	gcn::Widget::setSize(w,h);
	update();
}

void bar::update(){
	if(draw_text){
		std::stringstream mytext;
		mytext.str(std::string(""));
		if(!show_percent){
			mytext << value << "/" << max;
		}else{
			mytext << ((value*100)/max) << "%";
		}
		text=mytext.str();
	}
	int a=mDimension.width;
	bar_lenght = (Uint32)(mDimension.width * (value/(max/1.0)));
}

void bar::setMax(const Uint32 _max){
	if(value > _max){
		max=value;
	}else{
		max=_max;
	}
	update();
}

void bar::setValue(const Uint32 _val){
	if(_val > max){
		value=max;
	}else{
		value=_val;
	}
	update();
}

void bar::draw (gcn::Graphics *graphics)
{
	graphics->setColor(mForegroundColor);
	graphics->drawRectangle(gcn::Rectangle(0,0,mDimension.width,mDimension.height));
	graphics->fillRectangle(gcn::Rectangle(0,0,bar_lenght,mDimension.height));
	if(draw_text){
		graphics->drawText(text,mDimension.width/2,-1,gcn::Graphics::CENTER);
	}
}


graphicBar::graphicBar(std::string _img,Uint32 _max, Uint32 _val, bool _text) :
	bar(_max,_val,_text), img(NULL), img_path(_img)
{
	
}

void graphicBar::draw (gcn::Graphics *graphics)
{
	//graphics->setColor(mForegroundColor);
	//graphics->drawRectangle(gcn::Rectangle(0,0,mDimension.width,mDimension.height));
	//graphics->fillRectangle(gcn::Rectangle(0,0,bar_lenght,mDimension.height));
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << img_path;
		img = gcn::Image::load(imgPath.str());
	}
	//graphics->drawImage(img,0,bar_lenght,);
	graphics->drawImage(img,0,mDimension.height-bar_lenght,0,mDimension.height-bar_lenght,mDimension.width,bar_lenght);
	if(draw_text){
		graphics->drawText(text,mDimension.width/2,mDimension.height/2-12,gcn::Graphics::CENTER);
	}
}
