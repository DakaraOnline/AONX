/***************************************************************************
 *   Copyright (C) 2007 by Esteban Torre   *
 *   esteban.torre@gmail.com   *
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
#include "console.h"
#include "paquete.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>

#include "aomap.h"
#include "console.h"
#include "clienteargentum.h"
#include "entity.h"
#include "linked_ptr.h"
#include "configdata.h"
#include "audioengine.h"
#include "verror.h"
#include "fonts.h"

using namespace std;
//#define DEBUG
/*
-----------------------------------------------------------------------
----------------------Paquetes-del-Servidor----------------------------
-----------------------------------------------------------------------
*/

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Logged
/// Sin parametros.
/// @brief: Avisa al cliente que el personaje ya esta logueado en el servidor

bool cPSLogged::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSLogged::exec(){
	#ifdef DEBUG
	cout << "Logged" << endl;
	#endif
	Consola::buffer << "Logged!" << endl;
	ClienteArgentum::instancia()->set_logged(true);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RemoveDialogs
/// Sin parámetros
/// @brief: Elimina todos los diálogos

cPSRemoveDialogs::cPSRemoveDialogs(){
}

cPSRemoveDialogs::~cPSRemoveDialogs(){
}

bool cPSRemoveDialogs::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSRemoveDialogs::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: RemoveDialogs" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RemoveCharDialog
/// @param: Sint16 charindex
/// @brief: Elimina el diálogo de Charindex.

cPSRemoveCharDialog::cPSRemoveCharDialog(){
}

cPSRemoveCharDialog::~cPSRemoveCharDialog(){
}

bool cPSRemoveCharDialog::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	return true;
	
}

void cPSRemoveCharDialog::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: RemoveCharDialog; charindex=" << charindex << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NavigateToggle
/// Sin parámetros.
/// @brief: Cambia el estado del personaje actual entre navegando y "no navegando".


cPSNavigateToggle::cPSNavigateToggle(){
}

cPSNavigateToggle::~cPSNavigateToggle(){
}

bool cPSNavigateToggle::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSNavigateToggle::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: NavigateToggle" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Disconnect
/// Sin parámetros
/// @brief: Alerta al cliente de una desconexión inminente.

cPSDisconnect::cPSDisconnect(){
}

cPSDisconnect::~cPSDisconnect(){
}

bool cPSDisconnect::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSDisconnect::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: Disconnect" << endl;
        #endif
	ClienteArgentum::instancia()->set_logged(false);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CommerceEnd
/// Sin par�metros.
/// @brief: Informa de la finalización del comercio con el npc.

cPSCommerceEnd::cPSCommerceEnd(){
}

cPSCommerceEnd::~cPSCommerceEnd(){
}

bool cPSCommerceEnd::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSCommerceEnd::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CommerceEnd" << endl;
        #endif
	ClienteArgentum::instancia()->NPCInventory.set_visibility(false);
	ClienteArgentum::instancia()->UserInventory.show_prices(false);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BankEnd
/// Sin parámetros
/// @brief: Informa al cliente de la finalización del diálogo con el banco.

cPSBankEnd::cPSBankEnd(){
}

cPSBankEnd::~cPSBankEnd(){
}

bool cPSBankEnd::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSBankEnd::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BankEnd" << endl;
        #endif
	ClienteArgentum::instancia()->BankInventory.set_visibility(false);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CommerceInit
/// Sin parámetros
/// @brief: Informa al cliente del comienzo del di�logo de comercio con un NPC.

cPSCommerceInit::cPSCommerceInit(){
}

cPSCommerceInit::~cPSCommerceInit(){
}

bool cPSCommerceInit::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSCommerceInit::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CommerceInit" << endl;
        #endif
	ClienteArgentum::instancia()->NPCInventory.set_visibility(true);
	ClienteArgentum::instancia()->NPCInventory.clear();
	ClienteArgentum::instancia()->NPCInventory.show_prices(true);
	ClienteArgentum::instancia()->UserInventory.show_prices(true);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BankInit
/// Sin parámetros.
/// @brief: Informa al cliente del comienzo del di�logo del banco.

cPSBankInit::cPSBankInit(){
}

cPSBankInit::~cPSBankInit(){
}

bool cPSBankInit::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSBankInit::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BankInit" << endl;
        #endif
	ClienteArgentum::instancia()->BankInventory.set_visibility(true);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserCommerceInit
/// Sin parámetros.
/// @brief: Informa al cliente el comienzo del diálogo de comercio entre usuarios.

cPSUserCommerceInit::cPSUserCommerceInit(){
}

cPSUserCommerceInit::~cPSUserCommerceInit(){
}

bool cPSUserCommerceInit::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSUserCommerceInit::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserCommerceInit" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserCommerceEnd
/// Sin parámetros
/// @brief: Informa al cliente de la finalización del diálogo de comercio entre usuarios.

cPSUserCommerceEnd::cPSUserCommerceEnd(){
}

cPSUserCommerceEnd::~cPSUserCommerceEnd(){
}

bool cPSUserCommerceEnd::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSUserCommerceEnd::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserCommerceEnd" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowBlacksmithForm
/// Sin parámetros.
/// @brief: Solicita al cliente que muestre el diálogo de Herrería.

cPSShowBlacksmithForm::cPSShowBlacksmithForm(){
}

cPSShowBlacksmithForm::~cPSShowBlacksmithForm(){
}

bool cPSShowBlacksmithForm::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSShowBlacksmithForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowBlacksmithForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowCarpenterForm
/// Sin parámetros.
/// @brief: Solicita al cliente que muestre el diálogo de Carpintería.

cPSShowCarpenterForm::cPSShowCarpenterForm(){
}

cPSShowCarpenterForm::~cPSShowCarpenterForm(){
}

bool cPSShowCarpenterForm::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSShowCarpenterForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowCarpenterForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NPCSwing
/// Sin parámetros.
/// @brief: Informa al cliente que un NPC fall� al intentar pegarle al usuario.

cPSNPCSwing::cPSNPCSwing(){
}

cPSNPCSwing::~cPSNPCSwing(){
}

bool cPSNPCSwing::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSNPCSwing::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: NPCSwing" << endl;
        #endif
	Consola::buffer << "La criatura fall� el golpe." <<  std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NPCKillUser
/// Sin parámetros.
/// @brief: Informa al cliente que un NPC mat� al usuario.

cPSNPCKillUser::cPSNPCKillUser(){
}

cPSNPCKillUser::~cPSNPCKillUser(){
}

bool cPSNPCKillUser::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSNPCKillUser::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: NPCKillUser" << endl;
        #endif
	Consola::buffer << "La criatura te ha matado!" << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlockedWithShieldUser
/// Sin parámetros.
/// @brief: Informa al cliente que el usuario rechaz� un ataque con el escudo.

cPSBlockedWithShieldUser::cPSBlockedWithShieldUser(){
}

cPSBlockedWithShieldUser::~cPSBlockedWithShieldUser(){
}

bool cPSBlockedWithShieldUser::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSBlockedWithShieldUser::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BlockedWithShieldUser" << endl;
        #endif
	Consola::buffer << "Has bloqueado el golpe con el escudo!" << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlockedWithShieldOther
/// Sin parámetros.
/// @brief: Informa al cliente que el ataque efectuado por el usuario fue bloqueado con un escudo

cPSBlockedWithShieldOther::cPSBlockedWithShieldOther(){
}

cPSBlockedWithShieldOther::~cPSBlockedWithShieldOther(){
}

bool cPSBlockedWithShieldOther::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSBlockedWithShieldOther::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BlockedWithShieldOther" << endl;
        #endif
	Consola::buffer << "El usuario a bloqueado el golpe con su escudo!" << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserSwing
/// Sin parámetros.
/// @brief: Informa al cliente que el usuario falló al atacar.

cPSUserSwing::cPSUserSwing(){
}

cPSUserSwing::~cPSUserSwing(){
}

bool cPSUserSwing::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSUserSwing::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserSwing" << endl;
        #endif
	//Consola::buffer << "Has fallado.\n";
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setChat("Has Fallado!");
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setChatFont(Fonts::sans_12_red());
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateNeeded
/// Sin parámetros.
/// @brief: Informa al cliente que requiere ser actualizado.

cPSUpdateNeeded::cPSUpdateNeeded(){
}

cPSUpdateNeeded::~cPSUpdateNeeded(){
}

bool cPSUpdateNeeded::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSUpdateNeeded::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateNeeded" << endl;
        #endif
	Consola::buffer << "El cliente está desactualizado." << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SafeModeOn
/// Sin parámetros.
/// @brief: Informa al cliente que está en modo seguro.

cPSSafeModeOn::cPSSafeModeOn(){
}

cPSSafeModeOn::~cPSSafeModeOn(){
}

bool cPSSafeModeOn::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSSafeModeOn::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: SafeModeOn" << endl;
        #endif
	Consola::buffer << "Modo seguro habilitado." << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SafeModeOff
/// Sin parámetros.
/// @brief: Informa al cliente que ya no está en modo seguro.

cPSSafeModeOff::cPSSafeModeOff(){
}

cPSSafeModeOff::~cPSSafeModeOff(){
}

bool cPSSafeModeOff::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSSafeModeOff::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: SafeModeOff" << endl;
        #endif
	Consola::buffer << "Modo seguro deshabilitado." << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NobilityLost
/// Sin parámetros
/// @brief: Informa al cliente que el usuario perdió su nobleza.

cPSNobilityLost::cPSNobilityLost(){
}

cPSNobilityLost::~cPSNobilityLost(){
}

bool cPSNobilityLost::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSNobilityLost::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: NobilityLost" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CantUseWhileMeditating
/// Sin parámetros.
/// @brief: Informa al cliente que no se pueden utilizar items mientras se medita.

cPSCantUseWhileMeditating::cPSCantUseWhileMeditating(){
}

cPSCantUseWhileMeditating::~cPSCantUseWhileMeditating(){
}

bool cPSCantUseWhileMeditating::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSCantUseWhileMeditating::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CantUseWhileMeditating" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateSta
/// @param: Sint16 stamina
/// @brief: Informa al cliente la cantidad actual de energía.

cPSUpdateSta::cPSUpdateSta(){
}

cPSUpdateSta::~cPSUpdateSta(){
}

bool cPSUpdateSta::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&stamina);
	return true;
}

void cPSUpdateSta::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateSta; stamina=" << stamina << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setStamina(stamina);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateMana
/// @param: Sint16 mana
/// @brief: Informa al cliente que la cantidad actual de maná es mana.

cPSUpdateMana::cPSUpdateMana(){
}

cPSUpdateMana::~cPSUpdateMana(){
}

bool cPSUpdateMana::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&mana);
	return true;
}

void cPSUpdateMana::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateMana; mana=" << mana << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setMana(mana);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateHP
/// @param: Sint16 hp
/// @brief: Informa al cliente que la cantidad actual de vida es hp.

cPSUpdateHP::cPSUpdateHP(){
}

cPSUpdateHP::~cPSUpdateHP(){
}

bool cPSUpdateHP::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&hp);
	return true;
}

void cPSUpdateHP::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateHP; hp=" << hp << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setVida(hp);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateGold
/// @param: Sint32 gold
/// @brief: Informa al cliente que la cantidad actual de oro es gold.

cPSUpdateGold::cPSUpdateGold(){
}

cPSUpdateGold::~cPSUpdateGold(){
}

bool cPSUpdateGold::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&gold);
	return true;
}

void cPSUpdateGold::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateGold; gold=" << gold << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setOro(gold);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateExp
/// @param: Sint32 exp
/// @brief: Informa al cliente que la cantidad actual de experiencia es exp.

cPSUpdateExp::cPSUpdateExp(){
}

cPSUpdateExp::~cPSUpdateExp(){
}

bool cPSUpdateExp::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&exp);
	return true;
}

void cPSUpdateExp::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateExp; exp=" << exp << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setExp(exp);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeMap
/// @param: @Sint16 map
/// @param: @Sint16 version
/// @brief: Informa al cliente el cambio de mapa a map, cuya version es version.

cPSChangeMap::cPSChangeMap(){
}

cPSChangeMap::~cPSChangeMap(){
}

bool cPSChangeMap::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&map);
	q->Read(&version);
	return true;
}

void cPSChangeMap::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ChangeMap; map=" << map << "; version=" << version << endl;
        #endif
	stringstream temp;
	temp.str(std::string());
	temp << ConfigData::GetPath("mapas") << "Mapa" << map << ".map";
	ClienteArgentum::instancia()->ActualMap()->loadMapFile(temp.str().c_str());
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PosUpdate
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Informa al cliente la posición actual del usuario.

cPSPosUpdate::cPSPosUpdate(){
}

cPSPosUpdate::~cPSPosUpdate(){
}

bool cPSPosUpdate::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&x);
	q->Read(&y);
	return true;
}

void cPSPosUpdate::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: PosUpdate; x=" << (int)x << "; y=" << (int)y << endl;
        #endif
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setPos(ao::Pos(x-1,y-1));
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NPCHitUser
/// @param: Sint8 donde
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que un NPC le pegó al usuario en donde por cuanto.

cPSNPCHitUser::cPSNPCHitUser(){
}

cPSNPCHitUser::~cPSNPCHitUser(){
}

bool cPSNPCHitUser::unserialize(cByteQueue* q){
	if(q->len()<4) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&donde);
	q->Read(&cuanto);
	return true;
}

void cPSNPCHitUser::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: NPCHitUser; donde=" << (int)donde << "; cuanto=" << cuanto << endl;
        #endif
	Consola::buffer << "La criatura te ha pegado por " << cuanto << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserHitNPC
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que el usuario le pegó por cuanto al un NPC.

cPSUserHitNPC::cPSUserHitNPC(){
}

cPSUserHitNPC::~cPSUserHitNPC(){
}

bool cPSUserHitNPC::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&cuanto);
	return true;
}

void cPSUserHitNPC::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserHitNPC; cuanto=" << cuanto << endl;
        #endif
	std::stringstream pip;
	pip << cuanto;
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setChat(pip.str());
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setChatFont(Fonts::sans_12_red());
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserAttackedSwing
/// @param: string username
/// @brief: Aparentemente charindex atacó al usuario y falló.

cPSUserAttackedSwing::cPSUserAttackedSwing(){
}

cPSUserAttackedSwing::~cPSUserAttackedSwing(){
}

