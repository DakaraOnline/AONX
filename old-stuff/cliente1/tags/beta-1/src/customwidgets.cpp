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


#include "customwidgets.h"

void _TextField::draw (gcn::Graphics *graphics){
	gcn::Color faceColor = getBackgroundColor();
	graphics->setColor(faceColor);
	graphics->fillRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));
	int baseX=0;
	if(align==gcn::Graphics::CENTER){
		baseX=mDimension.width/2;
		if (isFocused())
		{
			drawCaret(graphics, baseX+(getFont()->getWidth(mText.substr(0, mCaretPosition)))/2 - mXScroll);
		}
	}else if(align==gcn::Graphics::RIGHT){
		baseX=mDimension.width;
		///FIXME no ando bien, creo.
		if (isFocused())
		{
			drawCaret(graphics, baseX+getFont()->getWidth(mText.substr(0, mCaretPosition)) - mXScroll);
		}
	}else{
		if (isFocused())
		{
			drawCaret(graphics, baseX+getFont()->getWidth(mText.substr(0, mCaretPosition)) - mXScroll);
		}
	}

	graphics->setColor(getForegroundColor());
	graphics->setFont(getFont());
	graphics->drawText(mText, baseX+ 1 - mXScroll, 1,align);

}

void Dibujito::draw(gcn::Graphics* graphics){
	if(img)
		graphics->drawImage(img,0,0);
}



