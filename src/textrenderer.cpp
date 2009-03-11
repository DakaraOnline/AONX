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

#include <iostream>

#include "textrenderer.h"
#include "helpers_graphics.h"

using namespace std;

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
   on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define SDL_rmask 0xff000000
#define SDL_gmask 0x00ff0000
#define SDL_bmask 0x0000ff00
#define SDL_amask 0x000000ff
#else
#define SDL_rmask 0x000000ff
#define SDL_gmask 0x0000ff00
#define SDL_bmask 0x00ff0000
#define SDL_amask 0xff000000
#endif


template <typename T>
static std::string to_string( const T & dd )
{
	std::stringstream x("pixel mode: ");
	x << dd;
	return x.str();
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 */
static Uint32 sdl_getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	// Here p is the address to the pixel we want to retrieve 
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;
		
		default:
			return 0;       // shouldn't happen, but avoids warnings 
	}
}


/*
 * Set the pixel at (x, y) to the given value
 * NOTE: The surface must be locked before calling this!
 */
static void sdl_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			*p = pixel;
			break;

		case 2:
			*(Uint16 *)p = pixel;
			break;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;

		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}

static Uint8 bmp_get_pixel(FT_Bitmap* bitmap, int x, int y) 
{
	Uint8* p = bitmap->buffer + y * bitmap->pitch + x;
	Uint8 c = (255 * (int)*p / (int)bitmap->num_grays);
	return c;
}

static void sdl_draw_bitmap_gray(SDL_Surface *surf, FT_Bitmap* bitmap, int destx, int desty, int destw, int desth)
{
	int x, y;
	Uint8 *p;
		
	if (SDL_MUSTLOCK(surf))
		SDL_LockSurface(surf);

	for (y=0; y < bitmap->rows; y++) {
		p = bitmap->buffer + y * bitmap->pitch;
		for(x=0; x < bitmap->width; x++) {
			Uint8 c = (255 * (int)*p / (int)bitmap->num_grays);
			Uint32 color;
			
			// TRANSPARENT = 0
			color = SDL_MapRGBA(surf->format, 255, 255, 255, c);
			
			sdl_putpixel(surf, destx + x, desty + y, color);
			p++;
		}
	}

	if (SDL_MUSTLOCK(surf))
		SDL_UnlockSurface(surf);
	
}

static void sdl_draw_bitmap_mono(SDL_Surface *surf, FT_Bitmap* bitmap, const int destx, const int desty, const int destw, const int desth)
{
	SDL_Surface *ts = 0, *ts2 = 0;
	SDL_Rect rect;
	SDL_Color colors[2];
	int srcw = bitmap->width, srch = bitmap->rows;
	int x, y;
	Uint32 negro, blanco, transparente;
	Uint32 c;
	Uint8 r, g, b, a;
	
	ts = SDL_CreateRGBSurfaceFrom( bitmap->buffer, srcw, srch, 1, bitmap->pitch, 0, 0, 0, 0);
	if (!ts) 
		goto fin;
	
	ts2 = SDL_CreateRGBSurface( SDL_SWSURFACE, destw, desth, 24, SDL_rmask, SDL_gmask, SDL_bmask, 0);
	if (!ts2) 
		goto fin;
	
	colors[0].r=0;
	colors[0].g=0;
	colors[0].b=0;

	colors[1].r=255;
	colors[1].g=255;
	colors[1].b=255;

	SDL_SetColors(ts, colors, 0, 2);
	
	negro = SDL_MapRGBA(surf->format, 0, 0, 0, 255);
	blanco = SDL_MapRGBA(surf->format, 255, 255, 255, 255);
	transparente = SDL_MapRGBA(surf->format, 0, 0, 0, 0);
	
	// Destino
	rect.x = 1; 
	rect.y = 1;
	
	SDL_BlitSurface( ts, 0, ts2, &rect );

	rect.x = destx;
	rect.y = desty;
	rect.w = destw;
	rect.h = desth;
	
	SDL_FillRect(surf, &rect, transparente);
	
	if (SDL_MUSTLOCK(surf))
		SDL_LockSurface(surf);

	for (y = 0; y < desth; y++) {
		for (x = 0; x < destw; x++) {
			
			// ts2 tiene 24 bits con amask == 0x0.
			
			c = sdl_getpixel(ts2, x, y);
			// SDL_GetRGB(c, ts2->format, &r, &g, &b);
			
			if (c) {
				sdl_putpixel(surf, x + destx, y + desty, blanco);
				
				if (x > 0 && !sdl_getpixel(ts2, x - 1, y))
					sdl_putpixel(surf, x + destx - 1, y + desty, negro);
				if (y > 0 && !sdl_getpixel(ts2, x, y - 1))
					sdl_putpixel(surf, x + destx, y + desty - 1, negro);
				if (x < destw - 1 && !sdl_getpixel(ts2, x + 1, y))
					sdl_putpixel(surf, x + destx + 1, y + desty, negro);
				if (y < desth - 1 && !sdl_getpixel(ts2, x, y + 1))
					sdl_putpixel(surf, x + destx, y + desty + 1, negro);
			}
		}
	}

	if (SDL_MUSTLOCK(surf))
		SDL_UnlockSurface(surf);
	
fin:

	SDL_FreeSurface( ts );
	SDL_FreeSurface( ts2 );
}