bool cPSUserAttackedSwing::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(username,1024-1,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSUserAttackedSwing::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserAttackedSwing; username=" << username << endl;
        #endif
	Consola::buffer << username << " te ataco y fallo.";
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserHittedByUser
/// @param: Sint16 charindex
/// @param: Sint8 donde
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que charindex le pego al usuario por cuanto en donde.

cPSUserHittedByUser::cPSUserHittedByUser(){
}

cPSUserHittedByUser::~cPSUserHittedByUser(){
}

bool cPSUserHittedByUser::unserialize(cByteQueue* q){
	if(q->len()<6) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	q->Read(&donde);
	q->Read(&cuanto);
	return true;
}

void cPSUserHittedByUser::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserHittedByUser; charindex=" << charindex << "; donde=" << (int)donde << "; cuanto=" << cuanto << endl;
        #endif
	std::stringstream pip;
	pip << cuanto;
	ClienteArgentum::instancia()->_entities[charindex]->setChat(pip.str());
	ClienteArgentum::instancia()->_entities[charindex]->setChatFont(Fonts::sans_12_red());
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserHittedUser
/// @param: Sint16 charindex
/// @param: Sint8 donde
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que el usuario le pegó a charindex en donde por cuanto.

cPSUserHittedUser::cPSUserHittedUser(){
}

cPSUserHittedUser::~cPSUserHittedUser(){
}

bool cPSUserHittedUser::unserialize(cByteQueue* q){
	if(q->len()<6) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	q->Read(&donde);
	q->Read(&cuanto);
	return true;
}

void cPSUserHittedUser::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserHittedUser charindex=" << charindex << "; donde=" << donde << "; cuanto=" << cuanto << endl;
        #endif
	std::stringstream pip;
	pip << cuanto;
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setChat(pip.str());
	ClienteArgentum::instancia()->_entities[ClienteArgentum::instancia()->getCurrentChar()]->setChatFont(Fonts::sans_12_red());
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// Paquete: ChatOverHead
/// @param: char* text
/// @param: Sint16 charindex
/// @param: Sint8 r
/// @param: Sint8 g
/// @param: Sint8 b
/// @brief: Informa al cliente que cree un diálogo sobre charindex con el texto text y el color rgb.

cPSChatOverHead::cPSChatOverHead(){
}

cPSChatOverHead::~cPSChatOverHead(){
}

bool cPSChatOverHead::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(text,1024-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&charindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&r,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&g,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&b,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSChatOverHead::exec(){
	char* p;
	if((p=strstr(text,"\r")))
	{
		*p=' ';//TODO sacame cuando no hay m�s de estas mierdas en los recursos
	}
        #ifdef DEBUG
        cout << "Paquete.cpp: ChatOverHead; text=" << text << "; charindex=" << charindex << "; r,g,b=" << (int)r << "," << (int)g << "," << (int)b << endl;
        #endif

	ClienteArgentum::instancia()->_entities[charindex]->setChat(text);
	ClienteArgentum::instancia()->_entities[charindex]->setChatFont(Fonts::sans_12_white());
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ConsoleMsg
/// @param: char* text
/// @param: Sint8 fontindex
/// @brief: Informa al cliente de un mensaje de consola text con la fuente fontindex.

cPSConsoleMsg::cPSConsoleMsg(){
}

cPSConsoleMsg::~cPSConsoleMsg(){
}

bool cPSConsoleMsg::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(text,1024-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&fontindex,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSConsoleMsg::exec(){
	char* p;
	if((p=strstr(text,"\r")))
	{
		*p=' ';//TODO sacame cuando no hay m�s de estas mierdas en los recursos
	}
        #ifdef DEBUG
        cout << "Paquete.cpp: ConsoleMsg; text=" << text << "; fontindex=" << (int) fontindex << endl;
        #endif
	Consola::buffer << text;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: GuildChat
/// @param: char* text
/// @brief: Informa al cliente de un diálogo de clan con el contenido text.

cPSGuildChat::cPSGuildChat(){
}

cPSGuildChat::~cPSGuildChat(){
}

bool cPSGuildChat::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(text,1024-1,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSGuildChat::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: GuildChat; text=" << text << endl;
        #endif
	Consola::buffer << "GuildChat: " << text << std::endl;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowMessageBox
/// @param: char* text
/// @brief: Envia un mensaje al cliente para ser mostrado al usuario.

cPSShowMessageBox::cPSShowMessageBox(){
}

cPSShowMessageBox::~cPSShowMessageBox(){
}

bool cPSShowMessageBox::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(text,1024-1,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSShowMessageBox::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowMessageBox; text=" << text << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserIndexInServer
/// @param: Sint16 userindex
/// @brief: Informa al cliente que el índice del usuario en el servidor es userindex (no confundir con charindex)

cPSUserIndexInServer::cPSUserIndexInServer(){
}

cPSUserIndexInServer::~cPSUserIndexInServer(){
}

bool cPSUserIndexInServer::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&userindex);
	return true;
}

void cPSUserIndexInServer::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserIndexInServer; userindex=" << userindex << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserCharIndexInServer
/// @param: Sint16 charindex
/// @brief: Informa al cliente que el índice del char del usuario es charindex

cPSUserCharIndexInServer::cPSUserCharIndexInServer(){
}

cPSUserCharIndexInServer::~cPSUserCharIndexInServer(){
}

bool cPSUserCharIndexInServer::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	return true;
}

void cPSUserCharIndexInServer::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UserCharIndexInServer; charindex=" << charindex << endl;
        #endif
	ClienteArgentum::instancia()->setCurrentChar(charindex);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterCreate
/// @param: Sint16 charindex
/// @param: Sint16 bodyindex
/// @param: Sint16 headindex
/// @param: Sint8 heading
/// @param: Sint8 x
/// @param: Sint8 y
/// @param: Sint16 weaponindex
/// @param: Sint16 shieldindex
/// @param: Sint16 helmetindex
/// @param: Sint16 fxindex
/// @param: Sint16 fxloops
/// @param: char* nombre
/// @param: Sint8 criminal
/// @param: Sint8 privs
/// @brief: Informa al cliente la creación de un char en una posición del mapa actual.

cPSCharacterCreate::cPSCharacterCreate(){
}

cPSCharacterCreate::~cPSCharacterCreate(){
}

bool cPSCharacterCreate::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&charindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&bodyindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&headindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&heading,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&x,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&y,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&weaponindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&shieldindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&helmetindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&fxindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&fxloops,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&criminal,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&privs,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSCharacterCreate::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CharacterCreate; charindex=" << charindex << "; bodyindex=" << bodyindex;
	cout << ";headindex=" << headindex << ";heading=" << (int) heading << ";x,y=" << (int)x << "," << (int)y;
	cout << ";weaponindex=" << weaponindex << ";shieldindex=" << shieldindex << ";helmetindex=";
	cout << helmetindex << ";fxindex=" << fxindex << ";fxloops=" << fxloops << ";nombre=" << nombre;
	cout << ";criminal=" << (int) criminal << ";privs=" << (int) privs << endl;
        #endif
	
	ao::MapFile_ptr _map= ClienteArgentum::instancia()->ActualMap();
	ao::BodyData_ptr _bodyData = ClienteArgentum::instancia()->BodyData();
	ClienteArgentum::instancia()->_entities[charindex]= ao::Entity_ptr(new ao::Entity( _map, ao::Pos( x-1, y-1), (ao::Entity::Heading)(heading) ));
	//ao::Entity* ent = new ao::Entity( _map, ao::Pos( x-1, y-1), (ao::Entity::Heading)(heading-1) );
	ClienteArgentum::instancia()->_entities[charindex]->loadData( _bodyData,bodyindex-1, headindex-1, helmetindex-1, weaponindex-1, shieldindex -1);
	ClienteArgentum::instancia()->_entities[charindex]->setNombre(std::string(nombre));

}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterRemove
/// @param: Sint16 charindex
/// @brief: Informa al cliente de la eliminación del char charindex.

cPSCharacterRemove::cPSCharacterRemove(){
}

cPSCharacterRemove::~cPSCharacterRemove(){
}

bool cPSCharacterRemove::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	return true;
}

void cPSCharacterRemove::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CharacterRemove; charindex=" << charindex << endl;
        #endif
	ClienteArgentum::instancia()->_entities[charindex]->removeFromMap(); //TODO: revisar esto
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterMove
/// @param: Sint16 charindex
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Informa al cliente del movimiento de charindex a x,y

cPSCharacterMove::cPSCharacterMove(){
}

cPSCharacterMove::~cPSCharacterMove(){
}

bool cPSCharacterMove::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	q->Read(&x);
	q->Read(&y);
	return true;
}

void cPSCharacterMove::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CharacterMove; charindex=" << charindex << "; x,y=" << (int)x << "," << (int)y << endl;
        #endif
	ClienteArgentum::instancia()->_entities[charindex]->movePos(ao::Pos(x-1,y-1));
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterChange
/// @param: Sint16 charindex
/// @param: Sint16 bodyindex
/// @param: Sint16 headindex //verifica si es la cabeza de muerto le setea la flag.
/// @param: Sint8 heading
/// @param: Sint16 weaponindex
/// @param: Sint16 shieldindex
/// @param: Sint16 helmetindex
/// @param: Sint16 fxindex
/// @param: Sint16 fxloops
/// @brief: Informa al cliente de cambios en el char charindex.

cPSCharacterChange::cPSCharacterChange(){
}

cPSCharacterChange::~cPSCharacterChange(){
}

bool cPSCharacterChange::unserialize(cByteQueue* q){
	if(q->len()<18) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	q->Read(&bodyindex);
	q->Read(&headindex);
	q->Read(&heading);
	q->Read(&weaponindex);
	q->Read(&shieldindex);
	q->Read(&helmetindex);
	q->Read(&fxindex);
	q->Read(&fxloops);
	return true;
}

void cPSCharacterChange::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CharacterChange; charindex=" << charindex << "; bodyindex=" << bodyindex;
	cout << ";headindex=" << headindex << ";heading=" << (int) heading;
	cout << ";weaponindex=" << weaponindex << ";shieldindex=" << shieldindex << ";helmetindex=";
	cout << helmetindex << ";fxindex=" << fxindex << ";fxloops=" << endl;
        #endif
	ao::BodyData_ptr _bodyData = ClienteArgentum::instancia()->BodyData();
	ClienteArgentum::instancia()->_entities[charindex]->loadData( _bodyData,bodyindex-1, headindex-1, helmetindex-1, weaponindex-1, shieldindex -1);
	ClienteArgentum::instancia()->_entities[charindex]->setHeading((ao::Entity::Heading)(heading));

	
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ObjectCreate
/// @param: Sint8 x
/// @param: Sint8 y
/// @param: Sint16 grhindex
/// @brief: Informa al cliente de la creación de un objeto grhindex en x,y

cPSObjectCreate::cPSObjectCreate(){
}

cPSObjectCreate::~cPSObjectCreate(){
}

bool cPSObjectCreate::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&x);
	q->Read(&y);
	q->Read(&grhindex);
	return true;
}

