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
#ifndef AOMAP_H
#define AOMAP_H

#include <vector>
#include <string>

#include "class_types.h"
#include "file_types.h"
#include "grhdata.h"
#include "basictypes.h"

namespace ao 
{
	
	/**
	@page spec_file_map Especificacion de formatos de mapas
	
	El formato de los archivos de mapas consta de un Header (AoMap_Header) y a continuacion 
	10000 registros logicos (100 ancho x 100 alto son las dimensiones de todos los mapas)
	representando cada tile del mapa, una fila a continuacion de la otra. Primero se define la primer 
	fila, luego la segunda, etc. De cada fila, primero viene el tile de  la primer columna (mas 
	a la izquierda), luego de la segunda columna, etc. El formato de los datos se encuentra en binario
	little-endian.
	
	Los registros logicos por motivos de aprovechamiento de espacio constan cada uno de un byte
	de flags donde cada bit se utiliza para indicar si se encuentran presentes cada uno de los campos
	de informacion del tile actual. El byte de flags consta de los siguientes bits:
	
	- Bit 0: Indica si el tile esta bloqueado (1) o no (0)
	- Bit 1 - Bit 3: Indica si existen las layers 2 a 4, respectivamente por cada bit
	- Bit 4: Indica si hay un trigger en el tile
	
	El Bit 0 es el menos significativo del Byte.
	
	Luego viene un integer de 2 bytes (Sint16) en el cual se encuentra el numero de Grh (GrhDataItem)
	de la primer layer: el piso.
	
	Luego, si el Bit 1 del flag esta en 1, se encuentra el numero de Grh (tambien Sint16) de la segunda layer: segunda 
	capa del piso. Lo mismo ocurre con los Bits 2 y 3.
	
	Luego, si el Bit 4 esta en 1, viene el numero de Trigger (Sint16).
	
	 */

	
	
	
	/**
	@brief Un tile de un mapa
	@author alejandro santos <alejolp@gmail.com>
	 */
	class MapTile 
	{
	public:
		MapTile() 
		: blocked(false), trigger(0), ent(0)
		{}
		
		// Indica si puedo posicionarme en este tile
		bool blocked;
		
		// Trigger del tile: normal, lluvia, etc.
		Sint16 trigger;
		
		// Las 4 layers
		GrhBasic graphic[4];
		
		// El Objeto a dibujar
		GrhBasic obj;
		
		// Algun character en el tile ?
		Entity* ent;
	};
	
	/**
		@brief Clase para manejar mapas
		@author alejandro santos <alejolp@gmail.com>
	*/
	class MapFile
	{
	public:
		static const int AnchoMapa = 100;
		static const int AltoMapa = 100;
		
		static const int MapaMinX = 0;
		static const int MapaMaxX = AnchoMapa - 1;
		
		static const int MapaMinY = 0;
		static const int MapaMaxY = AltoMapa - 1;

		static bool IsValidPos( const Pos & p ) 
		{
			if ( /* p.x < MapaMinX || */ p.x > MapaMaxX )
				return false;
			if ( /* p.y < MapaMinY || */ p.y > MapaMaxY )
				return false;
			return true;
		}
		
		MapFile();
		~MapFile();
	
		/// Abre un nuevo mapa (nuevo formato compacto 0.11)
		void loadMapFile( std::string mapFile , ao::GrhManager_ptr grhmgr, ImageManager_ptr imgmgr);
		
		/**
		@brief Devuelve un tile del mapa
		*/
		inline MapTile & getTile( const Pos & wp ) {
			return _tiles[ (wp.y) * AnchoMapa + wp.x ];
		}
	private:
		
		
		/// No sirve para nada pero igual lo guardo.
		AoMap_Header _mapHeader;
		
		std::vector<MapTile> _tiles;
	};

};

#endif