TextRenderer::TextRenderer(std::string fontFile, int fontSize)
	: _fontFile(fontFile), _fontSize(fontSize), _library(0), _face(0), _opengl(false),
	  _minChar(numeric_limits<FT_UInt>::max()), _maxChar(numeric_limits<FT_UInt>::min())
{
	init_lib();
	load_font();
	init_char_data();
}

TextRenderer::~TextRenderer()
{
	FT_Done_Face( _face );
	FT_Done_FreeType( _library );
	
	if (_opengl) 
		unload_opengl();
}

void TextRenderer::init_all_char_data() {
	FT_ULong char_code;
	FT_UInt glyph_index;
	
	char_code = FT_Get_First_Char( _face, &glyph_index );
	while ( glyph_index != 0 )
	{
		if (char_code < _charIdx.size())
			init_char(char_code, glyph_index);
		char_code = FT_Get_Next_Char( _face, char_code, &glyph_index );
	}
	init_char(char_code, glyph_index);
}

void TextRenderer::sdl_render_text(SDL_Surface* screen, std::string text, int x, int y)
{
	for (int i=0; i<text.length(); i++)
		sdl_render_char(screen, text[i], &x, &y);
}

void TextRenderer::sdl_render_text(SDL_Surface* screen, std::wstring text, int x, int y)
{
	for (int i=0; i<text.length(); i++)
		sdl_render_char(screen, text[i], &x, &y);
}

void TextRenderer::sdl_render_char(SDL_Surface* screen, FT_ULong c, int * x, int * y)
{
	if (c < _charIdx.size()) {
		FT_UInt idx = _charIdx[c];
		
		if (idx == numeric_limits<FT_UInt>::max()) {
			init_char(c);
			idx = _charIdx[c];
		}
		
		if (idx != numeric_limits<FT_UInt>::max()) {
			CharData &data = _charData[idx];
				
			sdl_render_char_low(screen, c, *x + data.bmp_left, *y - data.bmp_top);
				
			*x += data.advance_x;
			*y += data.advance_y;
		}
	}
}

void TextRenderer::sdl_render_char_low(SDL_Surface* screen, FT_ULong c, int x, int y)
{
	SDL_Rect dst;
	SDL_Rect src;
	
	FT_UInt idx = _charIdx[c];
	CharData &data = _charData[idx];
	BlockData * block = &_blocks[data.block];
	
	dst.x = x;
	dst.y = y;
	dst.w = data.w;
	dst.h = data.h;
	
	src.x = data.x;
	src.y = data.y;
	src.w = data.w;
	src.h = data.h;
	
	SDL_BlitSurface(block->surf, &src, screen, &dst);
}

void TextRenderer::init_lib()
{
	FT_Error error;
	
	error = FT_Init_FreeType( &_library );
	if ( error )
		THROW_TextRendererException("FT_Init_FreeType", error);
}

void TextRenderer::load_font()
{
	FT_Error error;
	
	error = FT_New_Face( _library, _fontFile.c_str(), 0, &_face );
	if ( error )
		THROW_TextRendererException("FT_New_Face", error);
	
	error = FT_Set_Char_Size( _face, 0, _fontSize * 64, 100, 100 ); 
	if ( error ) 
		THROW_TextRendererException("FT_Set_Char_Size", error);
}

void TextRenderer::need_new_block()
{
	_blocks.resize(_blocks.size() + 1);
	_blocks[_blocks.size()-1].init( 256, 256 );
}