void cPSObjectCreate::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ObjectCreate; x,y=" << (int)x << "," << (int)y << "; grhindex=" << grhindex << endl;
        #endif
	//TODO: esto es MUY hardcoded.
	ClienteArgentum::instancia()->ActualMap()->getTile( ao::Pos( x-1, y-1 ) ).obj.init( grhindex );
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ObjectDelete
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Informa al cliente de la remoción del objeto en x,y.

cPSObjectDelete::cPSObjectDelete(){
}

cPSObjectDelete::~cPSObjectDelete(){
}

bool cPSObjectDelete::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&x);
	q->Read(&y);
	return true;
}

void cPSObjectDelete::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ObjectDelete; x,y=" << (int)x << "," << (int)y << endl;
        #endif
	ClienteArgentum::instancia()->ActualMap()->getTile( ao::Pos( x-1, y-1 ) ).obj.index=0;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlockPosition
/// @param: Sint8 x;
/// @param: Sint8 y;
/// @param: Sint8 blocked
/// @brief: Informa al cliente si un tile está o no bloqueado en x,y.

cPSBlockPosition::cPSBlockPosition(){
}

cPSBlockPosition::~cPSBlockPosition(){
}

bool cPSBlockPosition::unserialize(cByteQueue* q){
	if(q->len()<4) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&x);
	q->Read(&y);
	q->Read(&blocked);
	return true;
}

void cPSBlockPosition::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BlockPosition; x,y=" << (int)x << "," << (int)y << "; blocked=" << (int) blocked << endl;
        #endif
	ClienteArgentum::instancia()->ActualMap()->getTile( ao::Pos( x-1, y-1 ) ).blocked = bool(blocked);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PlayMIDI
/// @param: Sint8 num
/// @param: Sint16 nose
/// @brief: Indica al cliente que reproduzca el midi num.

cPSPlayMIDI::cPSPlayMIDI(){
}

cPSPlayMIDI::~cPSPlayMIDI(){
}

bool cPSPlayMIDI::unserialize(cByteQueue* q){
	if(q->len()<4) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&num);
	q->Read(&nose);
	return true;
}

void cPSPlayMIDI::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: PlayMIDI; num=" << (int) num << "; nose=" << nose << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PlayWave
/// @param: Sint8 num
/// @brief: Indica al cliente que reproduzca el wav num.

cPSPlayWave::cPSPlayWave(){
}

cPSPlayWave::~cPSPlayWave(){
}

bool cPSPlayWave::unserialize(cByteQueue* q){
	if(q->len()<2) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&num);
	return true;
}

void cPSPlayWave::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: PlayWave; num=" << (int)num << endl;
        #endif
	ClienteArgentum::instancia()->audio()->play_wav(num);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: guildList
/// @param:
/// @brief:

cPSguildList::cPSguildList(){
}

cPSguildList::~cPSguildList(){
}

bool cPSguildList::unserialize(cByteQueue* q){
	return true;
}

void cPSguildList::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: guildList" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PlayFireSound
/// Sin parámetros
/// @brief: Indica al cliente que reproduzca el sonido del fuego.

cPSPlayFireSound::cPSPlayFireSound(){
}

cPSPlayFireSound::~cPSPlayFireSound(){
}

bool cPSPlayFireSound::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSPlayFireSound::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: PlayFireSound" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: AreaChanged
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Indica al cliente un cambio de area a x,y

cPSAreaChanged::cPSAreaChanged(){
}

cPSAreaChanged::~cPSAreaChanged(){
}

bool cPSAreaChanged::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&x);
	q->Read(&y);
	return true;
}

void cPSAreaChanged::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: AreaChanged; x,y=" << (int)x << "," << (int)y << endl;
        #endif
	//FIXME TODO ALL WARNS I ORDER YOU TO SPAWN HERE: Esto es importante de revisar.
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PauseToggle
/// Sin parámetros
/// @brief: Indica al cliente que cambie el estado de pausa.

cPSPauseToggle::cPSPauseToggle(){
}

cPSPauseToggle::~cPSPauseToggle(){
}

bool cPSPauseToggle::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSPauseToggle::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: PauseToggle" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RainToggle
/// Sin parámetros
/// @brief: Indica al cliente que cambie el estado de lluvia.

cPSRainToggle::cPSRainToggle(){
}

cPSRainToggle::~cPSRainToggle(){
}

bool cPSRainToggle::unserialize(cByteQueue* q){
	q->RemoveData(1); //Eliminamos el byte de ID
	return true;
}

void cPSRainToggle::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: RainToggle" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CreateFX
/// @param: Sint16 charindex
/// @param: Sint16 fxindex
/// @param: Sint16 fxloops
/// @brief: Indica al cliente que cree un fx fxindex en charindex con loops fxloops.

cPSCreateFX::cPSCreateFX(){
}

cPSCreateFX::~cPSCreateFX(){
}

bool cPSCreateFX::unserialize(cByteQueue* q){
	if(q->len()<7) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&charindex);
	q->Read(&fxindex);
	q->Read(&fxloops);
	return true;
}

