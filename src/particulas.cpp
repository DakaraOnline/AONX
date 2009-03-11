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

#include "particulas.h"
#include "inifile.h"
#include "helpers.h"
#include "clienteargentum.h"
#include "imagemanager.h"
#include "graphicsadapter.h"
#include "grhmanager.h"
#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;
using namespace ga;

ListaDatosParticulas DatosParticulas::datos;

template <typename U, typename V>
inline V XtoY(U i)
{
	std::stringstream a;
	a << i;
	V c;
	a >> c;
	return c;
	
}
void DatosParticulas::load_from_file(std::string file)
{
	IniFile my_file(file,true);
	std::cout << "Cargando " << my_file["init"]["total"] << " particulas." << std::endl;
	int numpart = atoi(my_file["init"]["total"].c_str());
	datos.resize(numpart+1);
	for(int i = 1; i <= numpart ; i++)
	{
		std::string ind = XtoY<int,std::string>(i);
	//	std::cout << ind << std::endl;
		datos[i].name = my_file[ind]["name"];
		datos[i].particle_count = XtoY<std::string,int>(my_file[ind]["numofparticles"]);
		datos[i].x1 = XtoY<std::string,int>(my_file[ind]["x1"]);
		datos[i].x2 = XtoY<std::string,int>(my_file[ind]["x2"]);
		datos[i].y1 = XtoY<std::string,int>(my_file[ind]["y1"]);
		datos[i].y2 = XtoY<std::string,int>(my_file[ind]["y2"]);
		datos[i].angle = XtoY<std::string,int>(my_file[ind]["angle"]);
		datos[i].vecx1 = XtoY<std::string,int>(my_file[ind]["vecx1"]);
		datos[i].vecx2 = XtoY<std::string,int>(my_file[ind]["vecx2"]);
		datos[i].vecy1 = XtoY<std::string,int>(my_file[ind]["vecy1"]);
		datos[i].vecy2 = XtoY<std::string,int>(my_file[ind]["vecy2"]);
		datos[i].life1 = XtoY<std::string,int>(my_file[ind]["life1"]);
		datos[i].life2 = XtoY<std::string,int>(my_file[ind]["life2"]);
		datos[i].fric = XtoY<std::string,int>(my_file[ind]["friction"]);
		datos[i].spin = XtoY<std::string,bool>(my_file[ind]["spin"]);
		datos[i].spin_speedL = XtoY<std::string,float>(my_file[ind]["spin_speedl"]);
		datos[i].spin_speedH = XtoY<std::string,float>(my_file[ind]["spin_speedh"]);
		datos[i].grav_strength = XtoY<std::string,int>(my_file[ind]["grav_strength"]);
		datos[i].bounce_strength = XtoY<std::string,int>(my_file[ind]["bounce_strength"]);
		datos[i].alpha_blend = XtoY<std::string,bool>(my_file[ind]["alphablend"]);
		datos[i].gravity = XtoY<std::string,bool>(my_file[ind]["gravity"]);
		datos[i].XMove = XtoY<std::string,bool>(my_file[ind]["xmove"]);
		datos[i].YMove = XtoY<std::string,bool>(my_file[ind]["ymove"]);
		datos[i].move_x1 = XtoY<std::string,int>(my_file[ind]["move_x1"]);
		datos[i].move_x2 = XtoY<std::string,int>(my_file[ind]["move_x2"]);
		datos[i].move_y1 = XtoY<std::string,int>(my_file[ind]["move_y1"]);
		datos[i].move_y2 = XtoY<std::string,int>(my_file[ind]["move_y2"]);
		datos[i].life_counter =  XtoY<std::string,int>(my_file[ind]["life_counter"]);
		datos[i].speed = XtoY<std::string,float>(my_file[ind]["speed"]);
		datos[i].grh_resize = XtoY<std::string,bool>(my_file[ind]["resize"]);
		datos[i].grh_resize_x = XtoY<std::string,int>(my_file[ind]["rx"]);
		datos[i].grh_resize_y = XtoY<std::string,int>(my_file[ind]["ry"]);
		int numgrhs = XtoY<std::string,int>(my_file[ind]["numgrhs"]);
		datos[i].grhs.resize(numgrhs);
		datos[i].grh_index_count = numgrhs;
		std::string grhs_tmp = my_file[ind]["grh_list"];
		std::string::size_type pos;
		while((pos=grhs_tmp.find_first_of(","))!=std::string::npos)
		{
			grhs_tmp.replace(pos,1," ");
		}
		std::stringstream tmps;
		tmps << grhs_tmp;
		for(int j=0;j<numgrhs;j++)
		{
			tmps >> datos[i].grhs[j]; 
		}
		memset(datos[i].rgb_list,0,sizeof(Sint32)*4);
		std::string rgb_tmp;
		for(int j=1;j<5;j++)
		{
			std::string name ="colorset";
			name.append(XtoY<int,std::string>(j));
			rgb_tmp=my_file[ind][name];
			while((pos=rgb_tmp.find_first_of(","))!=std::string::npos)
			{
				rgb_tmp.replace(pos,1," ");
			}
			std::stringstream tmps_rgb;
			tmps_rgb << rgb_tmp;
			int pip;
			for(int k=0;k<3;k++)
			{
				tmps_rgb >> pip;
				datos[i].rgb_list[j-1] += (Sint32)(pip*pow(256.0,k));
			}
			//std::cout << datos[i].rgb_list[j-1] << std::endl;
		}
		
	}
}

