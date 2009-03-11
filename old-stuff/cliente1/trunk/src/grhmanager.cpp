/***************************************************************************
 *   Copyright (C) 2006 by alejandro santos   *
 *   alejolp@gmail.com   *
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

#include "grhmanager.h"
#include "grhdata.h"
#include "aomap.h"

namespace ao
{

	GrhManager::GrhManager(  GrhDataFile_ptr grhData )
	: _grhData( grhData )
	{
	}


	GrhManager::~GrhManager()
	{
	}


	GrhDataItem & GrhManager::getNextFrame( GrhBasic & grh )
	{
		int iGrhIndex = grh.index;
		ao::GrhDataItem * grhDataItem = & _grhData->getGrhData( iGrhIndex );
		
		// Me fijo si es una animacion
		if ( grhDataItem->numFrames > 1 )
		{
			// Obtiene el siguiente frame e incrementa el contador
			iGrhIndex = grhDataItem->frames[ grh.frame ];
			
			if (( grh.started )&&((grh.ticks+ANIM_SPEED)<SDL_GetTicks()))
			{
				grh.ticks = SDL_GetTicks();
				grh.frame++;
				// Se acabo la animacion ? Reinicio
				if ( grh.frame >= grhDataItem->numFrames )
				{
					grh.frame = 0;
					if(grh.looptimes>0)
					{
						grh.looptimes--;
						if(grh.looptimes==0)
							grh.stop();
					}
					
				}
			}
			
			// Obtengo el GrhDataItem
			grhDataItem = & _grhData->getGrhData( iGrhIndex );
		}
		
		return *grhDataItem;
	}
	
}
