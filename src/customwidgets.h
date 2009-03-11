/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre  				   *
 *   esteban.torre@gmail.com  						   *
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

#ifndef _customwidgets_h
#define _customwidgets_h
#include <guichan.hpp>

class _TextField : public gcn::TextField
{
	public:
		_TextField(std::string t, int _a) : align(_a),TextField(t) {}
		_TextField(std::string t) : align(gcn::Graphics::LEFT),TextField(t) {}
		_TextField(int _a) : align(_a) {}
		_TextField() : align(gcn::Graphics::LEFT) {}
		void draw (gcn::Graphics *graphics);
		void setAlignment(int _align){ align=_align;}
	private:
		int align;
};

class NoDrawButton : public gcn::Button
{
	public:
		void draw(gcn::Graphics *graphics){}
		void drawBorder(gcn::Graphics *graphics){}
};

class Dibujito : public gcn::Widget
{
	public:
		Dibujito(gcn::Image& _img) : img(&_img){}
		//No se queda el ownership de la imagen, solo la usa, CUIDADO.
		void draw(gcn::Graphics * graphics);
		void drawBorder(gcn::Graphics *graphics){}
	private:
		gcn::Image* img;
};

#endif

