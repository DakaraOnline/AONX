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

#include <iostream>
#include <exception>
#include <fstream>

#include "grhdata.h"

namespace ao
{
	
	void GrhBasic::init( Sint16 _index , bool autoStart ) 
	{
		// TODO Aca hace falta algo mas que solo esto...
		index = _index;
		
		if ( autoStart )
			start();
	}
	
	void GrhBasic::start()
	{
		started = 1;
		frame = 0;
	}
	
	void GrhBasic::stop()
	{
		started = 0;
		frame = 0;
	}
	

	GrhDataFile::GrhDataFile()
	// TODO HARD CODED !
	: _grhs( 50000 )
	{
	}

	GrhDataFile::~GrhDataFile()
	{
	}


#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	// TODO : Los archivos de datos son LITTLE ENDIAN
#error TODO : Aun sin implementar !! Los archivos de datos son LITTLE ENDIAN
#endif

	void GrhDataFile::loadData( std::string dataFile )
	{
		//
		// f.read( reinterpret_cast<char*>( & _fileHeader ), sizeof( Ao_MiCabecera ) );
		//
		std::cout << "GrhDataFile::loadData -> " << dataFile << " ... " << std::endl;
		
		std::ifstream f;
		
		f.exceptions(std::ios::eofbit);
		f.open(dataFile.c_str(), std::ios::binary | std::ios::in);

		Sint16 tmpInt16, grhNum;
		int n;
		
		// Leo el header
		bin_read( f, &_fileHeader );
		
		// GrhNum
		// f.read( reinterpret_cast<char*>( & grhNum ), sizeof( Sint16 ) );
		bin_read( f, &grhNum );
		
		while ( grhNum > 0 )
		{
			GrhDataItem & item = getGrhData( grhNum );
			
			// cantidad de frames en la animacion del GRH
			bin_read( f, & item.numFrames );
			
			// me fijo si es un valor valido
			if ( item.numFrames <= 0 )
				throw std::exception();
			
			// 
			if ( item.numFrames > 1 )
			{
				for ( n = 0; n < item.numFrames; n++ )
					bin_read( f, & item.frames[n] );
				
				bin_read( f, & item.speed );
				
				item.pixelWidth = getGrhData( item.frames[0] ).pixelWidth;
				item.pixelHeight = getGrhData( item.frames[0] ).pixelHeight;
				item.tileWidth = getGrhData( item.frames[0] ).tileWidth;
				item.tileHeight = getGrhData( item.frames[0] ).tileHeight;
			}
			else
			{
				bin_read( f, & item.fileNum );
				bin_read( f, & item.sx );
				bin_read( f, & item.sy );
				bin_read( f, & item.pixelWidth );
				bin_read( f, & item.pixelHeight );
				
				// TODO Constante Hard coded
				item.tileWidth = item.pixelWidth / 32;
				item.tileHeight = item.pixelHeight / 32;
				
				item.frames[0] = grhNum;
				item.myID = grhNum;
			}
			
			if ( f.eof() )
				break;
			
			//
			// TODO : ESTO ES UN ESPANTO
			//
			// lamentablemente no encuentro otra forma de hacerlo funcionar.
			// --alejo
			//
			try
			{
				bin_read( f, &grhNum );
			}
			catch ( std::ios::failure ex )
			{
				break;
			}
		}
	}
	
}

