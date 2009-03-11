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
#ifndef GAGRAPHICSADAPTER_H
#define GAGRAPHICSADAPTER_H

#include <string>
#include <exception>

#include "SDL.h"

#include "guichan.hpp"
#include "class_types.h"

#include "color.h"
#include "rect.h"

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>


namespace ga {
	
	// TODO: DONDE METO ESTAS DOS FUNCIONES ASIGNAR ??
	
	/**
	 * asigna desde la derecha hacia la izquierda, desde un %Rect hacia un SDL_Rect
	 */
	inline void asignar (SDL_Rect & sr, const Rect & rr)
	{
		sr.x = rr._x;
		sr.y = rr._y;
		sr.w = rr._w;
		sr.h = rr._h;
	}

	/**
	 * asigna desde la derecha hacia la izquierda, desde un SDL_Rect hacia un %Rect
	 */
	inline void asignar( Rect & rr, const SDL_Rect & sr )
	{
		rr = Rect(sr.x, sr.y, sr.w, sr.h);
	}
	
	
	/**
	 *  @brief Clase base para las excepciones de %GraphicsAdapter y familia.
	 *
	 */
	class GraphicsAdapterException : public std::exception 
	{
		public:
			GraphicsAdapterException(std::string mensaje)
			: _mensaje(mensaje)
			{}
			virtual ~GraphicsAdapterException() throw() {}
			
			virtual const char* what() const throw() { return _mensaje.c_str(); }
			
		private:
			std::string _mensaje;
	};
	
		
	/**
	 * @brief Clase para representar un Punto, usada en las funciones de %GraphicsAdapter
	 *
	 */
	class Point 
	{
		public:
			Point( int x, int y ) 
			: _x(x), _y(y)
			{}
		
			int _x, _y;
	};
		


	
	/**
	* @brief Clase abstracta para representar imagenes 
	* @author alejandro santos <alejolp@gmail.com>
	*/
	class Image
	{
	public:
		Image() : _rect(0, 0, 0, 0), _texture(0), _valid(false) {}
		~Image() {unloadImage();}
		
		inline const Rect& getRect() const { return _rect; }

		/**
		 * Carga la textura desde el archivo 
		 */
		void loadImage(std::string path);
		
		/**
		 * Devuelve si la textura es valida
		 */
		bool textureHandleValid() const { return _valid; }
		
		/**
		 * Devuelve el handle de OpenGL de la textura
		 */
		inline GLuint getTextureHandle() const { return _texture; }
		
		/**
		 * Devuelve las coordenadas reales para dibujar la textura
		 */
		inline const GLfloat* getTexCoords() const { return _texcoord; }
		
	protected:
		Rect _rect;
		void unloadImage();
	
		void checkSurface()
		{
			if ( ! _valid )
				throw GraphicsAdapterException("ImageSDL::checkSurface -> _surface == NULL ! ");
		}
	
		GLuint _texture;
		bool _valid;
		GLfloat _texcoord[4];
	};

	/**
	* @brief Clase base abstracta para representar un adaptador grafico 
	* @author alejandro santos <alejolp@gmail.com>
	*
	* Pequeña abstraccion realizada sobre una superficie de dibujo para
	* facilitar las operaciones basicas de dibujo. 
	*/
	class GraphicsAdapter
	{
		public:
		GraphicsAdapter( SDL_Surface* surface , GuichanLoader_ptr guichan);

		virtual ~GraphicsAdapter();
		
		virtual void drawPoint( int x, int y, const Color & c );
		virtual void drawLine( int x1, int y1, int x2, int y2, const Color & c );
		virtual void drawRect( const Rect & r, const Color & c );
	
		virtual Image_ptr loadImage(std::string imagePath);

		virtual void drawImage(int img_id, Image* img, const Rect & src, const Point & dest, bool ck , unsigned char alpha, short int angle = 0, bool light = false, int* rgb_list = NULL);
		virtual void drawImage(int img_id, Image* img, const Point & dest, bool ck , unsigned char alpha, short int angle = 0, bool light = false, int* rgb_list = NULL);

		virtual void drawText(gcn::ImageFont* font, const std::string txt, const Point & dest);
		virtual void drawText(const std::wstring txt, const Point & dest);

		virtual void beginFrame();
		virtual void endFrame();
		virtual void setBaseLight(unsigned char r, unsigned char g, unsigned char b);

	private:

		void enter2dMode();
		void leave2dMode();
		//TODO: este INLINE no hace nada, pero deberia.
		inline void drawImageLow(int img_id, Image *imgogl, GLfloat min_x, GLfloat min_y, GLfloat max_x, GLfloat max_y, int w, int h, const Point & dest,  bool ck , unsigned char alpha, short int angle, bool light, int* rgb_list);

	private:

		SDL_Surface* _surface;
		GuichanLoader_ptr guichan;
		unsigned char base_r;
		unsigned char base_g;
		unsigned char base_b;

		GLuint lists[50000];
	};
	
	
	
}

#endif
