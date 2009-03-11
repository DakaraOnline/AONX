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
#ifndef AOBODYDATA_H
#define AOBODYDATA_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <fstream>

#include "SDL.h"
#include "file_types.h"
#include "basictypes.h"
#include "grhdata.h"


namespace ao
{
	/*
'Lista de cuerpos
Public Type BodyData
    Walk(1 To 4) As Grh
    HeadOffset As Position
End Type

'Lista de cabezas
Public Type HeadData
    Head(1 To 4) As Grh
End Type

'Lista de las animaciones de las armas
Type WeaponAnimData
    WeaponWalk(1 To 4) As Grh
    '[ANIM ATAK]
    WeaponAttack As Byte
End Type

'Lista de las animaciones de los escudos
Type ShieldAnimData
    ShieldWalk(1 To 4) As Grh
End Type

'Lista de cuerpos
Public Type FxData
    Fx As Grh
    OffsetX As Long
    OffsetY As Long
End Type
	*/

	/**
		@author alejandro santos <alejolp@gmail.com>
	*/
	class BodyData
	{
	public:
				
		struct BasicAnim
		{
			GrhBasic anim[4];
			
		protected:
			void initAll( const Sint16* anims, bool autoStart = false );
		};
		
		struct BodyAnim : public BasicAnim
		{
			Offset headOffset;
			
			void init( AoIndiceCuerpo & cuerpo ) {
				initAll( cuerpo.head );
				headOffset.x = cuerpo.offsetX;
				headOffset.y = cuerpo.offsetY;
			}
		};
		
		struct HeadAnim : public BasicAnim
		{
			void init( AoIndiceCabeza & cabeza ) {
				initAll( cabeza.head );
			}
		};
		
		struct WeaponAnim : public BasicAnim
		{
			Sint8 attack;
			void init( AoIndiceCabeza & cabeza ) {
				initAll( cabeza.head );
				attack = 0;
			}
		};
		
		struct FxAnim 
		{
			// el FX No tiene Heading!
			GrhBasic anim;
			
			Offset offset;
			
			void init( AoIndiceFx & fx ) {
				anim.init( fx.anim );
				offset.x = fx.offsetX;
				offset.y = fx.offsetY;
			}
		};
		
		
	public:
		BodyData();
		~BodyData();

		void loadData();

	private:
		template <typename T, typename U, typename V>
		void cargarDataFile( std::string dataFile, U* header, Sint16* cantidad, V* elementos )
		{
			std::ifstream f;
			int i;
		
			f.exceptions( std::ios::eofbit | std::ios::failbit | std::ios::badbit );
			f.open( dataFile.c_str(), std::ios::binary | std::ios::in );

			bin_read( f, header );
		
			bin_read( f, cantidad );
		
			elementos->clear();
			elementos->resize( *cantidad );
		
			try
			{
				for ( i=0; i < *cantidad; i++ )
				{
					T registro;
				
					bin_read( f, & registro );
				
				// _cabezas[i].anim[0].init(cabeza.head[0]);
					(*elementos)[i].init( registro );
				}
			}
			catch(...)
			{
				*cantidad = i;
				elementos->resize( *cantidad );
			}
		}
		
		void cargarCabezas( std::string dataFile );
		void cargarCuerpos( std::string dataFile );
		void cargarCascos( std::string dataFile );
		void cargarFxs( std::string dataFile );
		void cargarArmas( std::string dataFile );
		void cargarEscudos( std::string dataFile );
		
		Ao_MiCabecera _fileHeaderCabezas;
		Ao_MiCabecera _fileHeaderCuerpos;
		Ao_MiCabecera _fileHeaderCascos;
		Ao_MiCabecera _fileHeaderFXs;
		Ao_MiCabecera _fileHeaderArmas;
		Ao_MiCabecera _fileHeaderEscudos;
		
		Sint16 _numCabezas;
		Sint16 _numCuerpos;
		Sint16 _numCascos;
		Sint16 _numFXs;
		Sint16 _numArmas;
		Sint16 _numEscudos;
		
	public:
		std::vector<HeadAnim> _cabezas;
		std::vector<BodyAnim> _cuerpos;
		std::vector<HeadAnim> _cascos;
		std::vector<FxAnim> _fxs;
		std::vector<WeaponAnim> _armas;
		std::vector<HeadAnim> _escudos;
		
	};

}

#endif