DatosParticula* DatosParticulas::get_data(unsigned int num)
{
	if(num<datos.size())
	{
		return &datos[num];
	}else
	{
		return NULL;
	}
}


inline void Particula::restart()
{
	alive_counter = GetRandomNumber(life1,life2);
	x = (float)GetRandomNumber(x1,x2);
	y = (float)GetRandomNumber(y1,y2);
	vector_x = (float)GetRandomNumber(vecx1,vecx2);
	vector_y = (float)GetRandomNumber(vecy1,vecy2);
	angle = (float)DatosParticulas::get_data(index)->angle;
	friction = (float)DatosParticulas::get_data(index)->fric;
}

inline void Particula::check_alive_counter()
{
	alive_counter--;
	if(alive_counter==1)
	{
		restart();
	}
}

inline void Particula::do_physics()
{
	if((last_physics+20)<SDL_GetTicks())
	{
		check_alive_counter();
		last_physics=SDL_GetTicks();
		if(gravity)
		{
			vector_y += grav_strength;
			if(y>0)
				vector_y = (float)bounce_strength;
		}
		if(spin)
		{
			angle += GetRandomNumber((int)spin_speedL,(int)spin_speedH);
			if(angle>=360) 
				angle=0;
		}
		if(XMove) vector_x = (float)GetRandomNumber(move_x1,move_x2);
		if(YMove) vector_y = (float)GetRandomNumber(move_y1,move_y2);
		x += vector_x/friction;
		y += vector_y/friction;
	}
}
Particula::Particula(int _index) : index(_index)
{
	life1 = DatosParticulas::get_data(index)->life1;
	life2 = DatosParticulas::get_data(index)->life2;
	vecx1 = DatosParticulas::get_data(index)->vecx1;
	vecx2 = DatosParticulas::get_data(index)->vecx2;
	vecy1 = DatosParticulas::get_data(index)->vecy1;
	vecy2 = DatosParticulas::get_data(index)->vecy2;
	x1 = DatosParticulas::get_data(index)->x1;
	x2 = DatosParticulas::get_data(index)->x2;
	y1 = DatosParticulas::get_data(index)->y1;
	y2 = DatosParticulas::get_data(index)->y2;
	XMove = DatosParticulas::get_data(index)->XMove;
	YMove = DatosParticulas::get_data(index)->YMove;
	move_x1 = DatosParticulas::get_data(index)->move_x1;
	move_x2 = DatosParticulas::get_data(index)->move_x2;
	move_y1 = DatosParticulas::get_data(index)->move_y1;
	move_y2 = DatosParticulas::get_data(index)->move_y2;
	gravity = DatosParticulas::get_data(index)->gravity;
	spin = DatosParticulas::get_data(index)->spin;
	spin_speedH = DatosParticulas::get_data(index)->spin_speedH;
	spin_speedL = DatosParticulas::get_data(index)->spin_speedL;
	grav_strength = DatosParticulas::get_data(index)->grav_strength;
	bounce_strength = DatosParticulas::get_data(index)->bounce_strength;
	memcpy(rgb_list, DatosParticulas::get_data(index)->rgb_list,sizeof(Sint32)*4);

	alive_counter=2;
	grh.init(DatosParticulas::get_data(index)->grhs[GetRandomNumber(0,DatosParticulas::get_data(index)->grh_index_count-1)]);
	check_alive_counter();
	last_physics=SDL_GetTicks();
}



void Particula::render(int screen_x, int screen_y, GraphicsAdapter_ptr &graphics, ao::GrhManager_ptr &_grhManager, ImageManager_ptr &_imgMan)
{
	do_physics();
	if ( grh.isValid() )
	{
		ao::GrhDataItem & grhDataItem = _grhManager->getNextFrame( grh );
		ga::Image* img = _imgMan->getImage( grhDataItem.fileNum );
		graphics->drawImage( -1,
			img, ga::Rect( grhDataItem.sx, grhDataItem.sy, 
				       grhDataItem.pixelWidth, grhDataItem.pixelHeight ), 
			ga::Point((int)(screen_x + x), (int)(screen_y + y) ), true,127,(int)angle,true, rgb_list);
	}
}

GrupoDeParticulas::GrupoDeParticulas(int _index) : index(_index)
{
	DatosParticula* data = DatosParticulas::get_data(index);
	active = false;
	if(!data)
		return;//TODO: exception? snif.
	particulas.resize(data->particle_count);
	for(ListaParticulas::iterator i = particulas.begin();
		i!=particulas.end();
		i++)
	{
		(*i)= new Particula(index);
	}
	active=true;
}

GrupoDeParticulas::~GrupoDeParticulas()
{
	for(ListaParticulas::iterator i = particulas.begin();
		i!=particulas.end();
		i++)
	{
		delete (*i);
	}
}

void GrupoDeParticulas::render(int screen_x, int screen_y, GraphicsAdapter_ptr &graphics, ao::GrhManager_ptr &_grhManager, ImageManager_ptr &_imgMan)
{
	if(!active) return;
	for(ListaParticulas::iterator i = particulas.begin();
		i!=particulas.end();
		i++)
	{
		(*i)->render(screen_x, screen_y, graphics, _grhManager, _imgMan);
	}
}
