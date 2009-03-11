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

#include "rendererengine.h"

#include "graphicsadapter.h"
#include "imagemanager.h"
#include "grhdata.h"
#include "grhmanager.h"
#include "aomap.h"
#include "configdata.h"
#include <sstream>
#include "fonts.h"
#include "bodydata.h"
#include "entity.h"
#include "clienteargentum.h"
#include "console.h"

RendererEngine::RendererEngine()
: _lastFpsCount( 0.0 ), _frameCounter( 0 ), _last_walk( SDL_GetTicks() ), _lastCheck( 0 )
{
}

RendererEngine::~RendererEngine()
{
}

void RendererEngine::initialize( ao::GrhDataFile_ptr grhData, ao::BodyData_ptr bodyData )
{
	_grhData = grhData;
	
	_bodyData = bodyData;
		
	_imgMan = ImageManager_ptr( new ImageManager( _graphic ) );
	
	_grhManager = ao::GrhManager_ptr( new ao::GrhManager( _grhData ) );
	
	
}

void RendererEngine::beginFrame()
{
	_graphic->beginFrame();
}
void RendererEngine::endFrame()
{
	_graphic->endFrame();
	calcularFPS();
}

void RendererEngine::calcularFPS()
{
	// Calcula los FPS
	Uint32 curTime = SDL_GetTicks();
	if ( curTime - _lastCheck > 1000 )
	{
		// Se calcula dividiendo la cantidad de frames dibujados desde el ultimo icheck
		// por el tiempo que paso. Dado que ese tiempo son milisegundos y yo quiero
		// "Frames por Segundo ", multiplico por 1000 arriba (en vez de dividir por 
		// 1000 abajo, que es lo mismo).
		_lastFpsCount = (float)( _frameCounter * 1000 ) / ( curTime - _lastCheck );
		std::stringstream pepe;
		pepe << _lastFpsCount;
		_fps_string = pepe.str();
		// Reinicio el contador de frames junto con el momento del check actual
		_frameCounter = 0;
		_lastCheck = curTime;
		//TODO: esto deber�a estar en el titulo de la consola o texto onscreen.
		//NOTE: lo saque porque me molestaba tanto TANTO.
		//Consola::buffer << "FPS: " << _lastFpsCount << std::endl;
		//std::cout << "FPS: " << _fps_string << std::endl;
	}
	_frameCounter++;
}

void RendererEngine::setMap( ao::MapFile_ptr map )
{
	_map = map;
}

void RendererEngine::renderGrh( ao::GrhDataItem & grhDataItem, Offset basePixel, bool center, bool color_key )
{
	ga::Image_ptr img = _imgMan->getImage( grhDataItem.fileNum , color_key);
	
	if ( center )
	{
		// Santos Calculos Magicos, Batman !!
		basePixel.x -= grhDataItem.pixelWidth / 2 - 16;
		basePixel.y -= grhDataItem.pixelHeight - 32;
	}
	
	_graphic->drawImage( 
			img, ga::Rect( grhDataItem.sx, grhDataItem.sy, 
				       grhDataItem.pixelWidth, grhDataItem.pixelHeight ), 
	ga::Point( basePixel.x, basePixel.y ) );
}

void RendererEngine::renderGrh( ao::GrhBasic & grh, Offset basePixel, bool center, bool color_key )
{
	//
	// Esta funcion se encarga de animar automaticamente el GrhBasic
	//

	if ( grh.isValid() )
	{
		ao::GrhDataItem & grhDataItem = _grhManager->getNextFrame( grh );
		renderGrh( grhDataItem, basePixel, center, color_key );
	}
}

void RendererEngine::renderLayerTile( int layerNum, ao::MapTile & tile, Offset basePixel, bool center, bool color_key)
{
	tile.graphic[layerNum].started=true;
	renderGrh( tile.graphic[layerNum], basePixel, center, color_key );
}

void RendererEngine::renderObjLayer( ao::MapTile & tile, Offset basePixel, bool center )
{
	tile.obj.started=true;
	renderGrh( tile.obj, basePixel, center );
}


#include <list>
#define CHARS_PER_LINE 25
std::list<std::string> wrap(std::string s, int &n)
{
	std::list<std::string> lista;
	lista.clear();
	n=0;
	while(s.length() > CHARS_PER_LINE)
	{
		n++;
		std::string::size_type loc = s.find_first_of(' ',CHARS_PER_LINE);
		if(loc==std::string::npos)
			break;
		lista.push_back(s.substr(0,loc));
		s.erase(0,loc);
	}
	lista.push_back(s);
	return lista;
}

