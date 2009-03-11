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
#ifndef CLIENTEARGENTUM_H
#define CLIENTEARGENTUM_H

#include <guichan.hpp>
#include <vector>
#include "SDL.h"
#include "class_types.h"
#include "comunicador.h"
#include "sock.h"
#include "bodydata.h"


class vmain;
class vcreation;
#include "maingui.h"


#include "bytequeue.h"

#include "inventory.h"

class vpassword;

class vlogin;
class vdrop;

class audioengine;

/**
 @mainpage Cliente C++ - Documentacion Tecnica
 
 @section intro_sec Introduccion
 
 Hola !!

 */

/**
 * @brief Clase central del juego, se encarga de coordinar las distintas partes del juego
 * @author alejandro santos <alejolp@gmail.com>
 */
class ClienteArgentum : public gcn::ActionListener, public csocket::EventListener
{
	public:
		ClienteArgentum();
		~ClienteArgentum();

		/// Ejecuta el rendering loop del juego
		void run();

		static ClienteArgentum* instancia(){
			if(_instancia==0){
				_instancia=new ClienteArgentum();
			}
			return _instancia;
		}

		ao::MapFile_ptr ActualMap(){
			return _map;
		}
		
		ao::BodyData_ptr BodyData(){
			return _bodyData;
		}
		

		void setCurrentChar(const int c);

		inline const int getCurrentChar(){ return currentChar; };

		/// Para uso del render engine
		int getWalkSpeed(){ return walk_speed; }

		/// Action listener de guichan
		void action(const gcn::ActionEvent& actionEvent);

		/// Event listener del socket
		void socket_onEvent(csocket* sock, SocketEventsTypes ev_type, int param1);

		/// Avisa al cliente que se logueó
		void set_logged(bool a);

		/// FIXME
		std::vector<ao::Entity_ptr> _entities;

		/// FIXME?
		Inventory UserInventory;
		Inventory NPCInventory;
		Inventory BankInventory;
		
		ao::GrhDataFile_ptr get_grhData(){ return _grhData;};

		bool hayTecho(){ return bajoTecho; }

		///NOTE: No se si convendría que cliente argentum tenga copia de los datos y EL se encargue de setearlos en la ventana. Mirame despues :D.
		MainGui* get_ministats() { return main_gui; }

		/// TODO: mejorame?
		audioengine* audio() { return aengine; }

		/// Guichan Loader TODO sacame de aca después
		GuichanLoader_ptr _guichan;		

		void Dados(int fuerza,int agilidad,int inteligencia,int constitucion,int carisma);
	private:

		// Metodos privados
		
		/// Carga los archivos de datos
		void initData();
		
		/// Inicializa la pantalla
		void initScreen();

		/// El loop cental del juego
		void renderLoop();
		
		/// Dibuja los controles y objetos de la GUI
		void renderGUI();
		
		/// Procesa UN evento
		void handleEvent(SDL_Event & event);
		
		/// Recibe varios eventos
		void fetchEvents();

		/// Chequea si el usuario se puede mover, no usar a menos q se "intente" mover
		bool canWalk();

		/// Verifica las flechitas :D
		void checkKeys();

		/// Verifica si estamos bajo techo :O
		void checkTecho();

		/// Tira items
		void try_drop();

		void try_extract();

		void try_deposit();

		void try_buy();

		void try_sell();
		
	private:
		
		// Variables privadas

		bool bajoTecho;

		static ClienteArgentum* _instancia;

		/// Adaptador grafico, engargado de dibujar puntos, lineas e imagenes
		ga::GraphicsAdapter_ptr _graphic;
		
		/// Engine grafico, encargado de dibujar mapas, objetos, chars, etc.
		RendererEngine_ptr _engine;
		
		/// Administrador de imagenes
		ImageManager_ptr _imgMan;
		
		
		
		/// Boolean que indica si el engine debe seguir ejecutandose
		bool _run;
		
		/// 
		ao::GrhDataFile_ptr _grhData;
		
		///
		ao::MapFile_ptr _map;
		
		///
		ao::BodyData_ptr _bodyData;
		
		///
		cByteQueue in;

		cByteQueue out;

		csocket* sock;

		cComunicador* comu;

		/// Indica el indice de el personaje del ususario
		int currentChar;

		bool logged;

		bool ondialog;

		/// Velocidad de movimiento y variable de chequeo
		Uint32 walk_speed;

		Uint32 tickswalk;

		vlogin *login_window;


		vmain *main_window;

		vcreation* creation_window;

		vdrop *drop_window;

		audioengine *aengine;

		MainGui *main_gui;

		bool new_char;

		gcn::TextField* input_console;
		
		bool input_console_up;

		vpassword* password_window;

		bool showing_password_window;

		void command_parse(std::string what);
};

#endif
