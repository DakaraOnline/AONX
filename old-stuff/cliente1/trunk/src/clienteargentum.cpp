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
#include <cstring>

#include "inifile.h"
#include "configdata.h"
#include "particulas.h"
#include "class_types.h"

#include "clienteargentum.h"
#include "rendererengine.h"
#include "grhdata.h"
#include "aomap.h"
#include "bodydata.h"
#include "entity.h"

#include "vpassword.h"

#include "console.h"

#include "vlogin.h"
#include "vdrop.h"

#include "vmain.h"
#include "vcreation.h"

#include "maingui.h"
#include "verror.h"
#include "audioengine.h"

#include "vestadisticas.h"

#include "hechizos.h"

#include "stats.h"
#include "guichanloader.h"

#include "sdl_cursor_helper.h"

using namespace std;

#define AO_MAX_ENTITIES 10000


//------------------------------------------------------
//-FUNCION PEDORRA SACAR DE ACA
//------------------------------------------------------
bool check_ventana(int x, int y, gcn::Widget* ventana)
{
	if((x > ventana->getX()) && ( x < (ventana->getX() + ventana->getWidth())) && (y > ventana->getY()) && ( y < (ventana->getY() + ventana->getHeight()))) 
		return true;
	return false;
}
//--listo



ClienteArgentum* ClienteArgentum::_instancia = 0;

ClienteArgentum::ClienteArgentum()
	: test_particle(0), test_fx(0), sent_ping(0),recv_pong(1),latency(0),status(Welcome), _skills(NULL), _attributes(NULL), _run(false), _entities(AO_MAX_ENTITIES), currentChar(0), 
	tickswalk(0), UserInventory(20,"I_HIDE",this), NPCInventory(40,"N_HIDE",this),
	BankInventory(40,"B_HIDE",this), drop_window(NULL), 
	creation_window(NULL),main_gui(NULL),input_console_up(false), password_window(NULL), 
	showing_password_window(false), using_spell(-1), ve(NULL)
{
	walk_speed=250;
	_skills = new Skills();
    (*_skills)[0].setName("Suerte");
    (*_skills)[1].setName("Magia");
    (*_skills)[2].setName("Robar");
    (*_skills)[3].setName("Tacticas");
    (*_skills)[4].setName("Armas");
    (*_skills)[5].setName("Meditar");
    (*_skills)[6].setName("Apunialar");
    (*_skills)[7].setName("Ocultarse");
    (*_skills)[8].setName("Supervivencia");
    (*_skills)[9].setName("Talar");
    (*_skills)[10].setName("Comerciar");
    (*_skills)[11].setName("Defensa");
    (*_skills)[12].setName("Pesca");
    (*_skills)[13].setName("Mineria");
    (*_skills)[14].setName("Carpinteria");
    (*_skills)[15].setName("Herreria");
    (*_skills)[16].setName("Liderazgo");
    (*_skills)[17].setName("Domar");
    (*_skills)[18].setName("Proyectiles");
    (*_skills)[19].setName("Wrestling");
    (*_skills)[20].setName("Navegacion");
	(*_skills).setFree(0);

	_attributes = new Attributes();
	(*_attributes)[0].setName("Fuerza");
	(*_attributes)[1].setName("Agilidad");
	(*_attributes)[2].setName("Inteligencia");
	(*_attributes)[3].setName("Carisma");
	(*_attributes)[4].setName("Constitucion");
}

ClienteArgentum::~ClienteArgentum()
{
	if(login_window_added)
	{
		delete login_window;//FIXME esto no iria aca (??).
	}
	//FIXME no faltar�a main window?
//	delete ministats_window;
	delete aengine;
	if(showing_password_window)
	{
		//sacarlo?
	}
	delete password_window;
	SDL_FreeCursor(cflecha);
	SDL_FreeCursor(ccruz);
}

void ClienteArgentum::initData()
{

	_grhData = ao::GrhDataFile_ptr( new ao::GrhDataFile() );
	_grhData->loadData( (ConfigData::GetPath("init") + string("Graficos.ind")).c_str() );

	_map = ao::MapFile_ptr( new ao::MapFile() );

	
	_bodyData = ao::BodyData_ptr( new ao::BodyData() );
	_bodyData->loadData();

	DatosParticulas::load_from_file(ConfigData::GetPath("init") + string("Particles.ini"));
	VHechizos.init();
	Mensajes.cargarDatos();
}

