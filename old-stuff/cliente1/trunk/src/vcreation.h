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

#ifndef _vcreation_h_
#define _vcreation_h_
#include "SDL.h"
#include <guichan.hpp>
#include "customwidgets.h"
#include <string>
#include <vector>
#include "stats.h"

//TODO: mover esto a custom widgets?
class guiStringList : public gcn::ListModel
{
public:
	guiStringList() : num(0){};

	std::string getElementAt(int i){
		if(i>=num) return std::string("Error");
		return content[i+1];
	}

	void setElementAt(int i, std::string element){
		if(content.size()<=i) content.resize(i+1);
		content[i]=element;
		num=i+1;
	}

	int getNumberOfElements() {return num-1;};

private:
	int num;
	std::vector<std::string> content;
};


class vcreation : public gcn::Window, public gcn::ActionListener, public AttributesObserver
{
public:
	vcreation();
	~vcreation();
	void resetDados();
	void draw (gcn::Graphics *graphics);
	void drawBorder (gcn::Graphics *graphics) {}
	void action(const gcn::ActionEvent& actionEvent);

	void update(Attributes* d);

	void setCiudad(int num, std::string nom);
	void setClase(int num, std::string nom);
	void setRaza(int num, std::string nom);
	void setGenero(int num, std::string nom);
	int getCiudad();
	int getRaza();
	int getClase();
	int getGenero();
	const std::string getNombre();
	void getSkills(Sint8* skills);

private:
	gcn::Image* img;
	gcn::Image* img_clase;

	gcn::TextField* Text_Nombre;

	gcn::DropDown* Combo_Raza;
	guiStringList List_Raza;
	gcn::DropDown* Combo_Genero;
	guiStringList List_Genero;
	gcn::DropDown* Combo_Clase;
	guiStringList List_Clase;
	gcn::DropDown* Combo_Ciudad;
	guiStringList List_Ciudad;

	NoDrawButton* Boton_Volver;
	NoDrawButton* Boton_Continuar;
	NoDrawButton* Boton_Dados;

	gcn::Label* Label_Restantes;
	gcn::Label* Label_Fuerza;
	gcn::Label* Label_Agilidad;
	gcn::Label* Label_Inteligencia;
	gcn::Label* Label_Carisma;
	gcn::Label* Label_Constitucion;

	gcn::Label* Skill[21];
	NoDrawButton* Skill_up[21];
	NoDrawButton* Skill_down[21];

	int lastclase;
	std::string getImageFromClase();
};

#endif