void cPSCreateFX::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CreateFX; charindex=" << charindex << "; fxindex=" << fxindex << ";fxloops=" << fxloops << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateUserStats
/// @param: Sint16 maxhp
/// @param: Sint16 minhp
/// @param: Sint16 maxman
/// @param: Sint16 minman
/// @param: Sint16 maxsta
/// @param: Sint16 minsta
/// @param: Sint32 gold
/// @param: Sint8 lvl
/// @param: Sint32 pasarlvl
/// @param: Sint32 exp
/// @brief: Informa al cliente las stats del usuario.

cPSUpdateUserStats::cPSUpdateUserStats(){
}

cPSUpdateUserStats::~cPSUpdateUserStats(){
}

bool cPSUpdateUserStats::unserialize(cByteQueue* q){
	if(q->len()<26) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&maxhp);
	q->Read(&minhp);
	q->Read(&maxman);
	q->Read(&minman);
	q->Read(&maxsta);
	q->Read(&minsta);
	q->Read(&gold);
	q->Read(&lvl);
	q->Read(&pasarlvl);
	q->Read(&exp);
	return true;
}

void cPSUpdateUserStats::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateUserStats; max/min hp=" << maxhp << "/" << minhp;
	cout << ";max/min man=" << maxman << "/" << minman << "; max/min sta=" << maxsta;
	cout << "/" << minsta << "; gld=" << gold << "; lvl=" << (int) lvl << "; pasarlvl=";
	cout << pasarlvl << ";exp=" << exp << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setMaxVida(maxhp);
	ClienteArgentum::instancia()->get_ministats()->setVida(minhp);
	ClienteArgentum::instancia()->get_ministats()->setMaxMana(maxman);
	ClienteArgentum::instancia()->get_ministats()->setMana(minman);
	ClienteArgentum::instancia()->get_ministats()->setMaxStamina(maxsta);
	ClienteArgentum::instancia()->get_ministats()->setStamina(minsta);
	ClienteArgentum::instancia()->get_ministats()->setMaxExp(pasarlvl);
	ClienteArgentum::instancia()->get_ministats()->setExp(exp);
	ClienteArgentum::instancia()->get_ministats()->setOro(gold);
	ClienteArgentum::instancia()->get_ministats()->setLevel(lvl);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: WorkRequestTarget
/// @param: Sint8 skill
/// @brief: Avisa al usuario que está trabajando en skill.

cPSWorkRequestTarget::cPSWorkRequestTarget(){
}

cPSWorkRequestTarget::~cPSWorkRequestTarget(){
}

bool cPSWorkRequestTarget::unserialize(cByteQueue* q){
	if(q->len()<2) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&skill);
	return true;
}

void cPSWorkRequestTarget::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: WorkRequestTarget; skill=" << (int) skill << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeInventorySlot
/// @param: Sint8 slot
/// @param: Sint16 objindex
/// @param: char* nombre
/// @param: Sint16 cantidad
/// @param: Sint8 equipado
/// @param: Sint16 grhindex
/// @param: Sint8 objtype
/// @param: Sint16 maxhit
/// @param: Sint16 minhit
/// @param: Sint16 defensa
/// @param: Sint32 valor
/// @brief: Pasa al cliente los datos de un item determinado en el inventario.

cPSChangeInventorySlot::cPSChangeInventorySlot(){
}

cPSChangeInventorySlot::~cPSChangeInventorySlot(){
}

bool cPSChangeInventorySlot::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&slot,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&objindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&cantidad,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&equipado,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&grhindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&objtype,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&maxhit,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&minhit,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&defensa,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&valor,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSChangeInventorySlot::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ChangeInventorySlot; slot=" << (int) slot << "; objindex=" << objindex;
	cout << "; nombre=" << nombre << "; cantidad=" << cantidad << "; equipado=" << (int) equipado;
	cout << "; grhindex=" << grhindex << "; objtype=" << (int) objtype << "; maxhit=";
	cout << maxhit << "; minhit=" << minhit << "; defensa=" << defensa << "; valor=" << valor << endl;
        #endif
	ClienteArgentum::instancia()->UserInventory[slot]->objindex=objindex;
	ClienteArgentum::instancia()->UserInventory[slot]->objname=nombre;
	ClienteArgentum::instancia()->UserInventory[slot]->objamount=cantidad;
	ClienteArgentum::instancia()->UserInventory[slot]->isequipped=equipado;
	ClienteArgentum::instancia()->UserInventory[slot]->set_grhindex(grhindex);
	ClienteArgentum::instancia()->UserInventory[slot]->objtype=objtype;
	ClienteArgentum::instancia()->UserInventory[slot]->maxhit=maxhit;
	ClienteArgentum::instancia()->UserInventory[slot]->minhit=minhit;
	ClienteArgentum::instancia()->UserInventory[slot]->objdef=defensa;
	ClienteArgentum::instancia()->UserInventory[slot]->valor=valor;

}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeBankSlot
/// @param: Sint8 slot
/// @param: Sint16 objindex
/// @param: char* nombre
/// @param: Sint16 cantidad
/// @param: Sint16 grhindex
/// @param: Sint8 objtype
/// @param: Sint16 maxhit
/// @param: Sint16 minhit
/// @param: Sint16 def
/// @param: Sint32 valor
/// @brief: Informa al cliente la modificación de un slot del banco.

cPSChangeBankSlot::cPSChangeBankSlot(){
}

cPSChangeBankSlot::~cPSChangeBankSlot(){
}

bool cPSChangeBankSlot::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&slot,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&objindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&cantidad,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&grhindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&objtype,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&maxhit,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&minhit,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&def,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&valor,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSChangeBankSlot::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ChangeBankSlot; slot=" << (int) slot << "; objindex=" << objindex;
	cout << "; nombre=" << nombre << "; cantidad=" << cantidad;
	cout << "; grhindex=" << grhindex << "; objtype=" << (int) objtype << "; maxhit=";
	cout << maxhit << "; minhit=" << minhit << "; defensa=" << def << "; valor=" << valor << endl;
        #endif
	ClienteArgentum::instancia()->BankInventory[slot-1]->objindex=objindex;
	ClienteArgentum::instancia()->BankInventory[slot-1]->objname=nombre;
	ClienteArgentum::instancia()->BankInventory[slot-1]->objamount=cantidad;
	ClienteArgentum::instancia()->BankInventory[slot-1]->set_grhindex(grhindex);
	ClienteArgentum::instancia()->BankInventory[slot-1]->maxhit=maxhit;
	ClienteArgentum::instancia()->BankInventory[slot-1]->minhit=minhit;
	ClienteArgentum::instancia()->BankInventory[slot-1]->objdef=def;
	ClienteArgentum::instancia()->BankInventory[slot-1]->valor=valor;
	ClienteArgentum::instancia()->BankInventory[slot-1]->objtype=objtype;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeSpellSlot
/// @param: Sint8 slot
/// @param: Sint16 hindex (va a userhechizos(slot)?)
/// @param: char* nombre
/// @brief: Informa al cliente el hechizo correspondiente a slot

cPSChangeSpellSlot::cPSChangeSpellSlot(){
}

cPSChangeSpellSlot::~cPSChangeSpellSlot(){
}

bool cPSChangeSpellSlot::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&slot,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&hindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSChangeSpellSlot::exec(){
        #ifdef DEBUG
	cout << "Paquete.cpp: ChangeSpellSlot; slot=" << (int) slot;
	cout << "; hindex=" << hindex << "; nombre=" << nombre << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Atributes
/// @param: Sint8 fuerza
/// @param: Sint8 agilidad
/// @param: Sint8 inteligencia
/// @param: Sint8 carisma
/// @param: Sint8 constitucion
/// @brief: Informa los atributos del usuario actual al cliente

cPSAtributes::cPSAtributes(){
}

cPSAtributes::~cPSAtributes(){
}

bool cPSAtributes::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1); //Eliminamos el byte de ID
	q->Read(&fuerza);
	q->Read(&agilidad);
	q->Read(&inteligencia);
	q->Read(&carisma);
	q->Read(&constitucion);
	return true;
}

