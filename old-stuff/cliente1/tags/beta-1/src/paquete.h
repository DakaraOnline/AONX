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

#ifndef paquete_h
#define paquete_h





#include "SDL.h"

#include "bytequeue.h"
#include "linked_ptr.h"

class cPaqueteServidor;
typedef linked_ptr<cPaqueteServidor> PaqueteServidor_ptr;

#include "aomap.h"



class cPaqueteServidor{
	public:
		cPaqueteServidor(){}
		virtual ~cPaqueteServidor(){}
		virtual bool unserialize(cByteQueue* q){return false;}
		virtual void exec() = 0;
};


/*
-----------------------------------------------------------------------
----------------------Paquetes-del-Servidor----------------------------
-----------------------------------------------------------------------
*/

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Logged
/// Sin parametros.
/// @brief: Avisa al cliente que el personaje ya esta logueado en el servidor

class cPSLogged : public cPaqueteServidor{
	public:
		cPSLogged(){};
		~cPSLogged(){};
		bool unserialize(cByteQueue* q);
		void exec();
};

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RemoveDialogs
/// Sin párametros
/// @brief: Elimina todos los diálogos

class cPSRemoveDialogs : public cPaqueteServidor{
        public:
                cPSRemoveDialogs();
                ~cPSRemoveDialogs();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RemoveCharDialog
/// @param: Sint16 charindex
/// @brief: Elimina el diálogo de Charindex.

class cPSRemoveCharDialog : public cPaqueteServidor{
        public:
                cPSRemoveCharDialog();
                ~cPSRemoveCharDialog();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NavigateToggle
/// Sin parámetros.
/// @brief: Cambia el estado del personaje actual entre navegando y "no navegando".

class cPSNavigateToggle : public cPaqueteServidor{
        public:
                cPSNavigateToggle();
                ~cPSNavigateToggle();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Disconnect
/// Sin parámetros
/// @brief: Alerta al cliente de una desconexión inminente.


class cPSDisconnect : public cPaqueteServidor{
        public:
                cPSDisconnect();
                ~cPSDisconnect();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CommerceEnd
/// Sin parámetros.
/// @brief: Informa de la finalización del comercio con el npc.

class cPSCommerceEnd : public cPaqueteServidor{
        public:
                cPSCommerceEnd();
                ~cPSCommerceEnd();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BankEnd
/// Sin parámetros
/// @brief: Informa al cliente de la finalización del diálogo con el banco.

class cPSBankEnd : public cPaqueteServidor{
        public:
                cPSBankEnd();
                ~cPSBankEnd();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CommerceInit
/// Sin parámetros
/// @brief: Informa al cliente del comienzo de un diálogo de comercio con un NPC.

class cPSCommerceInit : public cPaqueteServidor{
        public:
                cPSCommerceInit();
                ~cPSCommerceInit();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BankInit
/// Sin parámetros.
/// @brief: Informa al cliente del comienzo del diálogo del banco.

class cPSBankInit : public cPaqueteServidor{
        public:
                cPSBankInit();
                ~cPSBankInit();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserCommerceInit
/// Sin parámetros.
/// @brief: Informa al cliente el comienzo del diálogo de comercio entre usuarios.

class cPSUserCommerceInit : public cPaqueteServidor{
        public:
                cPSUserCommerceInit();
                ~cPSUserCommerceInit();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserCommerceEnd
/// Sin parámetros
/// @brief: Informa al cliente de la finalización del diálogo de comercio entre usuarios.

class cPSUserCommerceEnd : public cPaqueteServidor{
        public:
                cPSUserCommerceEnd();
                ~cPSUserCommerceEnd();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowBlacksmithForm
/// Sin parámetros
/// @brief: Solicita al cliente que muestre el diálogo de Herrería.

class cPSShowBlacksmithForm : public cPaqueteServidor{
        public:
                cPSShowBlacksmithForm();
                ~cPSShowBlacksmithForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowCarpenterForm
/// Sin parámetros
/// @brief: Solicita al cliente que muestre el diálogo de Carpintería.

class cPSShowCarpenterForm : public cPaqueteServidor{
        public:
                cPSShowCarpenterForm();
                ~cPSShowCarpenterForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NPCSwing
/// Sin parámetros.
/// @brief: Informa al cliente que un NPC falló al intentar pegarle al usuario.

class cPSNPCSwing : public cPaqueteServidor{
        public:
                cPSNPCSwing();
                ~cPSNPCSwing();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NPCKillUser
/// Sin parámetros.
/// @brief: Informa al cliente que un NPC mató al usuario.

class cPSNPCKillUser : public cPaqueteServidor{
        public:
                cPSNPCKillUser();
                ~cPSNPCKillUser();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlockedWithShieldUser
/// Sin parámetros.
/// @brief: Informa al cliente que el usuario rechazó un ataque con el escudo.

class cPSBlockedWithShieldUser : public cPaqueteServidor{
        public:
                cPSBlockedWithShieldUser();
                ~cPSBlockedWithShieldUser();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlockedWithShieldOther
/// Sin parámetros.
/// @brief: Informa al cliente que el ataque efectuado por el usuario fue bloqueado con un escudo

class cPSBlockedWithShieldOther : public cPaqueteServidor{
        public:
                cPSBlockedWithShieldOther();
                ~cPSBlockedWithShieldOther();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserSwing
/// Sin parámetros.
/// @brief: Informa al cliente que el usuario falló al atacar.

class cPSUserSwing : public cPaqueteServidor{
        public:
                cPSUserSwing();
                ~cPSUserSwing();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateNeeded
/// Sin parámetros.
/// @brief: Informa al cliente que requiere ser actualizado.

class cPSUpdateNeeded : public cPaqueteServidor{
        public:
                cPSUpdateNeeded();
                ~cPSUpdateNeeded();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SafeModeOn
/// Sin parámetros.
/// @brief: Informa al cliente que está en modo seguro.

class cPSSafeModeOn : public cPaqueteServidor{
        public:
                cPSSafeModeOn();
                ~cPSSafeModeOn();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SafeModeOff
/// Sin parámetros.
/// @brief: Informa al cliente que ya no está en modo seguro.

class cPSSafeModeOff : public cPaqueteServidor{
        public:
                cPSSafeModeOff();
                ~cPSSafeModeOff();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NobilityLost
/// Sin parámetros
/// @brief: Informa al cliente que el usuario perdió su nobleza.

class cPSNobilityLost : public cPaqueteServidor{
        public:
                cPSNobilityLost();
                ~cPSNobilityLost();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CantUseWhileMeditating
/// Sin parámetros.
/// @brief: Informa al cliente que no se pueden utilizar items mientras se medita.

class cPSCantUseWhileMeditating : public cPaqueteServidor{
        public:
                cPSCantUseWhileMeditating();
                ~cPSCantUseWhileMeditating();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateSta
/// @param: Sint16 stamina
/// @brief: Informa al cliente que la cantidad actual de energía es stamina.

class cPSUpdateSta : public cPaqueteServidor{
        public:
                cPSUpdateSta();
                ~cPSUpdateSta();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 stamina;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateMana
/// @param: Sint16 mana
/// @brief: Informa al cliente que la cantidad actual de maná es mana.

class cPSUpdateMana : public cPaqueteServidor{
        public:
                cPSUpdateMana();
                ~cPSUpdateMana();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 mana;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateHP
/// @param: Sint16 hp
/// @brief: Informa al cliente que la cantidad actual de vida es hp.

class cPSUpdateHP : public cPaqueteServidor{
        public:
                cPSUpdateHP();
                ~cPSUpdateHP();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 hp;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateGold
/// @param: Sint32 gold
/// @brief: Informa al cliente que la cantidad actual de oro es gold.

class cPSUpdateGold : public cPaqueteServidor{
        public:
                cPSUpdateGold();
                ~cPSUpdateGold();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint32 gold;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateExp
/// @param: Sint32 exp
/// @brief: Informa al cliente que la cantidad actual de experiencia es exp.

class cPSUpdateExp : public cPaqueteServidor{
        public:
                cPSUpdateExp();
                ~cPSUpdateExp();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint32 exp;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeMap
/// @param: @Sint16 map
/// @param: @Sint16 version
/// @brief: Informa al cliente el cambio de mapa a map, cuya version es version.

class cPSChangeMap : public cPaqueteServidor{
        public:
                cPSChangeMap();
                ~cPSChangeMap();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 map;
		Sint16 version;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PosUpdate
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Informa al cliente la posición actual del usuario.

class cPSPosUpdate : public cPaqueteServidor{
        public:
                cPSPosUpdate();
                ~cPSPosUpdate();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 x;
		Sint8 y;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: NPCHitUser
/// @param: Sint8 donde
/// @param: Sint16 cuanto
/// @brief: Informa al usuario que un NPC le pegó donde por cuanto.

class cPSNPCHitUser : public cPaqueteServidor{
        public:
                cPSNPCHitUser();
                ~cPSNPCHitUser();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 donde;
		Sint16 cuanto;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserHitNPC
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que el usuario le pegó por cuanto al un NPC.

class cPSUserHitNPC : public cPaqueteServidor{
        public:
                cPSUserHitNPC();
                ~cPSUserHitNPC();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 cuanto;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserAttackedSwing
/// @param: string username
/// @brief: Aparentemente charindex atacó al usuario y falló.
class cPSUserAttackedSwing : public cPaqueteServidor{
        public:
                cPSUserAttackedSwing();
                ~cPSUserAttackedSwing();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char username[1024];

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserHittedByUser
/// @param: Sint16 charindex
/// @param: Sint8 donde
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que charindex le pegó al usuario por cuanto en donde.

class cPSUserHittedByUser : public cPaqueteServidor{
        public:
                cPSUserHittedByUser();
                ~cPSUserHittedByUser();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint8 donde;
		Sint16 cuanto;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserHittedUser
/// @param: Sint16 charindex
/// @param: Sint8 donde
/// @param: Sint16 cuanto
/// @brief: Informa al cliente que el usuario le pegó a charindex en donde por cuanto.

class cPSUserHittedUser : public cPaqueteServidor{
        public:
                cPSUserHittedUser();
                ~cPSUserHittedUser();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint8 donde;
		Sint16 cuanto;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChatOverHead
/// @param: char* text
/// @param: Sint16 charindex
/// @param: Sint8 r
/// @param: Sint8 g
/// @param: Sint8 b
/// @brief: Informa al cliente que cree un diálogo sobre charindex con el texto text y el color rgb.

class cPSChatOverHead : public cPaqueteServidor{
        public:
                cPSChatOverHead();
                ~cPSChatOverHead();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char text[1024];
		Sint16 charindex;
		Sint8 r;
		Sint8 g;
		Sint8 b;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ConsoleMsg
/// @param: char* text
/// @param: Sint8 fontindex
/// @brief: Informa al cliente de un mensaje de consola text con la fuente fontindex.

class cPSConsoleMsg : public cPaqueteServidor{
        public:
                cPSConsoleMsg();
                ~cPSConsoleMsg();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char text[1024];
		Sint8 fontindex;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: GuildChat
/// @param: char* text
/// @brief: Informa al cliente de un diálogo de clan con el contenido text.

class cPSGuildChat : public cPaqueteServidor{
        public:
                cPSGuildChat();
                ~cPSGuildChat();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char text[1024];

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowMessageBox
/// @param: char* text
/// @brief: Envia un mensaje al cliente para ser mostrado al usuario.

class cPSShowMessageBox : public cPaqueteServidor{
        public:
                cPSShowMessageBox();
                ~cPSShowMessageBox();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char text[1024];
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserIndexInServer
/// @param: Sint16 userindex
/// @brief: Informa al cliente que el índice del usuario en el servidor es userindex (no confundir con charindex)

class cPSUserIndexInServer : public cPaqueteServidor{
        public:
                cPSUserIndexInServer();
                ~cPSUserIndexInServer();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 userindex;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UserCharIndexInServer
/// @param: Sint16 charindex
/// @brief: Informa al cliente que el índice del char del usuario es charindex

class cPSUserCharIndexInServer : public cPaqueteServidor{
        public:
                cPSUserCharIndexInServer();
                ~cPSUserCharIndexInServer();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
};
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

class cPSCharacterCreate : public cPaqueteServidor{
        public:
                cPSCharacterCreate();
                ~cPSCharacterCreate();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint16 bodyindex;
		Sint16 headindex;
		Sint8 heading;
		Sint8 x;
		Sint8 y;
		Sint16 weaponindex;
		Sint16 shieldindex;
		Sint16 helmetindex;
		Sint16 fxindex;
		Sint16 fxloops;
		char nombre[256];
		Sint8 criminal;
		Sint8 privs;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterRemove
/// @param: Sint16 charindex
/// @brief: Informa al cliente de la eliminación del char charindex.

class cPSCharacterRemove : public cPaqueteServidor{
        public:
                cPSCharacterRemove();
                ~cPSCharacterRemove();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterMove
/// @param: Sint16 charindex
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Informa al cliente del movimiento de charindex a x,y

class cPSCharacterMove : public cPaqueteServidor{
        public:
                cPSCharacterMove();
                ~cPSCharacterMove();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint8 x;
		Sint8 y;
};
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

class cPSCharacterChange : public cPaqueteServidor{
        public:
                cPSCharacterChange();
                ~cPSCharacterChange();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint16 bodyindex;
		Sint16 headindex;
		Sint8 heading;
		Sint16 weaponindex;
		Sint16 shieldindex;
		Sint16 helmetindex;
		Sint16 fxindex;
		Sint16 fxloops;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ObjectCreate
/// Paquete: ObjectCreate
/// @param: Sint8 x
/// @param: Sint8 y
/// @param: Sint16 grhindex
/// @brief: Informa al cliente de la creación de un objeto grhindex en x,y

class cPSObjectCreate : public cPaqueteServidor{
        public:
                cPSObjectCreate();
                ~cPSObjectCreate();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 x;
		Sint8 y;
		Sint16 grhindex;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ObjectDelete
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Informa al cliente de la remoción del objeto en x,y.

class cPSObjectDelete : public cPaqueteServidor{
        public:
                cPSObjectDelete();
                ~cPSObjectDelete();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 x;
		Sint8 y;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlockPosition
/// @param: Sint8 x;
/// @param: Sint8 y;
/// @param: Sint8 blocked
/// @brief: Informa al cliente si un tile está o no bloqueado en x,y.


class cPSBlockPosition : public cPaqueteServidor{
        public:
                cPSBlockPosition();
                ~cPSBlockPosition();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 x;
		Sint8 y;
		Sint8 blocked;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PlayMIDI
/// @param: Sint8 num
/// @param: Sint16 nose
/// @brief: Indica al cliente que reproduzca el midi num.

class cPSPlayMIDI : public cPaqueteServidor{
        public:
                cPSPlayMIDI();
                ~cPSPlayMIDI();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 num;
		Sint16 nose;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PlayWave
/// @param: Sint8 num
/// @brief: Indica al cliente que reproduzca el wav num.

class cPSPlayWave : public cPaqueteServidor{
        public:
                cPSPlayWave();
                ~cPSPlayWave();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 num;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: guildList
/// @param:
/// @brief:

class cPSguildList : public cPaqueteServidor{
        public:
                cPSguildList();
                ~cPSguildList();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PlayFireSound
/// Sin parámetros
/// @brief: Indica al cliente que reproduzca el sonido del fuego.

class cPSPlayFireSound : public cPaqueteServidor{
        public:
                cPSPlayFireSound();
                ~cPSPlayFireSound();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: AreaChanged
/// @param: Sint8 x
/// @param: Sint8 y
/// @brief: Indica al cliente un cambio de area a x,y

class cPSAreaChanged : public cPaqueteServidor{
        public:
                cPSAreaChanged();
                ~cPSAreaChanged();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 x;
		Sint8 y;

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PauseToggle
/// Sin parámetros
/// @brief: Indica al cliente que cambie el estado de pausa.

class cPSPauseToggle : public cPaqueteServidor{
        public:
                cPSPauseToggle();
                ~cPSPauseToggle();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RainToggle
/// Sin parámetros
/// @brief: Indica al cliente que cambie el estado de lluvia.

class cPSRainToggle : public cPaqueteServidor{
        public:
                cPSRainToggle();
                ~cPSRainToggle();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CreateFX
/// @param: Sint16 charindex
/// @param: Sint16 fxindex
/// @param: Sint16 fxloops
/// @brief: Indica al cliente que cree un fx fxindex en charindex con loops fxloops.

class cPSCreateFX : public cPaqueteServidor{
        public:
                cPSCreateFX();
                ~cPSCreateFX();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint16 fxindex;
		Sint16 fxloops;

};
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

class cPSUpdateUserStats : public cPaqueteServidor{
        public:
                cPSUpdateUserStats();
                ~cPSUpdateUserStats();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 maxhp;
		Sint16 minhp;
		Sint16 maxman;
		Sint16 minman;
		Sint16 maxsta;
		Sint16 minsta;
		Sint32 gold;
		Sint8 lvl;
		Sint32 pasarlvl;
		Sint32 exp;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: WorkRequestTarget
/// @param: Sint8 skill
/// @brief: Avisa al usuario que está trabajando en skill.

class cPSWorkRequestTarget : public cPaqueteServidor{
        public:
                cPSWorkRequestTarget();
                ~cPSWorkRequestTarget();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 skill;
};
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

class cPSChangeInventorySlot : public cPaqueteServidor{
        public:
                cPSChangeInventorySlot();
                ~cPSChangeInventorySlot();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 slot;
		Sint16 objindex;
		char nombre[256];
		Sint16 cantidad;
		Sint8 equipado;
		Sint16 grhindex;
		Sint8 objtype;
		Sint16 maxhit;
		Sint16 minhit;
		Sint16 defensa;
		Sint32 valor;
};
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

class cPSChangeBankSlot : public cPaqueteServidor{
        public:
                cPSChangeBankSlot();
                ~cPSChangeBankSlot();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 slot;
		Sint16 objindex;
		char nombre[256];
		Sint16 cantidad;
		Sint16 grhindex;
		Sint8 objtype;
		Sint16 maxhit;
		Sint16 minhit;
		Sint16 def;
		Sint32 valor;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeSpellSlot
/// @param: Sint8 slot
/// @param: Sint16 hindex (va a userhechizos(slot)?)
/// @param: char* nombre
/// @brief: Informa al cliente el hechizo correspondiente a slot

class cPSChangeSpellSlot : public cPaqueteServidor{
        public:
                cPSChangeSpellSlot();
                ~cPSChangeSpellSlot();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 slot;
		Sint16 hindex;
		char nombre[256];
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Atributes
/// @param: Sint8 fuerza
/// @param: Sint8 agilidad
/// @param: Sint8 inteligencia
/// @param: Sint8 carisma
/// @param: Sint8 constitucion
/// @brief: Informa los atributos del usuario actual al cliente

class cPSAtributes : public cPaqueteServidor{
        public:
                cPSAtributes();
                ~cPSAtributes();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 fuerza;
		Sint8 agilidad;
		Sint8 inteligencia;
		Sint8 carisma;
		Sint8 constitucion;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlacksmithWeapons
/// @param: Sint16 count 
/// @warning Esto es bastante variable, solo lo des serializo, las variables se pisan
/// struct blacksmithweapon{ char* nombre, Sint16 hierro, Sint16 plata, Sint16 oro, Sint16 windex}
/// @param: blacksmithweapon[count];
/// @brief: Envia las armas que se pueden construir en la herrería.

class cPSBlacksmithWeapons : public cPaqueteServidor{
        public:
                cPSBlacksmithWeapons();
                ~cPSBlacksmithWeapons();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 count;
		// Esto debería ser un struct :)
		char nombre[256];
		Sint16 hierro;
		Sint16 plata;
		Sint16 oro;
		Sint16 windex;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlacksmithArmors
/// @param: Sint16 count 
/// @warning Esto es bastante variable, solo lo des serializo, las variables se pisan
/// struct blacksmitharmor{ char* nombre, Sint16 hierro, Sint16 plata, Sint16 oro, Sint16 aindex}
/// @param: blacksmitharmor[count]
/// @brief: Envia las armaduras que se pueden construir en la herrería.


class cPSBlacksmithArmors : public cPaqueteServidor{
        public:
                cPSBlacksmithArmors();
                ~cPSBlacksmithArmors();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 count;
		// Esto debería ser un struct :)
		char nombre[256];
		Sint16 hierro;
		Sint16 plata;
		Sint16 oro;
		Sint16 aindex;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CarpenterObjects
/// @param: Sint16 count 
/// @warning Esto es bastante variable, solo lo des serializo, las variables se pisan
/// struct carpenterobject{ char* nombre, Sint16 madera, Sint16 cindex}
/// @param: carpenterobject[count]
/// @brief: Envia los objetos construibles en la carpintaría.

class cPSCarpenterObjects : public cPaqueteServidor{
        public:
                cPSCarpenterObjects();
                ~cPSCarpenterObjects();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 count;
		char nombre[256];
		Sint16 madera;
		Sint16 cindex;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: RestOK
/// Sin parametros
/// @brief: Informa al cliente que terminó de descansar.

class cPSRestOK : public cPaqueteServidor{
        public:
                cPSRestOK();
                ~cPSRestOK();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ErrorMsg
/// @param: char* mensaje
/// @brief: Informa al cliente de un error

class cPSErrorMsg : public cPaqueteServidor{
        public:
                cPSErrorMsg();
                ~cPSErrorMsg();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char mensaje[1024];
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Blind
/// Sin parametros
/// @brief: Informa al cliente que está ciego.

class cPSBlind : public cPaqueteServidor{
        public:
                cPSBlind();
                ~cPSBlind();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: Dumb
/// Sin parametros
/// @brief: Informa al cliente que está tonto.

class cPSDumb : public cPaqueteServidor{
        public:
                cPSDumb();
                ~cPSDumb();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowSignal
/// @param: char* mensaje
/// @param: Sint16 grhindex (i guess?)
/// @brief: Muestra una señal?

class cPSShowSignal : public cPaqueteServidor{
        public:
                cPSShowSignal();
                ~cPSShowSignal();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char mensaje[1024];
		Sint16 grhindex;
};
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

class cPSChangeNPCInventorySlot : public cPaqueteServidor{
        public:
		cPSChangeNPCInventorySlot();
		~cPSChangeNPCInventorySlot();
		bool unserialize(cByteQueue* q);
		void exec();
		static Uint32 last;//de esto hablaba en remarks
        private:
		char nombre[256];
		Sint8 slot;
		Sint16 cantidad;
		Sint32 valor;
		Sint16 grhindex;
		Sint16 objindex;
		Sint8 objtype;
		Sint16 maxhit;
		Sint16 minhit;
		Sint16 def;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: UpdateHungerAndThirst
/// @param: Sint8 maxagu
/// @param: Sint8 minagu
/// @param: Sint8 maxham
/// @param: Sint8 minham
/// @brief: Informa al cliente el estado de hambre y sed.

class cPSUpdateHungerAndThirst : public cPaqueteServidor{
        public:
                cPSUpdateHungerAndThirst();
                ~cPSUpdateHungerAndThirst();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 maxagu;
		Sint8 minagu;
		Sint8 maxham;
		Sint8 minham;
};
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

class cPSFame : public cPaqueteServidor{
        public:
                cPSFame();
                ~cPSFame();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint32 asesino;
		Sint32 bandido;
		Sint32 burgues;
		Sint32 ladron;
		Sint32 noble;
		Sint32 plebeyo;
		Sint32 promedio;
};
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

class cPSMiniStats : public cPaqueteServidor{
        public:
                cPSMiniStats();
                ~cPSMiniStats();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint32 ciudadanosmatados;
		Sint32 criminalesmatados;
		Sint32 usuariosmatados;
		Sint16 npcsmatados;
		Sint8 clase;
		Sint32 penacarcel;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: LevelUp
/// @param: Sint16 skills
/// @brief: Informa al cliente que el usuario subió de nivel y gano x skills.

class cPSLevelUp : public cPaqueteServidor{
        public:
		cPSLevelUp();
		~cPSLevelUp();
		bool unserialize(cByteQueue* q);
		void exec();
        private:
		Sint16 skills;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: AddForumMsg
/// @param: char* titulo
/// @param: char* mensaje
/// @brief: Agrega un mensaje al foro con titulo  y mensaje.

class cPSAddForumMsg : public cPaqueteServidor{
        public:
                cPSAddForumMsg();
                ~cPSAddForumMsg();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		char titulo[1024];
		char mensaje[4096];//ni idea
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowForumForm
/// Sin parametros
/// @brief: Pide al cliente que muestre el foro.

class cPSShowForumForm : public cPaqueteServidor{
        public:
                cPSShowForumForm();
                ~cPSShowForumForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SetInvisible
/// @param: Sint16 charindex
/// @param: Sint8 invisible
/// @brief: Informa el estado de visibilidad de un char.

class cPSSetInvisible : public cPaqueteServidor{
        public:
                cPSSetInvisible();
                ~cPSSetInvisible();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint16 charindex;
		Sint8 invisible;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: DiceRoll
/// @param: Sint8 fuerza
/// @param: Sint8 agilidad
/// @param: Sint8 inteligencia
/// @param: Sint8 carisma
/// @param: Sint8 constitucion
/// @brief: Informa los atributos del usuario.

class cPSDiceRoll : public cPaqueteServidor{
        public:
                cPSDiceRoll();
                ~cPSDiceRoll();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 fuerza;
		Sint8 agilidad;
		Sint8 inteligencia;
		Sint8 carisma;
		Sint8 constitucion;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: MeditateToggle
/// Sin parámetros
/// @brief: Informa al cliente que comenzó/terminó de meditar

class cPSMeditateToggle : public cPaqueteServidor{
        public:
                cPSMeditateToggle();
                ~cPSMeditateToggle();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BlindNoMore
/// Sin parametros
/// @brief: Informa al cliente que ya no está ciego.

class cPSBlindNoMore : public cPaqueteServidor{
        public:
                cPSBlindNoMore();
                ~cPSBlindNoMore();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: DumbNoMore
/// Sin parametros
/// @brief: Informa al cliente que ya no está tonto.

class cPSDumbNoMore : public cPaqueteServidor{
        public:
                cPSDumbNoMore();
                ~cPSDumbNoMore();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SendSkills
/// @param: Sint8 skillN N for NUMSKILLS (actually 21)
/// @warning: only unserialized, no skills info saved.
/// @brief: Informa los skills al cliente.

class cPSSendSkills : public cPaqueteServidor{
        public:
                cPSSendSkills();
                ~cPSSendSkills();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 skill;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: TrainerCreatureList
/// @param:
/// @brief:

class cPSTrainerCreatureList : public cPaqueteServidor{
        public:
                cPSTrainerCreatureList();
                ~cPSTrainerCreatureList();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: guildNews
/// @param:
/// @brief:

class cPSguildNews : public cPaqueteServidor{
        public:
                cPSguildNews();
                ~cPSguildNews();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: OfferDetails
/// @param:
/// @brief:

class cPSOfferDetails : public cPaqueteServidor{
        public:
                cPSOfferDetails();
                ~cPSOfferDetails();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: AlianceProposalsList
/// @param:
/// @brief:

class cPSAlianceProposalsList : public cPaqueteServidor{
        public:
                cPSAlianceProposalsList();
                ~cPSAlianceProposalsList();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: PeaceProposalsList
/// @param:
/// @brief:

class cPSPeaceProposalsList : public cPaqueteServidor{
        public:
                cPSPeaceProposalsList();
                ~cPSPeaceProposalsList();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: CharacterInfo
/// @param:
/// @brief:

class cPSCharacterInfo : public cPaqueteServidor{
        public:
                cPSCharacterInfo();
                ~cPSCharacterInfo();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: GuildLeaderInfo
/// @param:
/// @brief:

class cPSGuildLeaderInfo : public cPaqueteServidor{
        public:
                cPSGuildLeaderInfo();
                ~cPSGuildLeaderInfo();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: GuildDetails
/// @param:
/// @brief:

class cPSGuildDetails : public cPaqueteServidor{
        public:
                cPSGuildDetails();
                ~cPSGuildDetails();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowGuildFundationForm
/// @param:
/// @brief:

class cPSShowGuildFundationForm : public cPaqueteServidor{
        public:
                cPSShowGuildFundationForm();
                ~cPSShowGuildFundationForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ParalizeOK
/// Sin parametros
/// @brief: Informa el estado de paralisis del usuario.

class cPSParalizeOK : public cPaqueteServidor{
        public:
                cPSParalizeOK();
                ~cPSParalizeOK();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowUserRequest
/// @param:
/// @brief:

class cPSShowUserRequest : public cPaqueteServidor{
        public:
                cPSShowUserRequest();
                ~cPSShowUserRequest();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: TradeOK
/// @param:
/// @brief:

class cPSTradeOK : public cPaqueteServidor{
        public:
                cPSTradeOK();
                ~cPSTradeOK();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: BankOK
/// @param:
/// @brief:

class cPSBankOK : public cPaqueteServidor{
        public:
                cPSBankOK();
                ~cPSBankOK();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ChangeUserTradeSlot
/// @param:
/// @brief:

class cPSChangeUserTradeSlot : public cPaqueteServidor{
        public:
                cPSChangeUserTradeSlot();
                ~cPSChangeUserTradeSlot();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SendNight
/// @param: Sint8 noche
/// @brief: Es de noche?

class cPSSendNight : public cPaqueteServidor{
        public:
                cPSSendNight();
                ~cPSSendNight();
                bool unserialize(cByteQueue* q);
                void exec();
        private:
		Sint8 noche;
};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: SpawnList
/// @param:
/// @brief:

class cPSSpawnList : public cPaqueteServidor{
        public:
                cPSSpawnList();
                ~cPSSpawnList();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowSOSForm
/// @param:
/// @brief:

class cPSShowSOSForm : public cPaqueteServidor{
        public:
                cPSShowSOSForm();
                ~cPSShowSOSForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowMOTDEditionForm
/// @param:
/// @brief:

class cPSShowMOTDEditionForm : public cPaqueteServidor{
        public:
                cPSShowMOTDEditionForm();
                ~cPSShowMOTDEditionForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
/// Paquete: ShowGMPanelForm
/// @param:
/// @brief:

class cPSShowGMPanelForm : public cPaqueteServidor{
        public:
                cPSShowGMPanelForm();
                ~cPSShowGMPanelForm();
                bool unserialize(cByteQueue* q);
                void exec();
        private:

};
/// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#endif