void ClienteArgentum::initScreen()
{
	_engine = RendererEngine_ptr( new RendererEngine() );

	_graphic = _engine->getGraphicsAdapter();
	_imgMan = _engine->getImageManager();
	_guichan = _engine->getGuichan();

	cflecha = init_system_cursor(Cursor_Arrow);
	ccruz = init_system_cursor(Cursor_Cruz);

	_engine->initialize( _grhData, _bodyData );
	_engine->setMap( _map );

	input_console = new gcn::TextField;
	input_console->setWidth(590);
	input_console->setBaseColor(gcn::Color(255,255,255,127));
	input_console->setBackgroundColor(gcn::Color(255,255,255,127));
	input_console->setBorderSize(1);

	SDL_SetCursor(cflecha);

}

void ClienteArgentum::run()
{
	sock = new csocket(this);
	comu = new cComunicador(sock,&in,&out);
	
	initData();
	initScreen();

	aengine= new audioengine;

	aengine->init();
	aengine->play_music();
	renderLoop();
}


void ClienteArgentum::checkTecho(){
	ao::MapTile & tile = _map->getTile(_entities[currentChar]->getPos());

	bajoTecho=(tile.trigger==1)||(tile.trigger==2)||(tile.trigger==4);

}

bool ClienteArgentum::canWalk()
{
	if(paralizado)
		return false;
	if((tickswalk+walk_speed)<SDL_GetTicks()){
		tickswalk=SDL_GetTicks();
		return true;
		// TODO: Verificar usuario paralizado, world save, etc.
	}
	return false;
}


