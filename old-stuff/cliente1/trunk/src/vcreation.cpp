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

#include "vcreation.h"
#include "configdata.h"
#include "helpers.h"
#include "verror.h"
#include "clienteargentum.h"
#include <iostream>
#include <sstream>

vcreation::vcreation() : img(NULL), img_clase(NULL),lastclase(-1){
	setSize(800,600);
	setMovable(false);
	setTitleBarHeight(0);
	setPadding(0);
	setFocusable(false);

	Text_Nombre = new gcn::TextField;
	Text_Nombre->setWidth(328);
	Text_Nombre->setHeight(18);
	Text_Nombre->setBackgroundColor(gcn::Color(0,0,0,0));
	Text_Nombre->setBorderSize(0);
	add(Text_Nombre,240,79);

	setRaza(1,"Cargando...");
	/*setRaza(1,"Humano");
	setRaza(2,"Elfo");
	setRaza(3,"Elfo Oscuro");
	setRaza(4,"Gnomo");
	setRaza(5,"Enano");*/
	Combo_Raza = new gcn::DropDown(&List_Raza);
	Combo_Raza->setWidth(184);
	Combo_Raza->setHeight(16);
	Combo_Raza->setBackgroundColor(gcn::Color(0,0,0,255));
	
	add(Combo_Raza,395,123);

	setGenero(1,"Hombre");
	setGenero(2,"Mujer");
	Combo_Genero = new gcn::DropDown(&List_Genero);
	Combo_Genero->setWidth(184);
	Combo_Genero->setHeight(16);
	
	Combo_Genero->setBackgroundColor(gcn::Color(0,0,0,255));
	add(Combo_Genero,396,153);

	setClase(1,"Cargando...");
	/*setClase(1,"Mago");
	setClase(2,"Clerigo");
	setClase(3,"Guerrero");
	setClase(4,"Asesino");
	setClase(5,"Ladron");
	setClase(6,"Bardo");
	setClase(7,"Druida");
	setClase(8,"Bandido");
	setClase(9,"Paladin");
	setClase(10,"Cazador");
	setClase(11,"Pescador");
	setClase(12,"Herrero");
	setClase(13,"Leñador");
	setClase(14,"Minero");
	setClase(15,"Carpintero");
	setClase(16,"Pirata");*/
	Combo_Clase = new gcn::DropDown(&List_Clase);
	Combo_Clase->setWidth(184);
	Combo_Clase->setHeight(16);
	Combo_Clase->setActionEventId("CLASE");
	Combo_Clase->addActionListener(this);
	
	
	Combo_Clase->setBackgroundColor(gcn::Color(0,0,0,255));
	add(Combo_Clase,396,182);

	setCiudad(1,"Cargando...");
	/*setCiudad(2,"Nix");
	setCiudad(3,"Banderbille");
	setCiudad(1,"Ullathorpe");
	setCiudad(4,"Lindos");*/
	Combo_Ciudad = new gcn::DropDown(&List_Ciudad);
	Combo_Ciudad->setWidth(175);
	
	Combo_Ciudad->setHeight(16);
	Combo_Ciudad->setBackgroundColor(gcn::Color(0,0,0,255));
	add(Combo_Ciudad,610,222);

	Boton_Volver = new NoDrawButton;
	Boton_Volver->setWidth(180);
	Boton_Volver->setHeight(40);
	Boton_Volver->setActionEventId("MAIN");
	Boton_Volver->addActionListener(ClienteArgentum::instancia());
	add(Boton_Volver,0,560);

	Boton_Dados = new NoDrawButton;
	Boton_Dados->setWidth(100);
	Boton_Dados->setHeight(100);
	Boton_Dados->setActionEventId("DADOS");
	Boton_Dados->addActionListener(ClienteArgentum::instancia());
	add(Boton_Dados,0,180);

	Boton_Continuar = new NoDrawButton;
	Boton_Continuar->setWidth(200);
	Boton_Continuar->setHeight(40);
	Boton_Continuar->setActionEventId("CONTINUAR");
	Boton_Continuar->addActionListener(this);
	add(Boton_Continuar,600,560);

	Label_Fuerza = new gcn::Label("0");
	Label_Fuerza->setWidth(18);
	Label_Fuerza->setHeight(12);
	add(Label_Fuerza,355,162);

	Label_Agilidad = new gcn::Label("0");
	Label_Agilidad->setWidth(18);
	Label_Agilidad->setHeight(12);
	add(Label_Agilidad,355,187);

	Label_Inteligencia = new gcn::Label("0");
	Label_Inteligencia->setWidth(18);
	Label_Inteligencia->setHeight(12);
	add(Label_Inteligencia,355,213);

	Label_Carisma = new gcn::Label("0");
	Label_Carisma->setWidth(18);
	Label_Carisma->setHeight(12);
	add(Label_Carisma,355,238);
	
	Label_Constitucion = new gcn::Label("0");
	Label_Constitucion->setWidth(18);
	Label_Constitucion->setHeight(12);
	add(Label_Constitucion,355,262);

	Label_Restantes = new gcn::Label("10");
	Label_Restantes->setWidth(25);
	Label_Restantes->setHeight(20);
	add(Label_Restantes,479,566);

	for(int i=0;i<21;i++){
		Skill[i] = new gcn::Label("0");
		Skill[i]->setWidth(22);
		Skill[i]->setHeight(302/21);
		add(Skill[i],534,214+i*(int)(302/20.9));//Magic align trick :D xDD
		Skill_up[i] = new NoDrawButton;
		Skill_down[i] = new NoDrawButton;
		Skill_up[i]->setWidth(10);
		Skill_up[i]->setHeight(302/21);
		Skill_down[i]->setWidth(10);
		Skill_down[i]->setHeight(302/21);
		std::stringstream pepe;
		pepe.str("");
		pepe << i;
		Skill_down[i]->setActionEventId(std::string("SD") + pepe.str());
		Skill_up[i]->setActionEventId(std::string("SU") + pepe.str());
		Skill_down[i]->addActionListener(this);
		Skill_up[i]->addActionListener(this);
		add(Skill_down[i],524,214+i*(int)(302/20.9));
		add(Skill_up[i],556,214+i*(int)(302/20.9));
	}

	ClienteArgentum::instancia()->attributes().AddObserver(this);
}

