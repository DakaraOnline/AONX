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

#include <iostream>
#include <exception>

#include "inifile.h"
#include "configdata.h"

#include "class_types.h"

#include "clienteargentum.h"
#include "grhdata.h"
#include "aomap.h"
#include "bodydata.h"
#include "entity.h"

#include "rendererenginesdl.h"
#include "rendererengineogl.h"
#include "vpassword.h"

#include "console.h"

#include "vlogin.h"
#include "vdrop.h"

#include "vmain.h"
#include "vcreation.h"

#include "maingui.h"
#include "verror.h"
#include "audioengine.h"

using namespace std;

#define AO_MAX_ENTITIES 10000

ClienteArgentum* ClienteArgentum::_instancia = 0;

ClienteArgentum::ClienteArgentum()
	: _run(false), _entities(AO_MAX_ENTITIES), currentChar(0), 
	tickswalk(0), UserInventory(20,"I_HIDE",this), NPCInventory(40,"N_HIDE",this),
	BankInventory(40,"B_HIDE",this), logged(false), drop_window(NULL), new_char(false), creation_window(NULL),main_gui(NULL),input_console_up(false), password_window(NULL), showing_password_window(false)
{
	walk_speed=250;
}

ClienteArgentum::~ClienteArgentum()
{
	delete login_window;//FIXME esto no irï¿½a aca (??).
	//FIXME no faltarï¿½a main window?
//	delete ministats_window;
	delete aengine;
	if(showing_password_window)
	{
		//sacarlo?
	}
	delete password_window;
}

void ClienteArgentum::initData()
{

	_grhData = ao::GrhDataFile_ptr( new ao::GrhDataFile() );
	_grhData->loadData( (ConfigData::GetPath("init") + string("Graficos.ind")).c_str() );
	
	_map = ao::MapFile_ptr( new ao::MapFile() );

	
	_bodyData = ao::BodyData_ptr( new ao::BodyData() );
	_bodyData->loadData();
}

void ClienteArgentum::initScreen()
{
	if(ConfigData::Sdl)
	{
		_engine = RendererEngine_ptr( new RendererEngineSDL() );
	}else
	{
		_engine = RendererEngine_ptr( new RendererEngineOGL() );
	}
	_graphic = _engine->getGraphicsAdapter();
	_imgMan = _engine->getImageManager();
	_guichan = _engine->getGuichan();

	_engine->initialize( _grhData, _bodyData );
	_engine->setMap( _map );

	input_console = new gcn::TextField;
	input_console->setWidth(590);
	input_console->setBaseColor(gcn::Color(255,255,255,127));
	input_console->setBackgroundColor(gcn::Color(255,255,255,127));
	input_console->setBorderSize(1);

}

void ClienteArgentum::run()
{
	sock = new csocket(this);
	comu = new cComunicador(sock,&in,&out);
	
	initData();
	initScreen();

	aengine= new audioengine;

	aengine->init();
	aengine->play_music(ConfigData::GetPath("audio") + std::string("test.mp3"));
	renderLoop();
}


void ClienteArgentum::checkTecho(){
	ao::MapTile & tile = _map->getTile(_entities[currentChar]->getPos());

	bajoTecho=(tile.trigger==1)||(tile.trigger==2)||(tile.trigger==4);

}

bool ClienteArgentum::canWalk()
{
	if((tickswalk+walk_speed)<SDL_GetTicks()){
		tickswalk=SDL_GetTicks();
		return true;
		// TODO: Verificar usuario paralizado, world save, etc.
	}
	return false;
}


/// @remarks: tiene que hacerse despuï¿½s del check events, sino los datos son "viejos".
void ClienteArgentum::checkKeys()
{
	if(!logged) return;

	Uint8 *keystate = SDL_GetKeyState(NULL);
	if(keystate[SDLK_LSHIFT])
	{
		walk_speed-=3;
		if(walk_speed<30)
			walk_speed=30;
	}else
	{
		walk_speed+=4;
		if(walk_speed>250)
			walk_speed=250;
	}
	if(keystate[SDLK_LEFT]){
		if(canWalk()){
			if(_entities[currentChar]->moveDir(ao::Entity::WEST,true)){
				comu->Walk(ao::Entity::WEST);
				checkTecho();
			}else{
				comu->ChangeHeading(ao::Entity::WEST);
			}
		}
	}else if(keystate[SDLK_RIGHT]){
		if(canWalk()){
			if(_entities[currentChar]->moveDir(ao::Entity::EAST,true)){
				comu->Walk(ao::Entity::EAST);
				checkTecho();
			}else{
				comu->ChangeHeading(ao::Entity::EAST);
			}
		}
	}else if(keystate[SDLK_DOWN]){
		if(canWalk()){
			if(_entities[currentChar]->moveDir(ao::Entity::SOUTH,true)){
				comu->Walk(ao::Entity::SOUTH);
				checkTecho();
			}else{
				comu->ChangeHeading(ao::Entity::SOUTH);
			}
		}
	}else if(keystate[SDLK_UP]){
		if(canWalk()){
			if(_entities[currentChar]->moveDir(ao::Entity::NORTH,true)){
				comu->Walk(ao::Entity::NORTH);
				checkTecho();
			}else{
				comu->ChangeHeading(ao::Entity::NORTH);
			}
		}
	}
}

