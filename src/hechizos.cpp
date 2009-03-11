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

#include "hechizos.h"
#include <sstream>
#include "clienteargentum.h"
#include "configdata.h"

Hechizo::Hechizo()
{
	nombre="Nada";
	index=0;
	intervalo=0;
	setDimension(gcn::Rectangle(0,0,164,15));
	setBaseColor(gcn::Color(61,44,10,100));
	setBackgroundColor(gcn::Color(61,44,10,100));
	actualiza=true;
	actualizaNombre();
	setForegroundColor(gcn::Color(255,0,0,255));
}

void Hechizo::draw(gcn::Graphics * g)
{
	actualizaNombre();
	int percent = 100;
	if(intervalo)
	{
		percent = ((SDL_GetTicks() - ultimo_uso) * 100) / intervalo;
	}
	
	if(percent>100)
		percent=100;
	//actualizaNombre();
	setBaseColor(gcn::Color(61+((100.0-percent)/100.0)*(255-61),44,10,100));
	setBackgroundColor(gcn::Color(61+((100.0-percent)/100.0)*(255-61),44,10,100));
	g->drawRectangle(gcn::Rectangle(0,0,mDimension.width,mDimension.height));
	g->fillRectangle(gcn::Rectangle(0,0,mDimension.width*(percent/100.0),mDimension.height));
	int textX;
        int textY = getHeight() / 2 - getFont()->getHeight() / 2;

        switch (getAlignment())
        {
          case gcn::Graphics::LEFT:
              textX = 4;
              break;
          case gcn::Graphics::CENTER:
              textX = getWidth() / 2;
              break;
          case gcn::Graphics::RIGHT:
              textX = getWidth() - 4;
              break;
          default:
              throw GCN_EXCEPTION("Unknown alignment.");
        }

        g->setFont(getFont());

        if (isPressed())
        {
            g->drawText(getCaption(), textX + 1, textY + 1, getAlignment());
        }
        else
        {
            g->drawText(getCaption(), textX, textY, getAlignment());

            if (isFocused())
            {
                g->drawRectangle(gcn::Rectangle(2, 2, getWidth() - 4,
                                                  getHeight() - 4));
            }
        }
	gcn::Button::drawBorder(g);
}

void Hechizo::actualizaNombre()
{
	if(!actualiza) return;
	std::stringstream pepe;
	pepe << nombre;
/*	if(nombre!="Nada" && intervalo != 0.0)
	{
		int percent = ((SDL_GetTicks() - ultimo_uso) * 100) / intervalo;
		if(percent>100)
		{
			percent=100;
			actualiza=false;
		}
		pepe << " " << percent << "%";
	}*/
	setCaption(pepe.str());
}

bool Hechizo::usar()
{
	if(intervalo!=0)
	{
		if((SDL_GetTicks() - ultimo_uso)>=intervalo)
		{
			actualiza=true;
			ultimo_uso=SDL_GetTicks();
			return true;
		}else
		{
			return false;
		}
	}else
	{
		return false;
	}
}

bool Hechizo::puede_usar()
{
	if(intervalo!=0)
	{
		//TODO: Falta modificar el protocolo para q el server ya nos diga si lo puede usar
		//Esto solo verifica que no sea Nada. (Ningun hechizo debe tener intervalo 0.
		return true;
	}
	return false;
}

Hechizos::Hechizos() : hechis(50), gcn::Window("Hechizos"), showingFrom(0)
{

}
Hechizos::~Hechizos()
{

	for(int a=0;a<50;a++)
	{
		delete hechis[a];
	}
}

void Hechizos::init()
{
	//if(!cont) return;
	setDimension(gcn::Rectangle(800-200,600-210-135,195,215));
	setBaseColor(gcn::Color(100,100,230,127));
	setBackgroundColor(gcn::Color(100,100,230,127));
	int actx=6;
	int acty=11;
	visible=true;

	up = new gcn::Button;
	down = new gcn::Button;
	up->setBaseColor(gcn::Color(61,44,10,100));
	down->setBaseColor(gcn::Color(61,44,10,100));
	add(up,174,7);
	down->setWidth(14);
	up->setWidth(14);
	down->setHeight(14);
	up->setHeight(14);
	add(down,174,180);
	up->setActionEventId("HUP");
	down->setActionEventId("HDOWN");
	up->addActionListener(this);
	down->addActionListener(this);

	for(int a=0;a<50;a++)
	{
		std::stringstream pepe;
		pepe << "HECHI" << a;
		hechis[a]=new Hechizo();
		hechis[a]->setActionEventId(pepe.str());
		hechis[a]->addActionListener(ClienteArgentum::instancia());
	}
	for(int a=showingFrom;(a<(showingFrom+12))&&(a<50);a++)
	{
		add(hechis[a],actx,acty);
		acty+=15;
	}
	img=0;
}

void Hechizos::action(const gcn::ActionEvent &actionEvent)
{
	if(!visible) return;
	if(actionEvent.getId()=="HUP")
	{
		updateDisplay(false);
	}else if(actionEvent.getId()=="HDOWN")
	{
		updateDisplay(true);
	}
}

void Hechizos::updateDisplay(bool suma)
{

	for(int a=showingFrom;(a<(showingFrom+12))&&(a<50);a++)
	{
		remove(hechis[a]);
	}

	if(!suma)
	{
		if(showingFrom>0) 
			showingFrom--;
	}else
	{
		if(showingFrom<38) 
			showingFrom++;
	}
	int actx=6;
	int acty=11;
	for(int a=showingFrom;(a<(showingFrom+12))&&(a<50);a++)
	{
		add(hechis[a],actx,acty);
		acty+=15;
	}
}

void Hechizos::draw(gcn::Graphics *graphics)
{
	if(!visible) return;
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "Hechizos.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawChildren(graphics);
}
