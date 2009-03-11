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

#ifndef particulas_h
#define particulas_h

#include <list>
#include <vector>
#include <string>
#include "SDL.h"
#include "grhdata.h"
#include "class_types.h"
#include "graphicsadapter.h"
#include "helpers.h"

class DatosParticula
{
public:
	int id;
	std::string name;
	float frame_counter;
	float frame_speed;
	unsigned char stream_type;
	int particle_count;
	std::vector<int> grhs;
	int grh_index_count;
	bool alpha_blend;
	int alive_counter;
	bool never_die;
	
	int x1;
	int x2;
	int y1;
	int y2;
	int angle;
	int vecx1;
	int vecx2;
	int vecy1;
	int vecy2;
	int life1;
	int life2;
	int fric;
	float spin_speedL;
	float spin_speedH;
	bool gravity;
	int grav_strength;
	int bounce_strength;
	bool spin;
	bool XMove;
	bool YMove;
	int move_x1;
	int move_x2;
	int move_y1;
	int move_y2;
	Sint32 rgb_list[4];
	float speed;
	int life_counter;
	bool grh_resize;
	int grh_resize_x;
	int grh_resize_y;
};

typedef std::vector<DatosParticula> ListaDatosParticulas;

class DatosParticulas
{
public:
	static void load_from_file(std::string file);
	static DatosParticula* get_data(unsigned int num);
private:
	static ListaDatosParticulas datos;
};

class GrupoDeParticulas;

class Particula
{
public:
	Particula(int _index);
	~Particula(){};
	void render(int screen_x, int screen_y, ga::GraphicsAdapter_ptr &graphics, ao::GrhManager_ptr &_grhManager, ImageManager_ptr &_imgMan);
private:
	inline void do_physics();
	inline void restart();
	inline void check_alive_counter();
	Uint32 last_physics;
	int index;
	float friction;
	float x;
	float y;
	float vector_x;
	float vector_y;
	float angle;
	ao::GrhBasic grh;
	int alive_counter;
	int x1;
	int x2;
	int y1;
	int y2;
	int vecx1;
	int vecx2;
	int vecy1;
	int vecy2;
	int life1;
	int life2;
	int fric;
	float spin_speedL;
	float spin_speedH;
	bool gravity;
	int grav_strength;
	int bounce_strength;
	bool spin;
	bool XMove;
	bool YMove;
	int move_x1;
	int move_x2;
	int move_y1;
	int move_y2;
	Sint32 rgb_list[4];
	bool grh_resize;
	int grh_resizex;
	int grh_resizey;
	Sint32 my_light;
};

typedef std::list<Particula*> ListaParticulas;

class GrupoDeParticulas
{
public:
	GrupoDeParticulas(int _index);
	~GrupoDeParticulas();
	void render(int screen_x, int screen_y, ga::GraphicsAdapter_ptr &graphics, ao::GrhManager_ptr &_grhManager, ImageManager_ptr &_imgMan);
	int getIndex() { return index; }
	bool isActive() { return active; }
	void setActie(bool a) { active = a; }
private:
	int index;
	bool active;
	
	ListaParticulas particulas;
};

#endif