void ClienteArgentum::try_drop()
{
	if((logged) && (!drop_window)){
		if(UserInventory[UserInventory.get_active()]->objamount > 0){
			if(UserInventory[UserInventory.get_active()]->objamount==1){
				comu->Drop(UserInventory.get_active()+1,1);
			}else{
				drop_window = new vdrop(UserInventory.get_active(),&UserInventory,"DROP","Tirar");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deberï¿½an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_extract(){
	if((logged) && (!drop_window)){
		if(BankInventory[BankInventory.get_active()]->objamount > 0){
			if(BankInventory[BankInventory.get_active()]->objamount==1){
				comu->BankExtractItem(BankInventory.get_active()+1,1);
			}else{
				drop_window = new vdrop(BankInventory.get_active(),&BankInventory,"EXTRACT","Extraer");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deberï¿½an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_deposit(){
	if((logged) && (!drop_window)){
		if(UserInventory[UserInventory.get_active()]->objamount > 0){
			if(UserInventory[UserInventory.get_active()]->objamount==1){
				comu->BankDeposit(UserInventory.get_active()+1,1);
			}else{
				drop_window = new vdrop(UserInventory.get_active(),&UserInventory,"DEPOSIT","Depositar");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deberï¿½an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_buy(){
	if((logged) && (!drop_window)){
		if(NPCInventory[NPCInventory.get_active()]->objamount > 0){
			if(NPCInventory[NPCInventory.get_active()]->objamount==1){
				comu->CommerceBuy(NPCInventory.get_active(),1);
			}else{
				drop_window = new vdrop(NPCInventory.get_active(),&NPCInventory,"BUY","Comprar");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deberï¿½an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_sell(){
	if((logged) && (!drop_window)){
		if(UserInventory[UserInventory.get_active()]->objamount > 0){
			if(UserInventory[UserInventory.get_active()]->objamount==1){
				comu->CommerceSell(UserInventory.get_active(),1);
			}else{
				drop_window = new vdrop(UserInventory.get_active(),&UserInventory,"SELL","Vender");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deberï¿½an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::handleEvent(SDL_Event & event)
{
	bool gui=true;
	switch( event.type )
	{
		case SDL_KEYDOWN:
		{
			switch ( event.key.keysym.sym )
			{
				case SDLK_c:
					if(logged && !ondialog){
						comu->CombatModeToggle();
						gui=false;
					}
					break;
				case SDLK_m:
					if(logged && !ondialog)
					{
						main_gui->toggleMiniMapRender();
					}
					break;
				case SDLK_a:
					if(logged && !ondialog){
						comu->PickUp();
						gui=false;
					}
					break;
				case SDLK_e:
					if(logged && !ondialog){
						comu->Equip(UserInventory.get_active());
						gui=false;
					}
					break;
				case SDLK_u:
					if(logged && !ondialog){
						comu->Use(UserInventory.get_active());
						gui=false;
					}
					break;
				case SDLK_t:
					if(logged && !ondialog){
						try_drop();
						gui=false;
					}
					break;
				case SDLK_b:
					if(BankInventory.is_visible()) {
						try_extract();
						gui=false;
					}else if(NPCInventory.is_visible()){
						try_buy();
						gui=false;
					}
					break;
				case SDLK_s:
					if(BankInventory.is_visible()){
						try_deposit();
						gui=false;
					}else if(NPCInventory.is_visible()){
						try_sell();
						gui=false;
					}
					break;
				case SDLK_ASTERISK:
					break;
				case SDLK_RETURN:
					if(!logged)
						break;
					if(input_console_up)
					{
						_guichan->get_top()->remove(input_console);
						input_console_up = false;
						ondialog = false;
						std::string _cmd = input_console->getText();
						//TODO hacer una función para esto
						if(_cmd.substr(0,1)==std::string("/"))
						{
							//TODO: comandos
						}else
						{
							comu->Talk(_cmd);
						}
						input_console->setText("");
					}else
					{
						_guichan->get_top()->add(input_console,1,1);
						input_console->requestFocus();
						input_console_up = true;
						ondialog = true;
					}
					break;
				case SDLK_RCTRL:
				case SDLK_LCTRL:
					if(logged) comu->Attack();
					gui=false;
					break;
				case SDLK_ESCAPE:
					_run = false;
					gui=false;
					break;
			}
			
			// GUI Event
			if(!((logged)&&(!gui)))
				_guichan->pushInput(event);
		}
		break;

		case SDL_QUIT:
			/* Handle quit requests (like Ctrl-c). */
			_run = false;
		break;
		

		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button==SDL_BUTTON_LEFT){
				int mx,my;
				// FIXME: esto tendria q informarlo el engine.
				if(logged && !ondialog && !BankInventory.is_visible() && !NPCInventory.is_visible()){
					mx=_entities[currentChar]->getPos().x-12;
					my=_entities[currentChar]->getPos().y-7;
					mx+=event.button.x/32;
					my+=event.button.y/32;
					comu->LeftClick(mx+1,my+1);
				}
			}else if(event.button.button==SDL_BUTTON_RIGHT){
				int mx,my;
				// FIXME: esto tendria q informarlo el engine.
				if(logged && !ondialog && !BankInventory.is_visible() && !NPCInventory.is_visible()){
					mx=_entities[currentChar]->getPos().x-12;
					my=_entities[currentChar]->getPos().y-7;
					mx+=event.button.x/32;
					my+=event.button.y/32;
					comu->DoubleClick(mx+1,my+1);
				}
			}
			_guichan->pushInput(event);
		break;

		default:
			// GUI Event
			_guichan->pushInput(event);
		break;
	}
}

void ClienteArgentum::fetchEvents()
{
	SDL_Event event;

	while( SDL_PollEvent( &event ) )
	{
		handleEvent( event );
	}
}

void ClienteArgentum::renderGUI()
{
//	_graphic->drawRect( ga::Rect( 10, 10, 30, 20 ), ga::Color( 0xff, 0xff, 0xff ) );

	_guichan->logic();
	
	_guichan->draw();

}

void ClienteArgentum::set_logged(bool a){

	logged=a;
	if(logged){
		if(!main_gui)
			main_gui = new MainGui();
		main_gui->set_visibility(true);
		_guichan->get_top()->add(main_gui);
		_guichan->get_top()->add(&UserInventory,615,16);
		_guichan->get_top()->add(&NPCInventory,330,210);
		_guichan->get_top()->add(&BankInventory,330,210);
		NPCInventory.set_visibility(false);
		BankInventory.set_visibility(false);
//		_guichan->get_top()->add(ministats_window,20,20);
		if(new_char)
		{
			_guichan->get_top()->remove(creation_window);
			new_char=false;//??
		}else{
			_guichan->get_top()->remove(main_window);
		}
		//FIXME: en realidad hay q remover login de window y window dsp.
		bajoTecho=false; //No se si aca ya tengo el charindex...
		ondialog=false;
	}else{
		//sacar ventanitas? hacer cosas?
		main_gui->set_visibility(false);
	}
}

void ClienteArgentum::setCurrentChar(const int c){
	//validchar(c);
	currentChar=c;
	if(main_gui)//TODO: revisar bien cuando se crea main_gui
		main_gui->setNombre(_entities[c]->getNombre());
}

void ClienteArgentum::renderLoop()
{
	_run = true;

	//const char * fontFile = "/usr/share/fonts/ttf-bitstream-vera/Vera.ttf";
	
	//TextRenderer_ptr tr = TextRenderer_ptr( new TextRenderer(fontFile, 11) );

	/*ao::Entity* ent = new ao::Entity( _map, ao::Pos( 6, 6), ao::Entity::NORTH );
	ent->loadData( _bodyData, 1, 1, 2, 2, 2 );
	
	_map->getTile( ao::Pos( 5, 5 ) ).obj.init( 2720 );*/

	main_window= new vmain;
	login_window = new vlogin;
	_guichan->get_top()->add(main_window,0,0);
	main_window->setLoginWindow(login_window);
//	ministats_window= new vministats;
	main_gui = new MainGui();
	while (_run)
	{
		// Leo los eventos de mouse, teclado, etc.
		fetchEvents();

		// Reviso las "flechitas" :D

		checkKeys();

		// Reviso el socket
		sock->poll_status();

		// Actualiza la consola
		Consola::instancia()->update();

		// Inicia un nuevo frame de dibujo
		_engine->beginFrame();
		
		// Dibuja las cosas en la pantalla, si hay que hacerlo.
		if((logged)&&(currentChar>0)){
			_engine->render( _entities[currentChar]->getPos().x, _entities[currentChar]->getPos().y );
		}
		
		// Dibuja la GUI en la pantalla
		renderGUI();
		
		// Muestra el frame de dibujo en la pantalla
		_engine->endFrame();
		
	}
}


void ClienteArgentum::action(const gcn::ActionEvent& actionEvent){
	if(actionEvent.getId()==std::string("LOGIN"))
	{

		sock->conectar(main_window->getHost().c_str(), main_window->getPort());
	}else if(actionEvent.getId()==std::string("DROP"))
	{
		comu->Drop(drop_window->get_slot(),drop_window->get_amount());
		_guichan->get_top()->remove(drop_window);
		drop_window=NULL;
		ondialog=false;
	}else if(actionEvent.getId()==std::string("EXTRACT"))
	{
		comu->BankExtractItem(drop_window->get_slot()+1,drop_window->get_amount());
		_guichan->get_top()->remove(drop_window);
		drop_window=NULL;
		ondialog=false;
	}else if(actionEvent.getId()==std::string("DEPOSIT"))
	{
		comu->BankDeposit(drop_window->get_slot()+1,drop_window->get_amount());
		_guichan->get_top()->remove(drop_window);
		drop_window=NULL;
		ondialog=false;
	}else if(actionEvent.getId()==std::string("BUY"))
	{
		comu->CommerceBuy(drop_window->get_slot(),drop_window->get_amount());
		_guichan->get_top()->remove(drop_window);
		drop_window=NULL;
		ondialog=false;
	}else if(actionEvent.getId()==std::string("SELL"))
	{
		comu->CommerceSell(drop_window->get_slot(),drop_window->get_amount());
		_guichan->get_top()->remove(drop_window);
		drop_window=NULL;
		ondialog=false;
	}else if(actionEvent.getId()==std::string("DROP_CLOSE"))
	{
		_guichan->get_top()->remove(drop_window);
		drop_window=NULL;
		ondialog=false;
	}else if(actionEvent.getId()==std::string("B_HIDE"))
	{
		comu->EndBank();
	}else if(actionEvent.getId()==std::string("N_HIDE"))
	{
		comu->EndCommerce();
	}else if(actionEvent.getId()==std::string("CREATE"))
	{
		sock->conectar(main_window->getHost().c_str(), main_window->getPort());
		new_char=true;
		_guichan->get_top()->remove(main_window);
		if(!creation_window) creation_window= new vcreation;
		_guichan->get_top()->add(creation_window);
		creation_window->resetDados();
	}else if(actionEvent.getId()==std::string("MAIN"))
	{
		sock->cerrar();
		new_char=false;
		_guichan->get_top()->remove(creation_window);
		if(showing_password_window)
		{
			_guichan->get_top()->remove(password_window);
			showing_password_window=false;
		}
		_guichan->get_top()->add(main_window);
	}else if(actionEvent.getId()==std::string("DADOS"))
	{
		comu->Dados();
	}else if(actionEvent.getId()==std::string("CONTINUAR"))
	{
		//GetPassword
		if(!password_window)
			password_window = new vpassword;
		_guichan->get_top()->add(password_window);
		showing_password_window=true;
	}else if(actionEvent.getId()==std::string("PASSWORDOK"))
	{
		_guichan->get_top()->remove(password_window);
		showing_password_window=false;
		Sint8 skills[21];
		creation_window->getSkills(skills);
		comu->LoginNew(creation_window->getNombre(),password_window->getPassword(),"a@a.com",0,12,0, skills, creation_window->getRaza(), creation_window->getCiudad(), creation_window->getGenero(), creation_window->getClase());
	}else if(actionEvent.getId()==std::string("ERROR_OK"))
	{
		ErrorMessage::off();
	}

}
void ClienteArgentum::Dados(int fuerza,int agilidad,int inteligencia,int constitucion,int carisma)
{
	creation_window->setDados(fuerza,agilidad,inteligencia,constitucion,carisma);
}
void ClienteArgentum::socket_onEvent(csocket* sock, SocketEventsTypes ev_type, int param1)
{
	switch (ev_type)
	{
	case csocket::EventListener::SOCKEVENT_CONNECT:
		cout << "Conectado!" << endl;
		if(!new_char){
			comu->Login(login_window->get_user(),login_window->get_pass(),0,12,0);
			Consola::buffer << "Logueandose..." << std::endl;
		}else{

		}
		break;

	case csocket::EventListener::SOCKEVENT_READ:
		comu->Recibir();
		break;

// No me interesa
//	case csocket::EventListener::SOCKEVENT_WRITE:
//		break;

	case csocket::EventListener::SOCKEVENT_CLOSE:
		cout << "Conexion Cerrada!" << endl;
		logged = false;
		if(new_char)
		{
			sock->conectar(main_window->getHost().c_str(), main_window->getPort());
		}
		break;
	}
}

