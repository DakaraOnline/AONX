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
#ifndef AOENTITY_H
#define AOENTITY_H

#define DIALOG_TIMEOUT 12000

#include "basictypes.h"
#include "class_types.h"
#include "bodydata.h"
#include "fxanim.h"
#include "fonts.h"



namespace ao
{

	/**
		@author alejandro santos <alejolp@gmail.com>
	*/
	class Entity
	{
	public:
		enum Heading {
			NORTH = 0,
			EAST,
			SOUTH,
			WEST 
		};
		
		static Pos GetNewPosByDir(const Pos & epos, Heading dir);
		
		Entity(ao::MapFile_ptr map, const Pos & epos, Heading dir );
		~Entity();

		bool moveDir(Heading dir, bool checkBlock);

		void movePos(const Pos & epos);

		bool setPos(const Pos & epos, bool usermove = false);
		
		void loadData( BodyData_ptr bodyData, int a, int b, int c, int d, int e );
		
		const Pos & getPos() const { return _pos; }
		Heading getHeading() const { return _heading; }
		void setHeading(Heading heading) { _heading=heading; }
		Offset getHeadOffset() { return body.headOffset; }
		Offset getOffset() { return Offset(ox,oy); }

		void decOffset(int howmuch);

		GrhBasic & getBodyGrh() { return body.anim[_heading]; }
		GrhBasic & getHeadGrh() { return head.anim[_heading]; }
		GrhBasic & getCascoGrh() { return casco.anim[_heading]; }
		GrhBasic & getArmaGrh() { return arma.anim[_heading]; }
		GrhBasic & getEscudoGrh() { return escudo.anim[_heading]; }
		
		bool isMoving() { return moving; }

		const int getLastMov(){ return lastmov; }
		void removeFromMap();// Antes era privada

		void setNombre(std::string s) { nombre=s; }
		void setChat(std::string c);
		void setChatFont(gcn::ImageFont* font) { chat_font=font; }
		
		std::string getNombre() { return nombre; }
		std::string getChat();
		gcn::ImageFont* getChatFont() { return chat_font; }

	private:
		
		void startMoving();
		void stopMoving();

		Heading _heading;
		Pos _pos;
		ao::MapFile_ptr _map;
		
		BodyData::BodyAnim body;
		BodyData::HeadAnim head;
		BodyData::HeadAnim casco;
		BodyData::WeaponAnim arma;
		BodyData::BasicAnim escudo;
		
		bool usandoArma;

		bool moving;

		int ox,oy;
		
		int tempoff;

		int lastmov;

		FxAnim fx;

		std::string nombre;

		std::string chat;

		int chat_time;

		gcn::ImageFont* chat_font;
	};

}

#endif