void RendererEngine::renderEntityLayer( ao::MapTile & tile, Offset basePixel )
{
	ao::Entity* ent = tile.ent;
	Offset basePixelHead = basePixel + ent->getHeadOffset();
	
	renderGrh( ent->getBodyGrh(), basePixel+ent->getOffset(), true );
	renderGrh( ent->getHeadGrh(), basePixelHead+ent->getOffset(), true );
	renderGrh( ent->getCascoGrh(), basePixelHead+ent->getOffset(), true );
	renderGrh( ent->getArmaGrh(), basePixel+ent->getOffset(), true );
	renderGrh( ent->getEscudoGrh(), basePixel+ent->getOffset(), true );
	if(!ent->getChat().empty())
	{
		int lines;
		std::list<std::string> texto = wrap(ent->getChat(), lines);
		std::list<std::string>::iterator iter;
		int off = lines*16;
		for(iter = texto.begin();iter != texto.end(); iter++)
		{
			textos.push_back(new text_to_be_rendered(ent->getChatFont(), *iter ,ga::Point(
						basePixelHead.x+ent->getOffset().x+16-((*iter).length()*7/2),
						basePixelHead.y+ent->getOffset().y-off)));
			off-=16;
		}
	}

	_graphic->drawText(Fonts::sans_12_blue(), ent->getNombre(), ga::Point(basePixel.x+ent->getOffset().x+16-(ent->getNombre().size()*7/2),basePixel.y+ent->getOffset().y+32));//TODO: esto apesta, pero buehg.


	if(ent->isMoving()){

		if(_could_walk)
		{
			if(_lastFpsCount<30)
			{
				ent->decOffset(32/4);

			}else if(_lastFpsCount<87)
			{
				ent->decOffset(32/8);

			}else if(_lastFpsCount<200)
			{
				ent->decOffset(32/16);
			}else
			{
				ent->decOffset(32/32);
			}
		}
	}
}

void RendererEngine::renderTecho( ao::MapTile & tile, Offset basePixel )
{
	if(!ClienteArgentum::instancia()->hayTecho())
	{
		renderLayerTile( 3, tile, basePixel, true );
	}
}

/*
void RendererEngine::renderInventory(Inventory &inv){
	int baseX,baseY,actX,actY;
	int colsPerRow;
	//FIXME: hardcoded, testing, alpha beta (??)
	baseX=620;
	baseY=26;

	ga::Image_ptr img = _imgMan->getImage( 30000 );
	_graphic->drawImage( 
			img, ga::Rect( 0, 0, 
				       180, 180 ), 
	ga::Point( 610, 5 ) );

	colsPerRow=5;
	
	for(int i=0 ;i<inv.get_size(); i++){
		if(inv[i]->grhindex>0){
			actX=baseX + (i%colsPerRow) * 32;
			actY=baseY + (i/colsPerRow) * 32;
			renderGrh(_grhData->getGrhData(inv[i]->grhindex),Offset(actX,actY),false);
		}
	}
}
*/

// TODO: Mover esta funcion a otro lado, y sacarle el static 
template<typename T>
static inline T check_bounds( T value, T min, T max )
{
	if ( value < min )
		return min;
	if ( value > max )
		return max;
	return value;
}

void RendererEngine::renderTextos()
{
	_graphic->drawText(Fonts::sans_12_white(),  _fps_string, ga::Point(800-60, 2));
	std::list<std::string> *last_5 = Consola::instancia()->get_last_5();
	std::list<std::string>::iterator iter;
	int i=0;
	for(iter = last_5->begin(); iter != last_5->end(); iter++)
	{
		_graphic->drawText(NULL,  *iter, ga::Point(10, i*14));
		i++;
	}
}

