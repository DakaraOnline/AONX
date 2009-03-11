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


#include "helpers_graphics.h"


/* Quick utility function for texture creation */
int power_of_two(int input)
{
	int value = 1;

	while (value < input) {
		value <<= 1;
	}
	return value;
}

/* Funcion extraida del archivo testgl.c de la distribucion de SDL */
GLuint SDL_GL_LoadTexture(SDL_Surface * surface, GLfloat * texcoord)
{
	GLuint texture = 0;
	int w, h;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags;
	Uint8 saved_alpha;
	
	/* Use the surface width and height expanded to powers of 2 */
	w = power_of_two(surface->w);
	h = power_of_two(surface->h);
	texcoord[0] = 0.0f;         /* Min X */
	texcoord[1] = 0.0f;         /* Min Y */
	texcoord[2] = (GLfloat) surface->w / w;     /* Max X */
	texcoord[3] = (GLfloat) surface->h / h;     /* Max Y */
	
	image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN     /* OpenGL RGBA masks */
				     0x000000FF,
				     0x0000FF00, 0x00FF0000, 0xFF000000
#else
						     0xFF000000,
						     0x00FF0000, 0x0000FF00, 0x000000FF
#endif
				    );
	if (image == NULL)
	{
		return 0;
	}
	
	/* Save the alpha blending attributes */
	saved_flags = surface->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
	saved_alpha = surface->format->alpha;
	if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
	{
		SDL_SetAlpha(surface, 0, 0);
	}
	
	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);
	
	/* Restore the alpha blending attributes */
	if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
	{
		SDL_SetAlpha(surface, saved_flags, saved_alpha);
	}
	
	/* Create an OpenGL texture for the image */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	SDL_FreeSurface(image);     /* No longer needed */
	
	return texture;
}

void SDL_GL_drawImageLow(GLuint handle, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, GLint w, GLint h, GLint x, GLint y, bool ck , unsigned char alpha)
{

	if(ck) {
		glEnable(GL_BLEND);
		glColor4ub(255,255,255,alpha);
	}
	
	SDL_GL_drawImageLow( handle, min_x, min_y, max_x, max_y, w, h, x, y );
	
	if(ck) {
		glDisable(GL_BLEND);
	}
}

void SDL_GL_drawImageLow(GLuint handle, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, GLint w, GLint h, GLint x, GLint y)
{
	glBindTexture( GL_TEXTURE_2D, handle );
	glEnable( GL_TEXTURE_2D );
	glBegin(GL_QUADS);
	
	glTexCoord2f(min_x, min_y);
	glVertex3i(x, y, 0);
	
	glTexCoord2f(min_x, max_y);
	glVertex3i(x, y + h, 0);
	
	glTexCoord2f(max_x, max_y);
	glVertex3i(x + w, y + h, 0);
	
	glTexCoord2f(max_x, min_y);
	glVertex3i(x + w, y, 0);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void SDL_GL_convertCoords(GLfloat* coords, GLint x, GLint y, GLint w, GLint h, const GLfloat * texcoord, GLint iw, GLint ih )
{
	coords[0] = (x * texcoord[2]) / iw;
	coords[1] = (y * texcoord[3]) / ih;
	
	coords[2] = ((GLfloat)(x + w - 1) * texcoord[2]) / iw;
	coords[3] = ((GLfloat)(y + h - 1) * texcoord[3]) / ih;
}