void TextRenderer::init_char(FT_ULong charcode, FT_UInt glyph_index)
{
	FT_Error error;
	
	CharData * data = &_charData[glyph_index];
	
	if (charcode < _minChar)
		_minChar = charcode;
	
	if (charcode > _maxChar)
		_maxChar = charcode;
	
	if ( data->block == -1 )
	{
		const int margen = 2;
		
		error = FT_Load_Glyph( _face, glyph_index, FT_LOAD_DEFAULT ); 
		if ( error ) return; 
		
		error = FT_Render_Glyph( _face->glyph, FT_RENDER_MODE_MONO ); // FT_RENDER_MODE_NORMAL );
		if ( error ) {
			// HACK: Algunos caracteres no se renderizan en MONO :s
			error = FT_Render_Glyph( _face->glyph, FT_RENDER_MODE_NORMAL ); // FT_RENDER_MODE_NORMAL );
			if ( error )
				return;
		}
		
		FT_GlyphSlot slot = _face->glyph;
		
		// data->w y data->h indican el tamaño final y en pixeles de la
		// imagen del caracter renderizado.
		data->w = slot->bitmap.width + margen;
		data->h = slot->bitmap.rows + margen;
		
		// " >> 6 " equals " / 64 "
		
		data->advance_x = (slot->advance.x >> 6);
		data->advance_y = (slot->advance.y >> 6);
		
		data->bmp_left = slot->bitmap_left;
		data->bmp_top = slot->bitmap_top;
		
		BlockData * block;
		
		for (;;)
		{
			data->block = _blocks.size()-1;
			block = &_blocks[data->block];
			
			if ( block->get_next_pos( &data->x, &data->y, data->w, data->h ) )
				break;
			
			need_new_block();
		}
		
		switch (slot->bitmap.pixel_mode)
		{
		case FT_PIXEL_MODE_GRAY:
			sdl_draw_bitmap_gray( block->surf, &slot->bitmap, data->x, data->y, data->w, data->h  );
			break;
			
		case FT_PIXEL_MODE_MONO:
			sdl_draw_bitmap_mono( block->surf, &slot->bitmap, data->x, data->y, data->w, data->h );
			break;
		}
	}
	
	_charIdx[charcode] = glyph_index;
}

void TextRenderer::init_char(FT_ULong charcode)
{
	FT_UInt glyph_index;
	FT_Error error;
	
	glyph_index = FT_Get_Char_Index( _face, charcode );
	error = FT_Load_Glyph( _face, glyph_index, FT_LOAD_DEFAULT );
	
	if ( ! error )
		init_char(charcode, glyph_index);
}

void TextRenderer::init_char_data()
{
	_charIdx.resize(64 * 1024, numeric_limits<FT_UInt>::max());
	_charData.resize(_face->num_glyphs);
	
	need_new_block();
}

void TextRenderer::BlockData::init(Uint16 w, Uint16 h)
{
	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
	as expected by OpenGL for textures */
	
	if (this->surf)
		return;
	
	this->font_h = 0;
	
	this->surf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, SDL_rmask, SDL_gmask, SDL_bmask, SDL_amask);
	if ( !this->surf )
		THROW_TextRendererException(
			std::string("SDL_CreateRGBSurface") + std::string(SDL_GetError()), 0);
}

bool TextRenderer::BlockData::get_next_pos(Uint16 * x, Uint16 * y, Uint16 w, Uint16 h)
{
	if ( h > font_h )
		font_h = h;
	
	if ( next_y + font_h >= surf->h )
		return false;
			
	*x = next_x;
	*y = next_y;
			
	next_x += w;
			
	if ( *x + w >= surf->w )
	{
		*x  = 0;
		*y += font_h;
		next_y = *y;
		next_x = w;
		
		font_h = 0;
	}
	
	if ( *y + font_h >= surf->h )
		return false;
			
	return true;
}

void TextRenderer::unload_sdl_surfaces() 
{
	for (int i=0; i<_blocks.size(); i++)
		_blocks[i].freesurf();
}

void TextRenderer::init_opengl()
{
	init_all_char_data();
	
	GLuint cant = (GLuint)(_maxChar - _minChar + 1);
	GLuint i;
	
	_gl_font_blocks.resize(0);
	_gl_font_blocks.resize(_blocks.size());
	
	for (i=0; i<_gl_font_blocks.size(); i++) 
		_gl_font_blocks[i].img = SDL_GL_LoadTexture( _blocks[i].surf, _gl_font_blocks[i].coords );
	
	_gl_font_list = glGenLists((GLuint)cant);
	
	GLfloat coords[4];
	
	for (i=0; i<cant; i++) {
		FT_ULong charcode = (FT_ULong)i + _minChar;
		FT_UInt idx = _charIdx[charcode];
		
		if (idx != numeric_limits<FT_UInt>::max()) {
			CharData &data = _charData[idx];
		
			/*
			sdl_render_char_low(screen, c, *x + data.bmp_left, *y - data.bmp_top);
				
			*x += data.advance_x;
			*y += data.advance_y;
			*/
			
			SDL_GL_convertCoords( coords, data.x, data.y, data.w, data.h, 
					      _gl_font_blocks[data.block].coords, 
					      _blocks[data.block].surf->w, 
					      _blocks[data.block].surf->h );
			
			glNewList (_gl_font_list, GL_COMPILE);
			
			glTranslatef( data.bmp_left, - data.bmp_top, 0.0f );
			SDL_GL_drawImageLow( _gl_font_blocks[data.block].img, coords[0], coords[1], coords[2], coords[3], data.w, data.h, 0, 0 );
			glTranslatef( data.advance_x, data.advance_y, 0.0f );
			
			glEndList ();
		
		}
	}
	
	// Liberar un poco de memoria
	
	unload_sdl_surfaces();
	

}

void TextRenderer::unload_opengl()
{
}

