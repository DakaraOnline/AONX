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

#ifndef AOMAPTYPES_H
#define AOMAPTYPES_H

#include "SDL.h"


/** 
 @brief Funcion para facilitar la lectura de archivos binarios
 @author Alejandro Santos
 @todo ESTO ACA NO VA !!
 */
template<typename F, typename T>
void bin_read( F & f, T * t )
{
	size_t tam =  sizeof( T );	
	f.read( reinterpret_cast<char*>( t ), tam );
}

// TODO :: Buscar una forma mas portable para la alineacion de structs.

//
// Le indico al compilador que la alineacion de campos en los struct sea
// de un Byte. Sintaxis compatibe con GCC y MSVC++
//
#pragma pack(push, 1)

/*
 * Aca solamente hay structs para leerlos directamente desde un archivo de mapas.
 */

/**
 * @brief Header generico de ciertos archivos 
 * @author alejandro santos <alejolp@gmail.com>
 * @see AoMap_Header, AoGraficosInd_Header
 */
struct Ao_MiCabecera
{
	Sint8   desc[255];
	Sint32  CRC;
	Sint32  MagicWord;
};

/**
 * @brief Header de los archivos de mapas
 * @author alejandro santos <alejolp@gmail.com>
 * @see MapFile
 */
struct AoMap_Header
{
	Sint16           MapVersion;
	Ao_MiCabecera MiCabecera;
	Sint16           tempint[4];
};

/**
 * @brief Header del archivos Graficos.Inc
 * @author alejandro santos <alejolp@gmail.com>
 * @see GrhDataFile
 */
struct AoGraficosInd_Header
{
	Ao_MiCabecera MiCabecera;
	Sint16 tempint[5];
};

/*
Public Type tIndiceCabeza
    Head(1 To 4) As Integer
End Type

Public Type tIndiceCuerpo
    Body(1 To 4) As Integer
    HeadOffsetX As Integer
    HeadOffsetY As Integer
End Type

Public Type tIndiceFx
    Animacion As Integer
    OffsetX As Integer
    OffsetY As Integer
End Type
*/

struct AoIndiceCabeza
{
	Sint16 head[4];	
};

struct AoIndiceCuerpo
{
	Sint16 head[4];
	Sint16 offsetX;
	Sint16 offsetY;	
};

struct AoIndiceFx
{
	Sint16 anim;	
	Sint16 offsetX;
	Sint16 offsetY;	
};

#pragma pack(pop)


#endif