void cPSAtributes::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: Atributes; fuerza=" << (int) fuerza << "; agilidad=";
	cout << (int) agilidad << "; inteligencia=" << (int )inteligencia << "; carisma=";
	cout << (int) carisma << "; constitucion=" << (int) constitucion << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlacksmithWeapons
/// @param: Sint16 count 
/// @warning Esto es bastante variable, solo lo des serializo, las variables se pisan
/// struct blacksmithweapon{ char* nombre, Sint16 hierro, Sint16 plata, Sint16 oro, Sint16 windex}
/// @param: blacksmithweapon[count];
/// @brief: Envia las armas que se pueden construir en la herrería.

cPSBlacksmithWeapons::cPSBlacksmithWeapons(){
}

cPSBlacksmithWeapons::~cPSBlacksmithWeapons(){
}

bool cPSBlacksmithWeapons::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&count,offset))<1) return false;
	offset+=tmpoffset;
	for(int i=0;i<count;i++){
		if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&hierro,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&plata,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&oro,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&windex,offset))<1) return false;
		offset+=tmpoffset;
	}
	q->RemoveData(offset);
	return true;
}

void cPSBlacksmithWeapons::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BlacksmithWeapons; count=" << count << " Not fully debugged!" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlacksmithArmors
/// @param: Sint16 count 
/// @warning Esto es bastante variable, solo lo des serializo, las variables se pisan
/// struct blacksmitharmor{ char* nombre, Sint16 hierro, Sint16 plata, Sint16 oro, Sint16 aindex}
/// @param: blacksmitharmor[count];
/// @brief: Envia las armaduras que se pueden construir en la herrería.

cPSBlacksmithArmors::cPSBlacksmithArmors(){
}

cPSBlacksmithArmors::~cPSBlacksmithArmors(){
}

bool cPSBlacksmithArmors::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&count,offset))<1) return false;
	offset+=tmpoffset;
	for(int i=0;i<count;i++){
		if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&hierro,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&plata,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&oro,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&aindex,offset))<1) return false;
		offset+=tmpoffset;
	}
	q->RemoveData(offset);
	return true;
}

void cPSBlacksmithArmors::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BlacksmithArmors; count=" << count << " Not fully debugged!" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CarpenterObjects
/// @param: Sint16 count 
/// @warning Esto es bastante variable, solo lo des serializo, las variables se pisan
/// struct carpenterobject{ char* nombre, Sint16 madera, Sint16 cindex}
/// @param: carpenterobject[count]
/// @brief: Envia los objetos construibles en la carpintaría.

cPSCarpenterObjects::cPSCarpenterObjects(){
}

cPSCarpenterObjects::~cPSCarpenterObjects(){
}

bool cPSCarpenterObjects::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&count,offset))<1) return false;
	offset+=tmpoffset;
	for(int i=0;i<count;i++){
		if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&madera,offset))<1) return false;
		offset+=tmpoffset;
		if((tmpoffset=q->Peek(&cindex,offset))<1) return false;
		offset+=tmpoffset;
	}
	q->RemoveData(offset);
	return true;
}

void cPSCarpenterObjects::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CarpenterObjects; count=" << count << " Not fully debugged!" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RestOK
/// Sin parametros
/// @brief: Informa al cliente que terminó de descansar.

cPSRestOK::cPSRestOK(){
}

cPSRestOK::~cPSRestOK(){
}

bool cPSRestOK::unserialize(cByteQueue* q){
	q->RemoveData(1);//ID
	return true;
}

void cPSRestOK::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: RestOK" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ErrorMsg
/// @param: char* mensaje
/// @brief: Informa al cliente de  un error

cPSErrorMsg::cPSErrorMsg(){
}

cPSErrorMsg::~cPSErrorMsg(){
}

bool cPSErrorMsg::unserialize(cByteQueue* q){
	int offset;
	if((offset=q->ReadString(mensaje,1024-1,1))<1) return false;
	offset++;
	q->RemoveData(offset);
	return true;
}

void cPSErrorMsg::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ErrorMsg: " << mensaje << endl;
        #endif
	ErrorMessage::ShowError(mensaje);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Blind
/// Sin parametros
/// @brief: Informa al cliente que está ciego.

cPSBlind::cPSBlind(){
}

cPSBlind::~cPSBlind(){
}

bool cPSBlind::unserialize(cByteQueue* q){
	q->RemoveData(1);//ID
	return true;
}

void cPSBlind::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: Blind" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Dumb
/// Sin parametros
/// @brief: Informa al cliente que está tonto.

cPSDumb::cPSDumb(){
}

cPSDumb::~cPSDumb(){
}

bool cPSDumb::unserialize(cByteQueue* q){
	q->RemoveData(1);//ID
	return true;
}

void cPSDumb::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: Dumb" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowSignal
/// @param: char* mensaje
/// @param: Sint16 grhindex (i guess?)
/// @brief: Muestra una señal?

cPSShowSignal::cPSShowSignal(){
}

cPSShowSignal::~cPSShowSignal(){
}