void RendererEngine::render( int incX, int incY )
{
	int x, y;
//	int basePixelX, basePixelY;
	Offset basePixel(0, 0);
	int basePixelX_start, basePixelY_start;
	
	int startX, endX, startY, endY;
	int startX_real, endX_real, startY_real, endY_real;	
	
	int tilesFuera;
	
	// Indica cuantos tiles adicionales se dibujan en las 4 direcciones
	
	tilesFuera = 1;
	
	startX_real = incX - 24/2 - tilesFuera ;
	endX_real = incX + 24/2 + tilesFuera ;
	startY_real = incY - 14/2 - tilesFuera;
	endY_real = incY + 14/2 + tilesFuera;
	
	// Ajusto el rango de tiles a dibujar para que no se vaya de rango
	
	startX = check_bounds( startX_real, ao::MapFile::MapaMinX, ao::MapFile::MapaMaxX );
	endX = check_bounds( endX_real, ao::MapFile::MapaMinX, ao::MapFile::MapaMaxX );
	startY = check_bounds( startY_real, ao::MapFile::MapaMinY, ao::MapFile::MapaMaxY );
	endY = check_bounds( endY_real, ao::MapFile::MapaMinY, ao::MapFile::MapaMaxY );
	
	basePixelX_start = ( -tilesFuera - startX_real + startX ) * 32;
	basePixelX_start -= ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->getOffset().x;

	basePixelY_start = ( -tilesFuera - startY_real + startY ) * 32 ;
	basePixelY_start -= ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->getOffset().y;

	for ( y = startY, basePixel.y = basePixelY_start; y <= endY; y++, basePixel.y += 32 )
	{
		for ( x = startX, basePixel.x = basePixelX_start; x <= endX; x++, basePixel.x += 32 )
		{
			ao::Pos pos( x, y );
			try
			{
				ao::MapTile & tile = _map->getTile( pos );
				
				//
				// Layer 0 :: Pisos
				//
				renderLayerTile( 0, tile, basePixel, false ,false);
				
				if ( tile.graphic[1].isValid() )
				{
					renderLayerTile( 1, tile, basePixel, false );
				}
				
			}
			catch(...)
			{
			}
		}
	}
	


	





	// BEGIN COPY-PASTE Inc. //
	
	int tilesFueraX = 5;
	int tilesFueraY = 7;
	
	startX_real = incX - 24/2 - tilesFueraX;
	endX_real = incX + 24/2 + tilesFueraX;
	startY_real = incY - 14/2 - tilesFueraY+3;
	endY_real = incY + 14/2 + tilesFueraY;
		
	startX = check_bounds( startX_real, ao::MapFile::MapaMinX, ao::MapFile::MapaMaxX );
	endX = check_bounds( endX_real, ao::MapFile::MapaMinX, ao::MapFile::MapaMaxX );
	startY = check_bounds( startY_real, ao::MapFile::MapaMinY, ao::MapFile::MapaMaxY );
	endY = check_bounds( endY_real, ao::MapFile::MapaMinY, ao::MapFile::MapaMaxY );
	
	basePixelX_start = ( -tilesFueraX - startX_real + startX ) * 32;
	basePixelX_start -= ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->getOffset().x;

	basePixelY_start = ( -tilesFueraY - startY_real + startY +3) * 32; 
	basePixelY_start -= ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->getOffset().y;

	// END COPY-PASTE Inc. //
	_could_walk=false;
		int walk_speed = ClienteArgentum::instancia()->getWalkSpeed()-5;
		///NOTE: talvez esto tendria que hacerlo todo el ent, seguro, pero bue.
		///NOTE: la implementacion anterior estaba mas linda pero esta funciona mejor.
	if(_lastFpsCount<30)
	{
		if((SDL_GetTicks()-_last_walk)>=(walk_speed/4))
		{
			_could_walk=true;
			_last_walk=SDL_GetTicks();
		}
	}else if(_lastFpsCount<87)
	{
		if((SDL_GetTicks()-_last_walk)>=(walk_speed/8))
		{
			_could_walk=true;
			_last_walk=SDL_GetTicks();
		}
	}else if(_lastFpsCount<200)
	{
		if((SDL_GetTicks()-_last_walk)>=(walk_speed/16))
		{
			_could_walk=true;
			_last_walk=SDL_GetTicks();
		}
	}else
	{
		if((SDL_GetTicks()-_last_walk)>=(walk_speed/32))
		{
			_could_walk=true;
			_last_walk=SDL_GetTicks();
		}
	}


	for ( y = startY, basePixel.y = basePixelY_start; y <= endY; y++, basePixel.y += 32 )
	{
		for ( x = startX, basePixel.x = basePixelX_start; x <= endX; x++, basePixel.x += 32 )
		{
			ao::Pos pos( x, y );
			try
			{
				ao::MapTile & tile = _map->getTile( pos );

				if ( tile.obj.isValid() )
				{
					renderObjLayer( tile, basePixel, true );
				}

				//
				// Layer 2 :: Carteles, Paredes, etc.
				//
				if ( tile.graphic[2].isValid() )
				{
					renderLayerTile( 2, tile, basePixel, true );
				}
				//
				// Char Layer
				//
				if ( tile.ent )
				{
					renderEntityLayer( tile, basePixel );
				}
				
				
				//
				// Char FX Layer
				//
			}
			catch(...)
			{
			}
		}
	}

	while(!textos.empty())
	{
		text_to_be_rendered *temp_t = textos.back();
		textos.pop_back();
		_graphic->drawText(temp_t->font, temp_t->text, temp_t->donde);
		delete temp_t;
	}

	for ( y = startY, basePixel.y = basePixelY_start; y <= endY; y++, basePixel.y += 32 )
	{
		for ( x = startX, basePixel.x = basePixelX_start; x <= endX; x++, basePixel.x += 32 )
		{
			ao::Pos pos( x, y );
			try
			{
				ao::MapTile & tile = _map->getTile( pos );

				//
				// Layer 3 :: Techos.
				//

				if (tile.graphic[3].isValid())
				{
					renderTecho( tile, basePixel );
				}
				
			}
			catch(...)
			{
			}
		}
	}
	
	renderTextos();
	
}

