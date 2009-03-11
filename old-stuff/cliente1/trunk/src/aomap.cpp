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

#include <fstream>

#include "aomap.h"
#include "imagemanager.h"
#include "grhmanager.h"

namespace ao 
{
		
	MapFile::MapFile()
	: _tiles(AnchoMapa * AltoMapa)
	{}
	
	
	MapFile::~MapFile()
	{}
	
	#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	// TODO : Los archivos de mapas son LITTLE ENDIAN
	#error TODO : Aun sin implementar !! Los archivos de mapas son LITTLE ENDIAN
	#endif
	
	void MapFile::loadMapFile( std::string mapFile, ao::GrhManager_ptr grhmgr, ImageManager_ptr imgmgr)
	{
		std::ifstream f;
		
		f.exceptions(std::ios::failbit | std::ios::badbit | std::ios::eofbit);
		f.open(mapFile.c_str(), std::ios::binary | std::ios::in);
		
		Sint8 bFlags;
		Sint16 tmpInt;
		
		int x, y, k;
		
		// Header
		bin_read( f, & _mapHeader );
		
		for ( y = MapaMinY; y <= MapaMaxY; y++ )
		{
			for ( x = MapaMinX; x <= MapaMaxX; x++ )
			{
				
				MapTile & tile = getTile( Pos( x, y ) );
				//Piluex TODO: verificar, CLEANUP. =).
				tile.ent=NULL;
				tile.obj.index=0;
				// /Piluex

				// f.read( reinterpret_cast<char*>( & bFlags ), sizeof( bFlags ) );
				bin_read( f, & bFlags );
				
				// Tile Blocked ?
				tile.blocked = bool( bFlags & 1 );
				
				// Primer Layer
				bin_read( f, & tmpInt );
				tile.graphic[0].init(tmpInt);
				
				// GRAPHICS
				for ( k = 1; k < 4; k++ )
				{
					if ( bFlags & (1 << k) ) {
						bin_read( f, & tmpInt );
						tile.graphic[k].init(tmpInt);
						//TODO FIXME : primer intento de precarga de graficos.
						imgmgr->getImage(grhmgr->getNextFrame(tile.graphic[k]).fileNum);
					} else {
						tile.graphic[k].init(0);
					}
				}
				
				// Trigger
				if ( bFlags & 16 )
					bin_read( f, & tile.trigger );
				else
					tile.trigger = 0;
			}
		}
	}
};

