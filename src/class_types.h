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

#ifndef CLASS_TYPES_H
#define CLASS_TYPES_H

#include "linked_ptr.h"

namespace ga
{
	
	class GraphicsAdapter;
	typedef linked_ptr<GraphicsAdapter> GraphicsAdapter_ptr;


	class Image;
	typedef linked_ptr<Image> Image_ptr;

};

class RendererEngine;
typedef linked_ptr<RendererEngine> RendererEngine_ptr;

class RendererEngineSDL;
typedef linked_ptr<RendererEngineSDL> RendererEngineSDL_ptr;

class RendererEngineOGL;
typedef linked_ptr<RendererEngineOGL> RendererEngineOGL_ptr;

class ImageManager;
typedef linked_ptr<ImageManager> ImageManager_ptr;

class GuichanLoader;
typedef linked_ptr<GuichanLoader> GuichanLoader_ptr;

class TextRenderer;
typedef linked_ptr<TextRenderer> TextRenderer_ptr;

namespace ao
{
	
	class GrhDataItem;
	
	class GrhDataFile;
	typedef linked_ptr<GrhDataFile> GrhDataFile_ptr;
	
	class Pos;
	class GrhBasic;
	class MapTile;
	class FxAnim;
	
	class MapFile;
	typedef linked_ptr<MapFile> MapFile_ptr;
	
	class GrhManager;
	typedef linked_ptr<GrhManager> GrhManager_ptr;
	
	class BodyData;
	typedef linked_ptr<BodyData> BodyData_ptr;
	
	/*
	struct BodyData::BasicAnim;
	struct BodyData::BodyAnim;
	struct BodyData::BodyAnim;
	struct BodyData::HeadAnim;
	struct BodyData::WeaponAnim;
	struct BodyData::FxAnim;
	*/
	
	class Entity;
	typedef linked_ptr<Entity> Entity_ptr;
};

#endif


