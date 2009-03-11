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

#ifndef __AONX_HELPER_GRAPHICS_H__
#define __AONX_HELPER_GRAPHICS_H__

#include "SDL.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

int power_of_two(int input);

GLuint SDL_GL_LoadTexture(SDL_Surface * surface, GLfloat * texcoord);

void SDL_GL_drawImageLow(GLuint handle, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, GLint w, GLint h, GLint x, GLint y, bool ck , unsigned char alpha);

void SDL_GL_drawImageLow(GLuint handle, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, GLint w, GLint h, GLint x, GLint y);

void SDL_GL_convertCoords(GLfloat* coords, GLint x, GLint y, GLint w, GLint h, const GLfloat * texcoord, GLint iw, GLint ih );

#endif // __AONX_HELPER_GRAPHICS_H__

