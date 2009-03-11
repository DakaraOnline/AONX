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

#ifndef _hechizos_h
#define _hechizos_h
#include <SDL.h>
#include <guichan.hpp>

#include <string>
#include <vector>
#include <list>

class Hechizo : public gcn::Button
{
public:
	Hechizo();
	~Hechizo(){}

	void draw(gcn::Graphics * g);

	void setNombre(std::string n){nombre=n;}
	std::string Nombre(){return nombre;}
	void setIndex(unsigned int n) {index=n;}
	unsigned int Index() {return index;}
	void setInvervalo(unsigned int n) {intervalo=n;}
	unsigned int Intervalo() {return intervalo;}
	void actualizaNombre();
	void clearUse() { ultimo_uso = 0; }
	bool usar();

	bool puede_usar();//No relacionado al intervalo, solo si es usable.

private:
	unsigned int index;
	unsigned int ultimo_uso;
	unsigned int intervalo;
	bool actualiza;
	std::string nombre;
};

class Hechizos : public gcn::Window, gcn::ActionListener
{
public:
	Hechizos();
	~Hechizos();
	void init();
	std::vector<Hechizo*> hechis;
	void draw (gcn::Graphics *graphics);
	void drawBorder(gcn::Graphics*){};
	void set_visibility(bool a){ visible=a;}
	bool is_visible() { return visible; }
	void action(const gcn::ActionEvent &actionEvent);
	void updateDisplay(bool suma);
private:
	bool visible;
	gcn::Button *up;
	gcn::Button *down;
	gcn::Image* img;
	int showingFrom;
};

#endif
