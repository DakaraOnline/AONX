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

#include <iostream>
#include <string>
#include <sstream>

#include "inifile.h"
#include "configdata.h"

#include "bodydata.h"

namespace ao
{

	void BodyData::BasicAnim::initAll( const Sint16* anims, bool autoStart )
	{
		for (int i=0; i<4; i++ )
			anim[i].init( anims[i], autoStart );
	}
	
	BodyData::BodyData()
	{
	}

	BodyData::~BodyData()
	{
	}


	void BodyData::cargarCabezas( std::string dataFile )
	{
		std::cout << "BodyData::cargasCabezas -> " << dataFile << " ... " << std::endl;
		cargarDataFile<AoIndiceCabeza>( dataFile, &_fileHeaderCabezas, &_numCabezas, &_cabezas );
	}
	
	void BodyData::cargarCuerpos( std::string dataFile )
	{
		std::cout << "BodyData::cargarCuerpos -> " << dataFile << " ... " << std::endl;
		cargarDataFile<AoIndiceCuerpo>( dataFile, &_fileHeaderCuerpos, &_numCuerpos, &_cuerpos );	
	}
	
	void BodyData::cargarCascos( std::string dataFile )
	{
		std::cout << "BodyData::cargarCascos -> " << dataFile << " ... " << std::endl;
		cargarDataFile<AoIndiceCabeza>( dataFile, &_fileHeaderCascos, &_numCascos, &_cascos );
	}
	
	void BodyData::cargarFxs( std::string dataFile )
	{
		std::cout << "BodyData::cargarFxs -> " << dataFile << " ... " << std::endl;
		cargarDataFile<AoIndiceFx>( dataFile, &_fileHeaderFXs, &_numFXs, &_fxs );
	}
	
	template<typename T>
	T convertir( const std::string & str )
	{
		std::istringstream ss( str );
		T x;
		ss >> x;
		return x;
	}
	
	template<typename T>
	std::string convertir( T x )
	{
		std::stringstream ss;
		ss << x;
		return ss.str();
	}
	
	void BodyData::cargarArmas( std::string dataFile )
	{
		/*
		IniFile ff( dataFile, true );
		int i;
		
		_numArmas = convertir<Sint16>( ff["init"]["numarmas"] );

		_armas.clear();
		_armas.resize( _numArmas + 2 );
		
		for ( i = 1; i <= _numArmas; i++ )
		{
			std::string sec = std::string("arma") + convertir(i);
			
			_armas[i].anim[0].init( convertir<Sint16>( ff[sec]["dir1"] ) );
			_armas[i].anim[1].init( convertir<Sint16>( ff[sec]["dir2"] ) );
			_armas[i].anim[2].init( convertir<Sint16>( ff[sec]["dir3"] ) );
			_armas[i].anim[3].init( convertir<Sint16>( ff[sec]["dir4"] ) );
		}
		*/
		std::cout << "BodyData::cargarArmas -> " << dataFile << " ... " << std::endl;
		cargarDataFile<AoIndiceCabeza>( dataFile, &_fileHeaderArmas, &_numArmas, &_armas );
	}
	
	void BodyData::cargarEscudos( std::string dataFile )
	{
		std::cout << "BodyData::cargarEscudos -> " << dataFile << " ... " << std::endl;
		cargarDataFile<AoIndiceCabeza>( dataFile, &_fileHeaderEscudos, &_numEscudos, &_escudos );
	}
	
	void BodyData::loadData()
	{
		std::string home( ConfigData::GetPath("init") );
		
		cargarCabezas( home + "Cabezas.ind" );
		cargarCuerpos( home + "Personajes.ind" );
		cargarFxs( home + "Fxs.ind" );
		cargarCascos( home + "Cascos.ind" );
		cargarArmas( home + "Armas.ind" );
		cargarEscudos( home + "Escudos.ind" );
	}
	
}

