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
#ifndef AOFXANIM_H
#define AOFXANIM_H

#include "class_types.h"

namespace ao
{

	/**
		@author alejandro santos <alejolp@gmail.com>
	*/
	class FxAnim
	{
	public:
		FxAnim() 
		{}

		~FxAnim()
		{}
		
		void init( int fx, int fxLoopTimes )
		{
			_fx = fx;
			_fxLoopTimes = fxLoopTimes;
		}

	private:
		int _fx;
		int _fxLoopTimes;
		
	};

}

#endif
