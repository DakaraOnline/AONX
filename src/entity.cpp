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

#include "entity.h"

#include "aomap.h"

namespace ao
{


	Entity::Entity(ao::MapFile_ptr map, const Pos & epos, Heading dir)
		: moving(false),ox(0),oy(0),tempoff(0),_heading(dir), _map(map),  _pos(epos), usandoArma(false)
	{
		setPos(epos);
	}
	
	Entity::~Entity()
	{
		removeFromMap();
	}

	void Entity::startMoving(){
		stopMoving();
		lastmov=SDL_GetTicks();

		moving=true;

		getBodyGrh().start();
		getArmaGrh().start();
		getCascoGrh().start();
		getHeadGrh().start();
		getEscudoGrh().start();

		switch(_heading){
			case WEST:
				ox=32;
				break;
			case EAST:
				ox=-32;
				break;
			case NORTH:
				oy=32;
				break;
			case SOUTH:
				oy=-32;
				break;
		}
	}

	void Entity::decOffset(int _howmuch)
	{
		lastmov=SDL_GetTicks();

		int howmuch = _howmuch;

		if(ox>0){
			ox-=howmuch;
			if(ox<=0){
				stopMoving();
			}
		}else if(ox<0){
			ox+=howmuch;
			if(ox>=0){
				stopMoving();
			}
		}

		if(oy>0){
			oy-=howmuch;
			if(oy<=0){
				stopMoving();
			}
		}else if(oy<0){
			oy+=howmuch;
			if(oy>=0){
				stopMoving();
			}
		}
	}

	void Entity::stopMoving(){
		ox=oy=0;
		moving=false;
		tempoff=0;
		getBodyGrh().stop();
		getArmaGrh().stop();
		getCascoGrh().stop();
		getHeadGrh().stop();
		getEscudoGrh().stop();
	}

	Pos Entity::GetNewPosByDir(const Pos & epos, Heading dir)
	{
		switch(dir)
		{
			case NORTH:
				return Pos(epos.x, epos.y - 1);
				break;
			case EAST:
				return Pos(epos.x + 1, epos.y);
				break;
			case SOUTH:
				return Pos(epos.x, epos.y + 1);
				break;
			case WEST:
				return Pos(epos.x - 1, epos.y);
				break;
		}
		return epos;
	}
	
	void Entity::loadData( BodyData_ptr bodyData, int a, int b, int c, int d, int e )
	{
		if(a>=0) body = bodyData->_cuerpos[a];
		if(b>=0) head = bodyData->_cabezas[b];
		if(c>=0){
			casco = bodyData->_cascos[c];
		}else{
			casco.anim[0].index=0;
			casco.anim[1].index=0;
			casco.anim[2].index=0;
			casco.anim[3].index=0;
		}
		if(d>=0)
		{
			arma = bodyData->_armas[d];
		}else{
			arma.anim[0].index=0;
			arma.anim[1].index=0;
			arma.anim[2].index=0;
			arma.anim[3].index=0;
		}
		if(e>=0){
			escudo = bodyData->_escudos[e];
		}else{
			escudo.anim[0].index=0;
			escudo.anim[1].index=0;
			escudo.anim[2].index=0;
			escudo.anim[3].index=0;
		}
	}
	
	bool Entity::moveDir(Heading dir, bool checkBlock)
	{

		_heading=dir;

		if(!setPos(GetNewPosByDir( _pos, dir ) , checkBlock)) return false; 

		startMoving();

		return true;
	}

	void Entity::movePos(const Pos & epos)
	{
		int h,v;

		h=epos.x-_pos.x;
		v=epos.y-_pos.y;

		setPos(epos);

		if(h<0){
			_heading=WEST;
		}else if(h>0){
			_heading=EAST;
		}
		if(v<0){
			_heading=NORTH;
		}else if(v>0){
			_heading=SOUTH;
		}

		startMoving();
	}
	
	void Entity::removeFromMap()
	{
		if ( ao::MapFile::IsValidPos(_pos) )
		{
			ao::MapTile & oldTile = _map->getTile(_pos);
			
			if ( oldTile.ent == this )
				oldTile.ent = 0;
		}
	}
	
	bool Entity::setPos(const Pos & epos, bool usermove)
	{
		if ( ! ao::MapFile::IsValidPos(epos) )
			return false;

		ao::MapTile & newTile = _map->getTile(epos);

		// TODO: check water/navigating
		if ((usermove)&&((newTile.ent>0)||(newTile.blocked))) return false;

		removeFromMap();
		
		newTile.ent = this;
		
		_pos = epos;

		return true;
	}
	void Entity::setChat(std::string c)
	{
		chat=c;
		chat_time=SDL_GetTicks();
	}

	std::string Entity::getChat() 
	{ 
		if((chat_time+DIALOG_TIMEOUT)<SDL_GetTicks())
		{
			return "";
		}
		return chat;
	}
}


