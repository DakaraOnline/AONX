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
#include "vmain.h"
#include "configdata.h"
#include <sstream>
#include "vlogin.h"
#include "clienteargentum.h"

vmain::vmain() : img(NULL){
	setSize(800,600);
	setMovable(false);
	setTitleBarHeight(0);
	setPadding(0);
	setFocusable(false);
	login_added=false;

	puerto= new _TextField("7666",gcn::Graphics::CENTER);
	puerto->setSize(133,14);
	puerto->setBackgroundColor(gcn::Color(0,0,0,0));
	puerto->setForegroundColor(gcn::Color(255,255,255,255));
	puerto->setBorderSize(0);
	add(puerto,200,163);

	host= new _TextField("testserver.aonx.com.ar",gcn::Graphics::CENTER);
	host->setSize(208,14);
	host->setBackgroundColor(gcn::Color(0,0,0,0));
	host->setForegroundColor(gcn::Color(255,255,255,255));
	host->setBorderSize(0);
	add(host,366,163);

	blogin = new NoDrawButton;
	blogin->setSize(230,80);
	blogin->setFocusable(false);
	blogin->setActionEventId("blogin");
	blogin->addActionListener(this);

	add(blogin,560,340);

	bcreate = new NoDrawButton;
	bcreate->setSize(230,80);
	bcreate->setFocusable(false);
	bcreate->setActionEventId("CREATE");
	bcreate->addActionListener(ClienteArgentum::instancia());

	add(bcreate,560,440);
}

vmain::~vmain(){
}

void vmain::draw (gcn::Graphics *graphics){
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "principal.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawChildren(graphics);
}

void vmain::action(const gcn::ActionEvent& actionEvent){
	if(!login_added){
		add(login,300,230);
		login_added=true;
	}
}
	
int vmain::getPort(){
	std::stringstream tmp;
	tmp.str(std::string(""));
	tmp << puerto->getText();
	int port;
	tmp >> port;
	return port;
}