void vcreation::update(Attributes *d){

	Label_Fuerza->setCaption(to_string((*d)[0].get()));

	Label_Agilidad->setCaption(to_string((*d)[1].get()));

	Label_Inteligencia->setCaption(to_string((*d)[2].get()));

	Label_Constitucion->setCaption(to_string((*d)[4].get()));

	Label_Carisma->setCaption(to_string((*d)[3].get()));
}

vcreation::~vcreation(){
	ClienteArgentum::instancia()->attributes().DelObserver(this);
	delete Combo_Raza;
	delete Combo_Clase;
	delete Combo_Genero;
	delete Text_Nombre;
	delete Boton_Volver;
	delete Label_Constitucion;
	delete Label_Inteligencia;
	delete Label_Agilidad;
	delete Label_Carisma;
	delete Label_Fuerza;
	delete Label_Restantes;
	delete img_clase;
	delete img;
}

void vcreation::draw (gcn::Graphics *graphics){
	if(!img){
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << "crear.png";
		img = gcn::Image::load(imgPath.str());
	}
	if(lastclase!=Combo_Clase->getSelected())
	{
		if(img_clase)
			delete img_clase;
		lastclase=Combo_Clase->getSelected();
		std::stringstream imgPath(std::string(""));
		imgPath << ConfigData::GetPath("gui") << getImageFromClase();
		img_clase = gcn::Image::load(imgPath.str());
	}
	graphics->drawImage(img,0,0);
	graphics->drawImage(img_clase,220,314);
	drawChildren(graphics);
}

