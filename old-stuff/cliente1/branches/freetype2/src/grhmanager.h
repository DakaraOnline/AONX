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
#ifndef AOGRHMANAGER_H
#define AOGRHMANAGER_H

#include "class_types.h"
#define ANIM_SPEED 50

namespace ao
{

	/**
	@brief Esta clase se encarga de administrar los Grh
	@author alejandro santos <alejolp@gmail.com>
	
	La clase GrhManager se encarga de administrar las operaciones que se realizan
	sobre los Grh. Un Grh representa un "Grafico" (tambien llamado "Sprite") el cual 
	puede tener varios frames. Esta clase se utiliza para controlar ese proceso de animacion.
	Para ello existe la funcion getNextFrame la cual dado un GrhBasic devuelve un
	GrhDataItem, el cual representa una imagen "basica", o sea, un cuadro de la 
	animacion del Grh.
	
	*/
	class GrhManager
	{
	public:
		GrhManager( GrhDataFile_ptr grhdata );

		~GrhManager();
		
		/** @brief Dado un Grh, devuelve un GrhDataItem indicando el proximo frame de animacion
		 * @see GrhDataItem
		 */
		GrhDataItem & getNextFrame( GrhBasic & grh );

	private:
		
		ao::GrhDataFile_ptr _grhData;
	};

}

#endif
