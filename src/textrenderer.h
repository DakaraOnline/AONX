/***************************************************************************
 *   Copyright (C) 2006 by Esteban Torren, Alejandro Santos                *
 *   esteban.torre@gmail.com alejolp@gmail.com                             *
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

#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <stdlib.h>

#include "SDL.h"

#include "helpers_graphics.h"


#define THROW_TextRendererException(a, b) throw TextRendererException((a), (b))


/**
	@author alejo <alejolp@alejolp.com>
*/
class TextRenderer
{
public:


	class TextRendererException : public std::exception
	{
	public:
		TextRendererException(std::string w, FT_Error e) : _what(w), _error(e) {}
		virtual ~TextRendererException() throw() {}

		virtual const char* what() { return _what.c_str(); }
	private:
		std::string _what;
		FT_Error _error;
	};

	TextRenderer(std::string fontFile, int fontSize);

	~TextRenderer();
	
	const FT_Face get_ft_face() const {
		return _face;
	}
	
	int get_font_size() const {
		return _fontSize;
	}
	
	void init_all_char_data();
	
	void sdl_render_text(SDL_Surface* screen, std::string text, int x, int y);
	
	void sdl_render_text(SDL_Surface* screen, std::wstring text, int x, int y);
	
	void sdl_render_char(SDL_Surface* screen, FT_ULong c, int * x, int * y);
	
	void sdl_render_char_low(SDL_Surface* screen, FT_ULong c, int x, int y);
	
	void init_opengl();
	
private:
	
	void init_lib();
	
	void load_font();
	
	void need_new_block();
		
	void init_char(FT_ULong charcode, FT_UInt glyph_index);
	
	void init_char(FT_ULong charcode);
	
	void init_char_data();
	
	void unload_sdl_surfaces();
	void unload_opengl();
	
	
	struct CharData;
	struct BlockData;
	
	struct CharData
	{
		CharData() 
			: block(-1), x(0), y(0), w(0), h(0),
			advance_x(0), advance_y(0),
			bmp_left(0), bmp_top(0)
		{
		}
		
		Sint16 block;
		Uint16 x, y;
		Uint16 w, h;
		
		Sint16 bmp_left;
		Sint16 bmp_top;
		
		Uint16 advance_x, advance_y;
	};
	
	struct BlockData
	{
		BlockData()
			: surf(0), next_x(0), next_y(0), font_h(0)
		{
		}
		
		~BlockData() 
		{
			freesurf();
		}
		
		void init(Uint16 w, Uint16 h);
		
		bool get_next_pos(Uint16 * x, Uint16 * y, Uint16 w, Uint16 h);
		
		void freesurf() {
			if (surf) {
				SDL_FreeSurface(surf);
				surf = 0;
			}
		}
		
		SDL_Surface* surf;
		int next_x, next_y;
		int font_h;
	};
	
	std::string _fontFile;
	int _fontSize;
	FT_Library _library;
	FT_Face _face;
	
	std::vector<FT_UInt> _charIdx;
	std::vector<CharData> _charData;
	std::vector<BlockData> _blocks;

	// OpenGL
	
	bool _opengl;
	GLuint _gl_font_list;
	
	FT_UInt _minChar;
	FT_UInt _maxChar;
	
	struct GLBlockData {
		GLBlockData() : img(0) { 
			coords[0] = 0; 
			coords[1] = 0; 
			coords[2] = 0; 
			coords[3] = 0; 
		}
		
		GLuint img;
		GLfloat coords[4];
	};
	
	std::vector<GLBlockData> _gl_font_blocks;
};

#endif

