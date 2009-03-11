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

#include <iostream>
#include <exception>

#include "configdata.h"
#include "guichanloader.h"

#include "console.h"

GuichanLoader::GuichanLoader()
{
}


GuichanLoader::~GuichanLoader()
{
}

void GuichanLoader::loadOpenGL( int width, int height )
{
	std::cout << "GuichanLoader::loadOpenGL..." ;
	
	_width = width;
	_height = height;
	
	imageLoader = new gcn::OpenGLSDLImageLoader();
	gcn::Image::setImageLoader(imageLoader);
	
	gcn::OpenGLGraphics* openglgraphics = new gcn::OpenGLGraphics();
	openglgraphics->setTargetPlane(width, height);
	
	graphics = openglgraphics ;
	
	input = new gcn::SDLInput();
	
	loadTopContainer();
	
	std::cout << " OK" << std::endl;
}


void GuichanLoader::loadTopContainer()
{
	top = new gcn::Container();
	top->setDimension(gcn::Rectangle(0, 0, _width, _height));
	
	// El color no influye, el control es opaco
	top->setBaseColor(gcn::Color(0, 0, 0, 0));
	
	// Al ponerlo en Opaque = False no dibuja el rectangulo
	top->setOpaque(false);
	
	gui = new gcn::Gui();
	gui->setGraphics(graphics);
	gui->setInput(input);
	gui->setTop(top);
	
	font = new gcn::ImageFont(
		// Editar la siguiente linea para indicar el PATH Del archivo de Font del texto
		(ConfigData::GetPath("guifonts") + std::string("rpgfont_wider.png")).c_str(), 
		" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "0123456789.,!?-+/():;%&`'*#=[]\"<>{}^~|_@$\\"
                "áÁéÉíÍóÓúÚ\xE7\xE6\xA5\xA3\xA2\xA1\xBF");
	gcn::Widget::setGlobalFont(font);
	
	// GUI //
	//TODO: revisar esto.
	//top->add(Consola::instancia()->getWindow(), 3, 480);


}