/// @remarks: tiene que hacerse despu�s del check events, sino los datos son "viejos".
void ClienteArgentum::checkKeys()
{
	if((status!=Logged) || !currentChar) return;

	Uint8 *keystate = SDL_GetKeyState(NULL);

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
	if((status==Logged) && (!drop_window)){
		if(UserInventory[UserInventory.get_active()]->objamount > 0){
			if(UserInventory[UserInventory.get_active()]->objamount==1){
				comu->Drop(UserInventory.get_active(),1);
			}else{
				drop_window = new vdrop(UserInventory.get_active(),&UserInventory,"DROP","Tirar");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deber�an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_extract(){
	if((status==Logged) && (!drop_window)){
		if(BankInventory[BankInventory.get_active()]->objamount > 0){
			if(BankInventory[BankInventory.get_active()]->objamount==1){
				comu->BankExtractItem(BankInventory.get_active()+1,1);
			}else{
				drop_window = new vdrop(BankInventory.get_active(),&BankInventory,"EXTRACT","Extraer");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deber�an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_deposit(){
	if((status==Logged) && (!drop_window)){
		if(UserInventory[UserInventory.get_active()]->objamount > 0){
			if(UserInventory[UserInventory.get_active()]->objamount==1){
				comu->BankDeposit(UserInventory.get_active()+1,1);
			}else{
				drop_window = new vdrop(UserInventory.get_active(),&UserInventory,"DEPOSIT","Depositar");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deber�an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_buy(){
	if((status==Logged) && (!drop_window)){
		if(NPCInventory[NPCInventory.get_active()]->objamount > 0){
			if(NPCInventory[NPCInventory.get_active()]->objamount==1){
				comu->CommerceBuy(NPCInventory.get_active(),1);
			}else{
				drop_window = new vdrop(NPCInventory.get_active(),&NPCInventory,"BUY","Comprar");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deber�an handlear esto somehow
			}
		}
	}
}

void ClienteArgentum::try_sell(){
	if((status==Logged) && (!drop_window)){
		if(UserInventory[UserInventory.get_active()]->objamount > 0){
			if(UserInventory[UserInventory.get_active()]->objamount==1){
				comu->CommerceSell(UserInventory.get_active(),1);
			}else{
				drop_window = new vdrop(UserInventory.get_active(),&UserInventory,"SELL","Vender");
				_guichan->get_top()->add(drop_window,325,260);
				drop_window->focus();
				ondialog=true;//TODO: los dialogos deber�an handlear esto somehow
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
					if(status==Logged && !ondialog){
						comu->CombatModeToggle();
						gui=false;
					}
					break;
				case SDLK_m:
					if(status==Logged && !ondialog)
					{
						main_gui->toggleMiniMapRender();
					}
					break;
				case SDLK_a:
					if(status==Logged && !ondialog){
						comu->PickUp();
						gui=false;
					}
					break;
				case SDLK_e:
					if(status==Logged && !ondialog){
						comu->Equip(UserInventory.get_active());
						gui=false;
					}
					break;
				case SDLK_u:
					if(status==Logged && !ondialog){
						comu->Use(UserInventory.get_active());
						gui=false;
					}
					break;
				case SDLK_t:
					if(status==Logged && !ondialog){
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
					if(status!=Logged)
						break;
					if(input_console_up)
					{
						_guichan->get_top()->remove(input_console);
						input_console_up = false;
						ondialog = false;
						std::string _cmd = input_console->getText();
						//TODO hacer una funci�n para esto
						if(_cmd.substr(0,1)==std::string("/"))
						{
							command_parse(_cmd);
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
					if(status==Logged) comu->Attack();
					gui=false;
					break;
				case SDLK_ESCAPE:
					_run = false;
					gui=false;
					break;
			}
			
			// GUI Event
			if(!((status==Logged)&&(!gui)))
				_guichan->pushInput(event);
		}
		break;

		case SDL_QUIT:
			/* Handle quit requests (like Ctrl-c). */
			_run = false;
		break;
		

		case SDL_MOUSEBUTTONDOWN:
			int cx,cy;
			cx=event.button.x;
			cy=event.button.y;
			//--------------------
			//TODO ESTO APESTA OK?
			//--------------------
			if((!(check_ventana(cx,cy,&VHechizos)&&VHechizos.is_visible())) && (!check_ventana(cx,cy,main_gui))
				&& !(UserInventory.is_visible() && (check_ventana(cx,cy,&UserInventory)))
				&& !(NPCInventory.is_visible() && (check_ventana(cx,cy,&NPCInventory)))
				&& !(BankInventory.is_visible() && (check_ventana(cx,cy,&BankInventory)))
				&& !((ve) && ve->is_visible() && (check_ventana(cx,cy,ve)))
				)
			{
			//--------------------
			//Hasta aca
			//--------------------
				if(event.button.button==SDL_BUTTON_LEFT){
					int mx,my;
					// FIXME: esto tendria q informarlo el engine.
					if((status==Logged) && !ondialog && !BankInventory.is_visible() && !NPCInventory.is_visible() && currentChar){
						mx=_entities[currentChar]->getPos().x-12;
						my=_entities[currentChar]->getPos().y-7;
						mx+=event.button.x/32;
						my+=event.button.y/32;
						if(using_spell!=-1)
						{//Trata de lanzar spell
							if(VHechizos.hechis[using_spell]->usar())
							{//Si da el intervalo
								SDL_SetCursor(cflecha);
								comu->Magia(using_spell,mx+1,my+1);
								using_spell=-1;
								
							}
						}else{
							comu->LeftClick(mx+1,my+1);
						}
					}
				}else if(event.button.button==SDL_BUTTON_RIGHT){
					int mx,my;
					// FIXME: esto tendria q informarlo el engine.
					if((status==Logged) && !ondialog && !BankInventory.is_visible() && !NPCInventory.is_visible()){
						mx=_entities[currentChar]->getPos().x-12;
						my=_entities[currentChar]->getPos().y-7;
						mx+=event.button.x/32;
						my+=event.button.y/32;
						if(using_spell!=-1)
						{// cancela el lanzamiento
							using_spell=-1;
							SDL_SetCursor(cflecha);
						}else
						{
							comu->DoubleClick(mx+1,my+1);
						}
					}
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
	_guichan->logic();
	
	_guichan->draw();

}

void ClienteArgentum::set_logged(bool a){

	if(a){

		if(!main_gui)
			main_gui = new MainGui();

		main_gui->set_visibility(true);
		_guichan->get_top()->add(main_gui);
		main_gui->setMovable(false);
		main_gui->setFocusable(false);
		_guichan->get_top()->add(&NPCInventory,330,210);
		_guichan->get_top()->add(&BankInventory,330,210);
		VHechizos.setFocusable(false);
		_guichan->get_top()->add(&VHechizos);
		_guichan->get_top()->add(&UserInventory,600,16);
		if(login_window_added)
		{
			_guichan->get_top()->remove(login_window);
			delete login_window;
		}		
		NPCInventory.set_visibility(false);
		BankInventory.set_visibility(false);
//		_guichan->get_top()->add(ministats_window,20,20);
		if(status==NewChar)
		{
			_guichan->get_top()->remove(creation_window);
		}else{
			_guichan->get_top()->remove(main_window);
		}
		//FIXME: en realidad hay q remover login de window y window dsp.
		bajoTecho=false; //No se si aca ya tengo el charindex...
		ondialog=false;
		_engine->setCurrentLight(100,100,100);
		_engine->setTargetLight(255,255,255);
		
		status=Logged;
	}else{
		//TODO: sacar ventanitas? hacer cosas?
		/*main_gui->set_visibility(false);
		NPCInventory.set_visibility(false);
		BankInventory.set_visibility(false);
		VHechizos.setVisible(false);*/

		_guichan->get_top()->remove(&UserInventory);
		_guichan->get_top()->remove(&NPCInventory);
		_guichan->get_top()->remove(&BankInventory);
		_guichan->get_top()->remove(&VHechizos);
		_guichan->get_top()->remove(main_gui);
		_guichan->get_top()->add(main_window);
		status=Welcome;
	}
}

void ClienteArgentum::setCurrentChar(const int c){
	//validchar(c);
	currentChar=c;
	if(main_gui && c)//TODO: revisar bien cuando se crea main_gui
			main_gui->setNombre(_entities[c]->getNombre());
}

void ClienteArgentum::renderLoop()
{
	_run = true;


	main_window= new vmain;
	login_window_added = false;
	_guichan->get_top()->add(main_window,800/2-283/2,600/2-342/2);
	main_gui = new MainGui();
	stringstream temp;
	temp.str(std::string());
	temp << ConfigData::GetPath("mapas") << "Mapa" << 34 << ".map";
	ClienteArgentum::instancia()->ActualMap()->loadMapFile(temp.str().c_str(), ClienteArgentum::instancia()->_engine->getGrhManager(), ClienteArgentum::instancia()->_engine->getImageManager());
	_engine->setCurrentLight(20,20,20);
	_engine->setTargetLight(160,160,160);
	_engine->raining = true;

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
		if((status==Logged)&&(currentChar>0)){
			_engine->render( _entities[currentChar]->getPos().x, _entities[currentChar]->getPos().y ,false);
			if((recv_pong>sent_ping)&&((recv_pong+1000)<SDL_GetTicks()))
			{
				sent_ping = SDL_GetTicks();
				comu->Ping();
			}
		}else
		{
			_engine->render(30,77,true);
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
	}else if(actionEvent.getId()==std::string("LOGIN_DIALOG"))
	{
		if(!login_window_added)
		{
			login_window = new vlogin;
			_guichan->get_top()->add(login_window,800/2-login_window->getWidth()/2, 600/2-login_window->getHeight()/2);
			login_window_added = true;
		}
		
	}else if(actionEvent.getId()==std::string("EXIT"))
	{
		_run = false;
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
		status=NewChar;
		_guichan->get_top()->remove(main_window);
		if(!creation_window) creation_window= new vcreation;
		_guichan->get_top()->add(creation_window);
		creation_window->resetDados();
		comu->GetClasesInfo();
		comu->GetCiudadesInfo();
		comu->GetRazasInfo();
		comu->Dados();
	}else if(actionEvent.getId()==std::string("MAIN"))
	{
		sock->cerrar();
		status=Welcome;
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
	}else if(actionEvent.getId()==std::string("INVENTORY_TOGGLE"))
	{
		UserInventory.set_visibility(!UserInventory.is_visible());
	}else if(actionEvent.getId()==std::string("SPELLS_TOGGLE"))
	{
		VHechizos.set_visibility(!VHechizos.is_visible());
	}else if(actionEvent.getId()==std::string("STATS_TOGGLE"))
	{
		if(!ve)
			ve = new vestadisticas();

		if(!ve->is_visible())
		{
			_guichan->get_top()->add(ve,150,50);
			comu->RequestSkills();
			ve->set_visible(true);
		}else
		{
			ve->set_visible(false);
			_guichan->get_top()->remove(ve);
		}

	}else if(actionEvent.getId().substr(0,5)==std::string("HECHI"))
	{
		if(VHechizos.is_visible())
		{
			std::stringstream num(actionEvent.getId().substr(5));
			int n;
			num >> n;

			if(VHechizos.hechis[n]->puede_usar())
			{
				SDL_SetCursor(ccruz);
				using_spell=n;
			}
		}
	}

}


void ClienteArgentum::socket_onEvent(csocket* sock, SocketEventsTypes ev_type, int param1)
{
	switch (ev_type)
	{
	case csocket::EventListener::SOCKEVENT_CONNECT:
		cout << "Conectado!" << endl;
		if(status!=NewChar){
			comu->Login(login_window->get_user(),login_window->get_pass(),0,1,0);
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
		//logged = false;
		if(status==NewChar)
		{
			sock->conectar(main_window->getHost().c_str(), main_window->getPort());
		}
		break;
	}
}


void ClienteArgentum::command_parse(std::string what)
{
	std::string command;
	std::string arguments;

	command = what.substr(1,what.find_first_of(" ")-1);

	int arg = what.find_first_of(" ");
	if(arg!=std::string::npos)
	{
		arguments=what.substr(arg+1);
	}
	
	if(strcmp(command.c_str(),"online")==0)//TODO en windows stricmp, en linux?
	{
		comu->Online();
	}else if(strcmp(command.c_str(),"meditar")==0)//TODO en windows stricmp, en linux?
	{
		comu->Meditar();
	}else if(strcmp(command.c_str(),"ira")==0)
	{
		comu->GoToChar(arguments);
	}else if(strcmp(command.c_str(),"telep")==0)
	{
		int t1 = arguments.find_first_of("\"");
		int t2 = arguments.find_first_of("\"",t1+1);
		std::string user = arguments.substr(t1+1,t2-1);
		std::stringstream numbers;
		numbers << arguments.substr(t2+1);
		unsigned int map,x,y;
		numbers >> map >> x >> y;
		comu->WarpChar(user,map,x,y);
	}else if(strcmp(command.c_str(),"test")==0)
	{//Test/Development commands
		std::stringstream tmp(arguments);
		std::string what;
		tmp >> what;
		if(what=="fx")
		{
			unsigned int num;
			tmp >> num;
			test_fx = num;
			_entities[currentChar]->setFx(BodyData(),test_fx,-1);
		}else if(what=="part")
		{
			unsigned int num;
			tmp >> num;
			test_particle = num;
			_entities[currentChar]->setPart(test_particle);
		}
	}
}

void ClienteArgentum::setParalizado(bool b)
{
	paralizado=b;
}


void ClienteArgentum::setMeditando(bool b)
{
	meditando=b;
}

void ClienteArgentum::Razas(int n, std::string i)
{
	if(creation_window)
	{
		creation_window->setRaza(n,i);
	}
}

void ClienteArgentum::Ciudades(int n, std::string i)
{
	if(creation_window)
	{
		creation_window->setCiudad(n,i);
	}
}

void ClienteArgentum::Clases(int n, std::string i)
{
	if(creation_window)
	{
		creation_window->setClase(n,i);
	}
}

void ClienteArgentum::ModifySkills(std::vector<Sint8> *s, int free)
{
	for(int i=0;i<21;i++)
	{
		Skills()[i].set((*s)[i]);
	}
	Skills().setFree(free);
	Skills().notify();
	comu->ModifySkills(s);
}

void ClienteArgentum::Pong()
{
	recv_pong = SDL_GetTicks();
	latency = recv_pong - sent_ping;
}
