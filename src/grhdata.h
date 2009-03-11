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
#ifndef AOGRHDATA_H
#define AOGRHDATA_H

#include <vector>
#include <string>

#include "SDL.h"
#include "file_types.h"
#pragma warning (disable : 4800 )

namespace ao
{
	
	/**
	@brief Un "Grh" es una cosa rara que nadie sabe bien que significa
	@author alejandro santos <alejolp@gmail.com>
	
	Un GrhBasic intenta representar una instancia de una animacion de graficos. Aqui
	se guarda el numero de GrhDataItem, el numero de frame siguiente y si la animacion
	ya inicio. Esto es asi para que las animaciones que el Engine dibuja sean 
	independientes aun cuando se dibuja el mismo grafico. 
	
	Ejemplos de Grh animados son el Agua y Efectos FX como la meditacion.
	
	 */
	class GrhBasic
	{
		public:
			GrhBasic() 
			: index(0), frame(0), speed(0), started(0), ticks(0),looptimes(0) 
			{}
		
			void init( Sint16 _index, bool autoStart = false );
			void start();
			void stop();
			inline bool isValid()
			{
				return bool(index);
			}
			
			//PILUEX SEEME TODO VER BIEN 
			int ticks;
			Sint16 index;
			Sint8 frame, speed, started;
			Sint8 looptimes;
	};
	
/*
	Public Type GrhData
	sX As Integer
	sY As Integer
	FileNum As Integer
	pixelWidth As Integer
	pixelHeight As Integer
	TileWidth As Single
	TileHeight As Single
    
	NumFrames As Integer
	Frames(1 To 25) As Integer
	Speed As Integer
	End Type
*/

	/**
	@brief Guarda informacion de un GrhDataItem. Ver %GrhDataFile
	@author alejandro santos <alejolp@gmail.com>
	
	Un GrhDataItem representa una animacion de un GrhBasic, a partir de un
	grafico y coordenadas de origen de ese grafico, ya sea de un solo frame
	o de varios frames animados.
	
	Existen dos clases de GrhDataItem. El primero es un grafico de un solo frame
	en el cual numFrames == 1. En este caso el vector frames como primer elemento
	posee el numero de GrhDataItem de si mismo. El segundo caso es cuando 
	numFrames > 1, en donde en cada uno de los elementos del vector frames se 
	encuentran los numeros de cada uno de los frames de la animacion, donde ese 
	numero es un GrhDataItem.
	
	La clase GrhManager se encarga de administrar los GrhBasic y reproducir las 
	animaciones de los graficos. 
	
	 */
	class GrhDataItem
	{
	public:
		GrhDataItem()
		: sx(0), sy(0), fileNum(0), pixelWidth(0), 
		  pixelHeight(0), centerTweakx(-1), centerTweaky(-1), tileWidth(0), tileHeight(0), 
		  numFrames(0), speed(0)
		{}
		
		/// Coordenada X de origen de la imagen
		Sint16 sx;
		
		/// Coordenada Y de origen de la imagen
		Sint16 sy;
		
		/// Numero de archivo de imagen
		Sint16 fileNum;
		
		/// Ancho de la imagen en pixeles
		Sint16 pixelWidth;

		int centerTweakx;
		int centerTweaky;
		int myID;
		
		/// Alto de la imagen en pixeles
		Sint16 pixelHeight;
		
		/// Valor temporal que se calcula: tileWidth = pixelWidth / 32
		Sint16 tileWidth;
		
		/// Valor temporal que se calcula: tileHeight = pixelHeight / 32
		Sint16 tileHeight;
		
		/// Cantidad de frames de la animacion
		Sint16 numFrames;
		
		/// Velocidad de la animacion
		Sint16 speed;
		
		/// Vector de cada uno de los numeros de los distintos GrhDataItem (frames) de la animacion
		Sint16 frames[25];
	};
	
	
	/**
	@brief Clase para cargar el archivo Graficos.ind. Ver %GrhDataItem
	@author alejandro santos <alejolp@gmail.com>
	*/
	class GrhDataFile
	{
	public:
		GrhDataFile();

		~GrhDataFile();

		/// Carga el archivo Graficos.ind
		void loadData( std::string dataFile );
		
		/// Devuelve un %GrhDataItem
		GrhDataItem & getGrhData( int num ) {
			return _grhs[num - 1];
		}
		
	private:
		
		AoGraficosInd_Header _fileHeader;
		
		std::vector<GrhDataItem> _grhs;
	};

}

#endif
