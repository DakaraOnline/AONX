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


#include "textrenderer.h"

#include "class_types.h"

#include "color.h"
#include "rect.h"

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
		Image() : _rect(0, 0, 0, 0) {}
		virtual ~Image() {}
		
		const Rect& getRect() const throw() { return _rect; }
		
		virtual void setColorKey( const Color & c, bool active = true ) = 0;
		virtual void setAlpha( unsigned int alpha, bool active = true ) = 0;
		virtual void displayFormat() = 0;
		
	protected:
		Rect _rect;
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
			GraphicsAdapter();
			virtual ~GraphicsAdapter();
	
			/// dibuja un punto de color %c indicado por las coordenadas x e y
			virtual void drawPoint( int x, int y, const Color & c ) = 0;
		
			/// Dibuja un punto de color c en el punto p
			void drawPoint( const Point & p, const Color & c ) {
				drawPoint( p._x, p._y, c );
			}
		
			/// Dibuja una linea
			virtual void drawLine( int x1, int y1, int x2, int y2, const Color & c ) = 0;
		
			/// Dibuja una linea
			void drawLine( const Point & p1, const Point & p2, const Color & c ) {
				drawLine( p1._x, p1._y, p2._x, p2._y, c );
			}
		
			/// Dibuja un rectangulo
			virtual void drawRect( const Rect & r, const Color & c ) = 0;
			
			/// Dibuja un rectangulo
			void drawRect( int x, int y, int w, int h, const Color & c ) {
				drawRect( Rect( x, y, w, h ), c );
			}
		
			/// Crea una nueva imagen. Tener presente que devuelve un %linked_ptr<Image> 
			virtual Image_ptr loadImage(std::string imagePath) = 0;
			
			/** @brief Muestra una porcion de una imagen
			 *
			 * Muestra una porcion de una imagen (indicada por el Rect src), en
			 * la posicion indicada por el Point.
			 */
			virtual void drawImage(Image_ptr img, const Rect & src, const Point & dest, bool ck , unsigned char alpha ) = 0;
			
			/// Muestra una imagen completa en la posicion indicada
			virtual void drawImage(Image_ptr img, const Point & dest, bool ck, unsigned char alpha ) = 0;
			
			/// Dibuja texto en la pantalla
			virtual void drawText(TextRenderer_ptr tr, const std::string txt, const Point & dest) = 0;
			
			/// Dibuja texto en la pantalla
			virtual void drawText(TextRenderer_ptr tr, const std::wstring txt, const Point & dest) = 0;
			
			/// Inicia un nuevo frame de dibujo
			virtual void beginFrame() = 0;
			
			/// Finaliza el frame actual
			virtual void endFrame() = 0;
	};
	
	
	
}

#endif
