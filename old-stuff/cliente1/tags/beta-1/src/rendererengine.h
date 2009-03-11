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
#ifndef RENDERERENGINE_H
#define RENDERERENGINE_H

#include "basictypes.h"
#include "class_types.h"

#include "graphicsadapter.h"
#include "imagemanager.h"
#include "guichanloader.h"
#include "inventory.h"
#include <list>
/**
	@author alejandro santos <alejolp@gmail.com>
*/
class RendererEngine
{
public:
	RendererEngine();
	virtual ~RendererEngine();
	
	ga::GraphicsAdapter_ptr getGraphicsAdapter() { return _graphic; }
	ImageManager_ptr getImageManager() { return _imgMan; }
	GuichanLoader_ptr getGuichan() { return _guichan; }
	
	void setMap( ao::MapFile_ptr map );
	
	
	virtual void render( int incX, int incY );
	virtual void beginFrame();
	virtual void endFrame();

	float getFPS() { return _lastFpsCount; }
	
	void initialize( ao::GrhDataFile_ptr grhData, ao::BodyData_ptr bodyData );

protected:
	
	void initializeGA( ga::GraphicsAdapter_ptr graphic ) {
		_graphic = graphic;
	}
	
	void initializeGuichan( GuichanLoader_ptr guichan ) {
		_guichan = guichan;
	}
	
	void renderGrh( ao::GrhDataItem & grhDataItem, Offset basePixel, bool center, bool color_key = true );
	void renderGrh( ao::GrhBasic & grh, Offset basePixel, bool center, bool color_key = true);
	
	void renderLayerTile( int layerNum, ao::MapTile & tile, Offset basePixel, bool center, bool color_key = true );
	void renderObjLayer( ao::MapTile & tile, Offset basePixel, bool center );
	void renderEntityLayer( ao::MapTile & tile, Offset basePixel );
	
	void renderTextos();
	
	virtual void renderTecho( ao::MapTile & tile, Offset basePixel );

protected:
	
	ga::GraphicsAdapter_ptr _graphic;
	ImageManager_ptr _imgMan;
	ao::GrhDataFile_ptr _grhData;
	ao::GrhManager_ptr _grhManager;
	ao::MapFile_ptr _map;
	ao::BodyData_ptr _bodyData;
	GuichanLoader_ptr _guichan;

private:

	void calcularFPS();

	// Variables para el contador de FPS
	int _frameCounter;
	int _last_walk;
	bool _could_walk;
	Uint32 _lastCheck;
	float _lastFpsCount;
	std::string _fps_string;
	class text_to_be_rendered
	{
		public:
			text_to_be_rendered(gcn::ImageFont* _font, std::string _text, ga::Point _donde) :
					font(_font), text(_text), donde(_donde){}
			gcn::ImageFont* font;
			std::string text;
			ga::Point donde;	
	};
	std::list<text_to_be_rendered*> textos;
};

#endif