bool cPSShowSignal::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(mensaje,256-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&grhindex,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSShowSignal::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowSignal; mensaje=" << mensaje << "; grhindex?=" << grhindex << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeNPCInventorySlot
/// @param: Sint8 slot
/// @param: char* nombre
/// @param: Sint16 cantidad
/// @param: Sint32 valor
/// @param: Sint16 grhindex
/// @param: Sint16 objindex
/// @param: Sint8 objtype
/// @param: Sint16 maxhit
/// @param: Sint16 minhit
/// @param: Sint16 def
/// @brief: Informa al cliente que agregue un slot al inventario del npc.
/// @remarks: El comité de antiestandarización de programación de ao decidió no informar que numero de slot era, por esa razón tube que hacer cosas FEAS. =).

cPSChangeNPCInventorySlot::cPSChangeNPCInventorySlot(){
}

cPSChangeNPCInventorySlot::~cPSChangeNPCInventorySlot(){
}


bool cPSChangeNPCInventorySlot::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->Peek(&slot,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->ReadString(nombre,256-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&cantidad,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&valor,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&grhindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&objindex,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&objtype,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&maxhit,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&minhit,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->Peek(&def,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSChangeNPCInventorySlot::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ChangeNPCInventorySlot; nombre=" << nombre;
	cout << "; cantidad=" << cantidad << "; valor=" << valor << ";grhindex=";
	cout << grhindex << "; objindex=" << objindex << "; objtype=";
	cout << (int) objtype << "; maxhit=" << maxhit << ";minhit=" << minhit;
	cout << ";def=" << def << endl;
        #endif
	ClienteArgentum::instancia()->NPCInventory[slot]->objindex=objindex;
	ClienteArgentum::instancia()->NPCInventory[slot]->objname=nombre;
	ClienteArgentum::instancia()->NPCInventory[slot]->objamount=cantidad;
	ClienteArgentum::instancia()->NPCInventory[slot]->set_grhindex(grhindex);
	ClienteArgentum::instancia()->NPCInventory[slot]->maxhit=maxhit;
	ClienteArgentum::instancia()->NPCInventory[slot]->minhit=minhit;
	ClienteArgentum::instancia()->NPCInventory[slot]->objdef=def;
	ClienteArgentum::instancia()->NPCInventory[slot]->valor=valor;
	ClienteArgentum::instancia()->NPCInventory[slot]->objtype=objtype;
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateHungerAndThirst
/// @param: Sint8 maxagu
/// @param: Sint8 minagu
/// @param: Sint8 maxham
/// @param: Sint8 minham
/// @brief: Informa al cliente el estado de hambre y sed.

cPSUpdateHungerAndThirst::cPSUpdateHungerAndThirst(){
}

cPSUpdateHungerAndThirst::~cPSUpdateHungerAndThirst(){
}

bool cPSUpdateHungerAndThirst::unserialize(cByteQueue* q){
	if(q->len()<5) return false;
	q->RemoveData(1);//id
	q->Read(&maxagu);
	q->Read(&minagu);
	q->Read(&maxham);
	q->Read(&minham);
	return true;
}

void cPSUpdateHungerAndThirst::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: UpdateHungerAndThirst; maxagu=" << (int) maxagu;
	cout << "; minagu=" << (int) minagu << "; maxham=" << (int) maxham << "; minham";
	cout << (int) minham << endl;
        #endif
	ClienteArgentum::instancia()->get_ministats()->setMaxSed(maxagu);
	ClienteArgentum::instancia()->get_ministats()->setSed(minagu);
	ClienteArgentum::instancia()->get_ministats()->setMaxHambre(maxham);
	ClienteArgentum::instancia()->get_ministats()->setHambre(minham);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Fame
/// @param: Sint32 asesino
/// @param: Sint32 bandido
/// @param: Sint32 burgues
/// @param: Sint32 ladron
/// @param: Sint32 noble
/// @param: Sint32 plebeyo
/// @param: Sint32 promedio
/// @brief: Informa la fama del usuario.

cPSFame::cPSFame(){
}

cPSFame::~cPSFame(){
}

bool cPSFame::unserialize(cByteQueue* q){
	if(q->len()<29) return false;
	q->RemoveData(1);//ID;
	q->Read(&asesino);
	q->Read(&bandido);
	q->Read(&burgues);
	q->Read(&ladron);
	q->Read(&noble);
	q->Read(&plebeyo);
	q->Read(&promedio);
	return true;
}

void cPSFame::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: Fame; asesino=" << asesino << "; bandido=";
	cout << bandido << "; burgues=" << burgues << ";ladron=" << ladron;
	cout << "; noble=" << noble << "; plebeyo=" << plebeyo << ";promedio=";
	cout << promedio << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: MiniStats
/// @param: Sint32 ciudadanosmatados
/// @param: Sint32 criminalesmatados
/// @param: Sint32 usuariosmatados
/// @param: Sint16 npcsmatados
/// @param: Sint8 clase
/// @param: Sint32 penacarcel
/// @brief: Informa las estadísticas del usuario.
cPSMiniStats::cPSMiniStats(){
}

cPSMiniStats::~cPSMiniStats(){
}

bool cPSMiniStats::unserialize(cByteQueue* q){
	if(q->len()<20) return false;
	q->RemoveData(1);//ID;
	q->Read(&ciudadanosmatados);
	q->Read(&criminalesmatados);
	q->Read(&usuariosmatados);
	q->Read(&npcsmatados);
	q->Read(&clase);
	q->Read(&penacarcel);
	return true;
}

void cPSMiniStats::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: MiniStats; cuidadanosmatados=" << ciudadanosmatados;
	cout << "; criminalesmatados=" << criminalesmatados << "; usuariosmatados=";
	cout << usuariosmatados << "; npcsmatados=" << npcsmatados;
	cout << "; clase=" << (int) clase << ";penacarcel=" << penacarcel << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: LevelUp
/// @param: Sint16 skills
/// @brief: Informa al cliente que el usuario subió de nivel y gano x skills.

cPSLevelUp::cPSLevelUp(){
}

cPSLevelUp::~cPSLevelUp(){
}

bool cPSLevelUp::unserialize(cByteQueue* q){
	if(q->len()<3) return false;
	q->RemoveData(1);//ID;
	q->Read(&skills);
	return true;
}

void cPSLevelUp::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: LevelUp; skills=" << skills << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: AddForumMsg
/// @param: char* titulo
/// @param: char* mensaje
/// @brief: Agrega un mensaje al foro con titulo  y mensaje.

cPSAddForumMsg::cPSAddForumMsg(){
}

cPSAddForumMsg::~cPSAddForumMsg(){
}

bool cPSAddForumMsg::unserialize(cByteQueue* q){
	int offset=0;
	int tmpoffset=0;
	offset++;//ID
	if((tmpoffset=q->ReadString(titulo,1024-1,offset))<1) return false;
	offset+=tmpoffset;
	if((tmpoffset=q->ReadString(mensaje,4096-1,offset))<1) return false;
	offset+=tmpoffset;
	q->RemoveData(offset);
	return true;
}

void cPSAddForumMsg::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: AddForumMsg; titulo=" << titulo << ";mensaje=";
	cout << mensaje << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowForumForm
/// Sin parametros
/// @brief: Pide al cliente que muestre el foro.

cPSShowForumForm::cPSShowForumForm(){
}

cPSShowForumForm::~cPSShowForumForm(){
}

bool cPSShowForumForm::unserialize(cByteQueue* q){
	q->RemoveData(1);
	return true;
}

void cPSShowForumForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowForumForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SetInvisible
/// @param: Sint16 charindex
/// @param: Sint8 invisible
/// @brief: Informa el estado de visibilidad de un char.

cPSSetInvisible::cPSSetInvisible(){
}

cPSSetInvisible::~cPSSetInvisible(){
}

bool cPSSetInvisible::unserialize(cByteQueue* q){
	if(q->len()<4) return false;
	q->Read(&charindex);
	q->Read(&invisible);
	return true;
}

void cPSSetInvisible::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: SetInvisible; charindex=" << charindex;
	cout << "; invisible=" << (int) invisible << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: DiceRoll
/// @param: Sint8 fuerza
/// @param: Sint8 agilidad
/// @param: Sint8 inteligencia
/// @param: Sint8 carisma
/// @param: Sint8 constitucion
/// @brief: Informa los atributos del usuario.


cPSDiceRoll::cPSDiceRoll(){
}

cPSDiceRoll::~cPSDiceRoll(){
}

bool cPSDiceRoll::unserialize(cByteQueue* q){
	if(q->len()<6) return false;
	q->RemoveData(1);//ID
	q->Read(&fuerza);
	q->Read(&agilidad);
	q->Read(&inteligencia);
	q->Read(&carisma);
	q->Read(&constitucion);
	return true;
}

void cPSDiceRoll::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: DiceRoll; fuerza=" << (int) fuerza << "; agilidad=";
	cout << (int) agilidad << "; inteligencia=" << (int) inteligencia << "; carisma=";
	cout << (int) carisma << "; constitucion=" << (int) constitucion << endl;
        #endif
	ClienteArgentum::instancia()->Dados(fuerza,agilidad,inteligencia,constitucion,carisma);
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: MeditateToggle
/// Sin parámetros
/// @brief: Informa al cliente que comenzó/terminó de meditar

cPSMeditateToggle::cPSMeditateToggle(){
}

cPSMeditateToggle::~cPSMeditateToggle(){
}

bool cPSMeditateToggle::unserialize(cByteQueue* q){
	q->RemoveData(1); //ID
	return true;
}

void cPSMeditateToggle::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: MeditateToggle" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlindNoMore
/// Sin parametros
/// @brief: Informa al cliente que ya no está ciego.

cPSBlindNoMore::cPSBlindNoMore(){
}

cPSBlindNoMore::~cPSBlindNoMore(){
}

bool cPSBlindNoMore::unserialize(cByteQueue* q){
	q->RemoveData(1); //ID
	return true;
}

void cPSBlindNoMore::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BlindNoMore" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: DumbNoMore
/// Sin parametros
/// @brief: Informa al cliente que ya no está tonto.

cPSDumbNoMore::cPSDumbNoMore(){
}

cPSDumbNoMore::~cPSDumbNoMore(){
}

bool cPSDumbNoMore::unserialize(cByteQueue* q){
	q->RemoveData(1); //ID
	return true;
}

void cPSDumbNoMore::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: DumbNoMore" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SendSkills
/// @param: Sint8 skillN N for NUMSKILLS (actually 21)
/// @warning: only unserialized, no skills info saved.
/// @brief: Informa los skills al cliente.

cPSSendSkills::cPSSendSkills(){
}

cPSSendSkills::~cPSSendSkills(){
}

bool cPSSendSkills::unserialize(cByteQueue* q){
	if(q->len()<22) return false;///@warning: hardcoded NUMSKILLS = 21
	q->RemoveData(1);//ID
	for(int i=0;i<21;i++){
		q->Read(&skill);
	}
	return true;
}

void cPSSendSkills::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: SendSkills Warning, no skill info saved." << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: TrainerCreatureList
/// @param:
/// @brief:

cPSTrainerCreatureList::cPSTrainerCreatureList(){
}

cPSTrainerCreatureList::~cPSTrainerCreatureList(){
}

bool cPSTrainerCreatureList::unserialize(cByteQueue* q){
	return true;
}

void cPSTrainerCreatureList::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: TrainerCreatureList" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: guildNews
/// @param:
/// @brief:

cPSguildNews::cPSguildNews(){
}

cPSguildNews::~cPSguildNews(){
}

bool cPSguildNews::unserialize(cByteQueue* q){
	return true;
}

void cPSguildNews::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: guildNews" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: OfferDetails
/// @param:
/// @brief:

cPSOfferDetails::cPSOfferDetails(){
}

cPSOfferDetails::~cPSOfferDetails(){
}

bool cPSOfferDetails::unserialize(cByteQueue* q){
	return true;
}

void cPSOfferDetails::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: OfferDetails" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: AlianceProposalsList
/// @param:
/// @brief:

cPSAlianceProposalsList::cPSAlianceProposalsList(){
}

cPSAlianceProposalsList::~cPSAlianceProposalsList(){
}

bool cPSAlianceProposalsList::unserialize(cByteQueue* q){
	return true;
}

void cPSAlianceProposalsList::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: AlianceProposalsList" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PeaceProposalsList
/// @param:
/// @brief:

cPSPeaceProposalsList::cPSPeaceProposalsList(){
}

cPSPeaceProposalsList::~cPSPeaceProposalsList(){
}

bool cPSPeaceProposalsList::unserialize(cByteQueue* q){
	return true;
}

void cPSPeaceProposalsList::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: PeaceProposalsList" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterInfo
/// @param:
/// @brief:

cPSCharacterInfo::cPSCharacterInfo(){
}

cPSCharacterInfo::~cPSCharacterInfo(){
}

bool cPSCharacterInfo::unserialize(cByteQueue* q){
	return true;
}

void cPSCharacterInfo::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: CharacterInfo" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: GuildLeaderInfo
/// @param:
/// @brief:

cPSGuildLeaderInfo::cPSGuildLeaderInfo(){
}

cPSGuildLeaderInfo::~cPSGuildLeaderInfo(){
}

bool cPSGuildLeaderInfo::unserialize(cByteQueue* q){
	return true;
}

void cPSGuildLeaderInfo::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: GuildLeaderInfo" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: GuildDetails
/// @param:
/// @brief:

cPSGuildDetails::cPSGuildDetails(){
}

cPSGuildDetails::~cPSGuildDetails(){
}

bool cPSGuildDetails::unserialize(cByteQueue* q){
	return true;
}

void cPSGuildDetails::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: GuildDetails" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowGuildFundationForm
/// @param:
/// @brief:

cPSShowGuildFundationForm::cPSShowGuildFundationForm(){
}

cPSShowGuildFundationForm::~cPSShowGuildFundationForm(){
}

bool cPSShowGuildFundationForm::unserialize(cByteQueue* q){
	return true;
}

void cPSShowGuildFundationForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowGuildFundationForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ParalizeOK
/// Sin parametros
/// @brief: Informa el estado de paralisis del usuario.

cPSParalizeOK::cPSParalizeOK(){
}

cPSParalizeOK::~cPSParalizeOK(){
}

bool cPSParalizeOK::unserialize(cByteQueue* q){
	q->RemoveData(1);//id
	return true;
}

void cPSParalizeOK::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ParalizeOK" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowUserRequest
/// @param:
/// @brief:

cPSShowUserRequest::cPSShowUserRequest(){
}

cPSShowUserRequest::~cPSShowUserRequest(){
}

bool cPSShowUserRequest::unserialize(cByteQueue* q){
	return true;
}

void cPSShowUserRequest::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowUserRequest" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: TradeOK
/// @param:
/// @brief:

cPSTradeOK::cPSTradeOK(){
}

cPSTradeOK::~cPSTradeOK(){
}

bool cPSTradeOK::unserialize(cByteQueue* q){
	q->RemoveData(1);//ID
	return true;
}

void cPSTradeOK::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: TradeOK" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BankOK
/// @param:
/// @brief:

cPSBankOK::cPSBankOK(){
}

cPSBankOK::~cPSBankOK(){
}

bool cPSBankOK::unserialize(cByteQueue* q){
	q->RemoveData(1);//ID
	return true;
}

void cPSBankOK::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: BankOK" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeUserTradeSlot
/// @param:
/// @brief:

cPSChangeUserTradeSlot::cPSChangeUserTradeSlot(){
}

cPSChangeUserTradeSlot::~cPSChangeUserTradeSlot(){
}

bool cPSChangeUserTradeSlot::unserialize(cByteQueue* q){
	return true;
}

void cPSChangeUserTradeSlot::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ChangeUserTradeSlot" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SendNight
/// @param: Sint8 noche
/// @brief: Es de noche?

cPSSendNight::cPSSendNight(){
}

cPSSendNight::~cPSSendNight(){
}

bool cPSSendNight::unserialize(cByteQueue* q){
	if(q->len()<2) return false;
	q->RemoveData(1);//id
	q->Read(&noche);
	return true;
}

void cPSSendNight::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: SendNight; noche=" << noche << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SpawnList
/// @param:
/// @brief:

cPSSpawnList::cPSSpawnList(){
}

cPSSpawnList::~cPSSpawnList(){
}

bool cPSSpawnList::unserialize(cByteQueue* q){
	return true;
}

void cPSSpawnList::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: SpawnList" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowSOSForm
/// @param:
/// @brief:

cPSShowSOSForm::cPSShowSOSForm(){
}

cPSShowSOSForm::~cPSShowSOSForm(){
}

bool cPSShowSOSForm::unserialize(cByteQueue* q){
	return true;
}

void cPSShowSOSForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowSOSForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowMOTDEditionForm
/// @param:
/// @brief:

cPSShowMOTDEditionForm::cPSShowMOTDEditionForm(){
}

cPSShowMOTDEditionForm::~cPSShowMOTDEditionForm(){
}

bool cPSShowMOTDEditionForm::unserialize(cByteQueue* q){
	return true;
}

void cPSShowMOTDEditionForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowMOTDEditionForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowGMPanelForm
/// @param:
/// @brief:

cPSShowGMPanelForm::cPSShowGMPanelForm(){
}

cPSShowGMPanelForm::~cPSShowGMPanelForm(){
}

bool cPSShowGMPanelForm::unserialize(cByteQueue* q){
	return true;
}

void cPSShowGMPanelForm::exec(){
        #ifdef DEBUG
        cout << "Paquete.cpp: ShowGMPanelForm" << endl;
        #endif
}
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

