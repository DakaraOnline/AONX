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

#ifndef _comunicador_h
#define _comunicador_h

class cComunicador;

#include "paquete.h"
#include "paquetec.h"
#include "sock.h"
#include "bytequeue.h"
#include "factory.h"



class cComunicador{
	public:
		cComunicador(csocket* asocket,cByteQueue* ain, cByteQueue* aout);
		~cComunicador(){};
		
		void Login(std::string u, std::string p, Sint8 M, Sint8 m, Sint8 r);
		void LoginNew(std::string u, std::string p, std::string e, Sint8 M, Sint8 m, Sint8 r, Sint8* s, Sint8 R, Sint8 Ci, Sint8 G, Sint8 Cl);
		void Walk(Sint8 heading);
		void ChangeHeading(Sint8 heading);
		void LeftClick(Sint8 x, Sint8 y);
		void DoubleClick(Sint8 x, Sint8 y);
		void Attack();
		void CombatModeToggle();
		void PickUp();
		void Equip(Sint8 slot);
		void Use(Sint8 slot);
		void Drop(Sint8 slot, Sint16 amount);
		void EndBank();
		void BankDeposit(Sint8 slot, Sint16 amount);
		void BankExtractItem(Sint8 slot, Sint16 amount);
		void EndCommerce();
		void CommerceBuy(Sint8 slot, Sint16 amount);
		void CommerceSell(Sint8 slot, Sint16 amount);
		void Dados();
		void Talk(std::string what);
		void Online();

		void Recibir();
		void Enviar();

	private:
		///la magia (??)
		PaqueteServidor_ptr (cServerFactory::*paquetes[200])();
		cByteQueue* in;
		cByteQueue* out;
		csocket* socket;
		cServerFactory factory;

		enum PaquetesServidor{
			Logged=0,		// LOGGED
			RemoveDialogs,		// QTDL
			RemoveCharDialog,	// QDL
			NavigateToggle,		// NAVEG
			Disconnect,		// FINOK
			CommerceEnd,		// FINCOMOK
			BankEnd,		// FINBANOK
			CommerceInit,		// INITCOM
			BankInit,		// INITBANCO
			UserCommerceInit,	// INITCOMUSU
			UserCommerceEnd,	// FINCOMUSUOK
			ShowBlacksmithForm,	// SFH
			ShowCarpenterForm,	// SFC
			NPCSwing,		// N1
			NPCKillUser,		// 6
			BlockedWithShieldUser,	// 7
			BlockedWithShieldOther,	// 8
			UserSwing,		// U1
			UpdateNeeded,		// REAU
			SafeModeOn,		// SEGON
			SafeModeOff,		// SEGOFF
			NobilityLost,		// PN
			CantUseWhileMeditating,	// M!
			UpdateSta,		// ASS
			UpdateMana,		// ASM
			UpdateHP,		// ASH
			UpdateGold,		// ASG
			UpdateExp,		// ASE
			ChangeMap,		// CM
			PosUpdate,		// PU
			NPCHitUser,		// N2
			UserHitNPC,		// U2
			UserAttackedSwing,	// U3
			UserHittedByUser,	// N4
			UserHittedUser,		// N5
			ChatOverHead,		// ||
			ConsoleMsg,		// || - Beware!! its the same as above, but it was properly splitted
			GuildChat,		// |+
			ShowMessageBox,		// !!
			UserIndexInServer,	// IU
			UserCharIndexInServer,	// IP
			CharacterCreate,	// CC
			CharacterRemove,	// BP
			CharacterMove,		// MP, +, * and _ //
			CharacterChange,	// CP
			ObjectCreate,		// HO
			ObjectDelete,		// BO
			BlockPosition,		// BQ
			PlayMIDI,		// TM
			PlayWave,		// TW
			guildList,		// GL
			PlayFireSound,		// FO
			AreaChanged,		// CA
			PauseToggle,		// BKW
			RainToggle,		// LLU
			CreateFX,		// CFX
			UpdateUserStats,	// EST
			WorkRequestTarget,	// T01
			ChangeInventorySlot,	// CSI
			ChangeBankSlot,		// SBO
			ChangeSpellSlot,	// SHS
			Atributes,		// ATR
			BlacksmithWeapons,	// LAH
			BlacksmithArmors,	// LAR
			CarpenterObjects,	// OBR
			RestOK,			// DOK
			ErrorMsg,		// ERR
			Blind,			// CEGU
			Dumb,			// DUMB
			ShowSignal,		// MCAR
			ChangeNPCInventorySlot,	// NPCI
			UpdateHungerAndThirst,	// EHYS
			Fame,			// FAMA
			MiniStats,		// MEST
			LevelUp,		// SUNI
			AddForumMsg,		// FMSG
			ShowForumForm,		// MFOR
			SetInvisible,		// NOVER
			DiceRoll,		// DADOS
			MeditateToggle,		// MEDOK
			BlindNoMore,		// NSEGUE
			DumbNoMore,		// NESTUP
			SendSkills,		// SKILLS
			TrainerCreatureList,	// LSTCRI
			guildNews,		// GUILDNE
			OfferDetails,		// PEACEDE&ALLIEDE
			AlianceProposalsList,	// ALLIEPR
			PeaceProposalsList,	// PEACEPR
			CharacterInfo,		// CHRINFO
			GuildLeaderInfo,	// LEADERI
			GuildDetails,		// CLANDET
			ShowGuildFundationForm,	// SHOWFUN
			ParalizeOK,		// PARADOK
			ShowUserRequest,	// PETICIO
			TradeOK,		// TRANSOK
			BankOK,			// BANCOOK
			ChangeUserTradeSlot,	// COMUSUINV
			SendNight,		// NOC

			// GMmessages
			SpawnList,		// SPL
			ShowSOSForm,		// MSOS
			ShowMOTDEditionForm,	// ZMOTD
			ShowGMPanelForm,	// ABPANEL
			UserNameList		// LISTUSU
		};
};

#endif
