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
	setSize(283,342);
	setPosition(800/2-283/2,600/2-342/2);
	setMovable(false);
	setTitleBarHeight(0);
	setPadding(0);
	setFocusable(false);
	login_added=false;

	/*puerto= new _TextField("7666",gcn::Graphics::CENTER);
	puerto->setSize(133,14);
	puerto->setBackgroundColor(gcn::Color(0,0,0,0));
	puerto->setForegroundColor(gcn::Color(255,255,255,255));
	puerto->setBorderSize(0);
	add(puerto,200,163);*/

	/*host= new _TextField("testserver.aonx.com.ar",gcn::Graphics::CENTER);
	host->setSize(208,14);
	host->setBackgroundColor(gcn::Color(0,0,0,0));
	host->setForegroundColor(gcn::Color(255,255,255,255));
	host->setBorderSize(0);
	add(host,366,163);*/

	/*blogin = new NoDrawButton;
	blogin->setSize(230,80);
	blogin->setFocusable(false);
	blogin->setActionEventId("blogin");
	blogin->addActionListener(this);

	add(blogin,560,340);*/

	/*bcreate = new NoDrawButton;
	bcreate->setSize(230,80);
	bcreate->setFocusable(false);
	bcreate->setActionEventId("CREATE");
	bcreate->addActionListener(ClienteArgentum::instancia());

	add(bcreate,560,440);*/

	login_button = new ImageButton();
	create_button = new ImageButton();
	servers_button = new ImageButton();
	options_button = new ImageButton();
	exit_button = new ImageButton();

	login_button->setSize(250, 40);
	create_button->setSize(250, 40);
	servers_button->setSize(250, 40);
	options_button->setSize(250, 40);
	exit_button->setSize(250, 40);
	
	std::string path;
	path=ConfigData::GetPath("gui") + std::string("main_menu/");

	login_button->setNormalImage(path + std::string("login.png"));
	login_button->setMoserOverImage(path + std::string("loginb.png"));
	login_button->setActionEventId("LOGIN_DIALOG");
	login_button->addActionListener(ClienteArgentum::instancia());

	create_button->setNormalImage(path + std::string("create.png"));
	create_button->setMoserOverImage(path + std::string("createb.png"));
	create_button->setActionEventId("CREATE");
	create_button->addActionListener(ClienteArgentum::instancia());

	servers_button->setNormalImage(path + std::string("servers.png"));
	servers_button->setMoserOverImage(path + std::string("serversb.png"));

	options_button->setNormalImage(path + std::string("opciones.png"));
	options_button->setMoserOverImage(path + std::string("opcionesb.png"));
	options_button->setActionEventId("OPTIONS");
	options_button->addActionListener(ClienteArgentum::instancia());

	exit_button->setNormalImage(path + std::string("salir.png"));
	exit_button->setMoserOverImage(path + std::string("salirb.png"));
	exit_button->setActionEventId("EXIT");
	exit_button->addActionListener(ClienteArgentum::instancia());

	add(login_button,17, 66);
	add(create_button,17, 121);
	add(servers_button,17, 176);
	add(options_button,17, 231);
	add(exit_button,17, 287);


}

vmain::~vmain(){
}

void vmain::draw (gcn::Graphics *graphics){
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "main_menu/main.png";
		img = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	drawChildren(graphics);
}

	
int vmain::getPort(){
	/*std::stringstream tmp;
	tmp.str(std::string(""));
	tmp << puerto->getText();
	int port;
	tmp >> port;*/
	return 7666;
}