void vcreation::action(const gcn::ActionEvent& actionEvent){

	int n;
	int n2;
	int t;
	if(actionEvent.getId().substr(0,2)=="SD")
	{
		n = to_number(actionEvent.getId().substr(2,2));
		t = to_number(Label_Restantes->getCaption());
		n2 = to_number(Skill[n]->getCaption());
		if(n2>0){
			t++;
			n2--;
			Label_Restantes->setCaption(to_string(t));
			Skill[n]->setCaption(to_string(n2));
		}
	}else if(actionEvent.getId().substr(0,2)=="SU")
	{
		n = to_number(actionEvent.getId().substr(2,2));
		t = to_number(Label_Restantes->getCaption());
		n2 = to_number(Skill[n]->getCaption());
		if(t>0){
			t--;
			n2++;
			Label_Restantes->setCaption(to_string(t));
			Skill[n]->setCaption(to_string(n2));
		}
	}else if(actionEvent.getId()=="CONTINUAR")
	{
		if(getNombre().empty())
		{
			ErrorMessage::ShowError("Debes tener un nombre");
		}else if(!ValidateAlpha(getNombre().c_str()))
		{
			ErrorMessage::ShowError("El nombre solo puede contener A-Z a-z y espacios");
		}else if(Label_Fuerza->getCaption()=="0")
		{
			ErrorMessage::ShowError("Tenés que tirar los dados (la bola blanca)");
		}else
		{
			ClienteArgentum::instancia()->action(actionEvent);
		}
	}else if(actionEvent.getId()=="CLASE")
	{
		
	}
}

int vcreation::getCiudad()
{
	return Combo_Ciudad->getSelected()+1;
}

int vcreation::getRaza()
{
	return Combo_Raza->getSelected()+1;
}

int vcreation::getClase()
{
	return Combo_Clase->getSelected()+1;
}

int vcreation::getGenero()
{
	return Combo_Genero->getSelected()+1;
}

const std::string vcreation::getNombre()
{
	return Text_Nombre->getText();
}

void vcreation::getSkills(Sint8* skills)
{
	for(int i=0;i<21;i++){
		skills[i]=to_number(Skill[i]->getCaption());
	}
}

std::string vcreation::getImageFromClase()
{
	switch(Combo_Clase->getSelected())
	{
		case 0:
			return "mago.jpg";
			break;
		case 1:
			return "clerigo.jpg";
			break;
		case 2:
			return "guerrero.jpg";
			break;
		case 3:
			return "asesino.jpg";
			break;
		case 4:
			return "ladron.jpg";
			break;
		case 5:
			return "bardo.jpg";
			break;
		case 6:
			return "druida.jpg";
			break;
		case 7:
			return "bandido.jpg";
			break;
		case 8:
			return "paladin.jpg";
			break;
		case 9:
			return "cazador.jpg";
			break;
		case 10:
			return "pescador.jpg";
			break;
		case 11:
			return "herrero.jpg";
			break;
		case 12:
			return "leniador.jpg";
			break;
		case 13:
			return "minero.jpg";
			break;
		case 14:
			return "carpintero.jpg";
			break;
		case 15:
			return "pirata.jpg";
			break;
	}
	return "";
}

void vcreation::resetDados()
{
	// ToDo: cambie setDados por update del observer, ver esto.
	// setDados(0,0,0,0,0);
}

void vcreation::setCiudad(int num, std::string nom)
{
	List_Ciudad.setElementAt(num, nom);
}

void vcreation::setClase(int num, std::string nom)
{
	List_Clase.setElementAt(num, nom);
}

void vcreation::setRaza(int num, std::string nom)
{
	List_Raza.setElementAt(num, nom);
}

void vcreation::setGenero(int num, std::string nom)
{
	List_Genero.setElementAt(num,nom);
}


