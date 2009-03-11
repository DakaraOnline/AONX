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

#ifndef factory_h
#define factory_h

#include "paquete.h"
#include "paquetec.h"

class cServerFactory{
	public:
		cServerFactory(){};
		~cServerFactory(){};
		PaqueteServidor_ptr Logged(){
			return PaqueteServidor_ptr(new cPSLogged());
		}

		PaqueteServidor_ptr RemoveDialogs(){
			return PaqueteServidor_ptr(new cPSRemoveDialogs());
		}
		
		PaqueteServidor_ptr RemoveCharDialog(){
			return PaqueteServidor_ptr(new cPSRemoveCharDialog());
		}
		
		PaqueteServidor_ptr NavigateToggle(){
			return PaqueteServidor_ptr(new cPSNavigateToggle());
		}
		
		PaqueteServidor_ptr Disconnect(){
			return PaqueteServidor_ptr(new cPSDisconnect());
		}
		
		PaqueteServidor_ptr CommerceEnd(){
			return PaqueteServidor_ptr(new cPSCommerceEnd());
		}
		
		PaqueteServidor_ptr BankEnd(){
			return PaqueteServidor_ptr(new cPSBankEnd());
		}
		
		PaqueteServidor_ptr CommerceInit(){
			return PaqueteServidor_ptr(new cPSCommerceInit());
		}
		
		PaqueteServidor_ptr BankInit(){
			return PaqueteServidor_ptr(new cPSBankInit());
		}
		
		PaqueteServidor_ptr UserCommerceInit(){
			return PaqueteServidor_ptr(new cPSUserCommerceInit());
		}
		
		PaqueteServidor_ptr UserCommerceEnd(){
			return PaqueteServidor_ptr(new cPSUserCommerceEnd());
		}
		
		PaqueteServidor_ptr ShowBlacksmithForm(){
			return PaqueteServidor_ptr(new cPSShowBlacksmithForm());
		}
		
		PaqueteServidor_ptr ShowCarpenterForm(){
			return PaqueteServidor_ptr(new cPSShowCarpenterForm());
		}
		
		PaqueteServidor_ptr NPCSwing(){
			return PaqueteServidor_ptr(new cPSNPCSwing());
		}
		
		PaqueteServidor_ptr NPCKillUser(){
			return PaqueteServidor_ptr(new cPSNPCKillUser());
		}
		
		PaqueteServidor_ptr BlockedWithShieldUser(){
			return PaqueteServidor_ptr(new cPSBlockedWithShieldUser());
		}
		
		PaqueteServidor_ptr BlockedWithShieldOther(){
			return PaqueteServidor_ptr(new cPSBlockedWithShieldOther());
		}
		
		PaqueteServidor_ptr UserSwing(){
			return PaqueteServidor_ptr(new cPSUserSwing());
		}
		
		PaqueteServidor_ptr UpdateNeeded(){
			return PaqueteServidor_ptr(new cPSUpdateNeeded());
		}
		
		PaqueteServidor_ptr SafeModeOn(){
			return PaqueteServidor_ptr(new cPSSafeModeOn());
		}
		
		PaqueteServidor_ptr SafeModeOff(){
			return PaqueteServidor_ptr(new cPSSafeModeOff());
		}
		
		PaqueteServidor_ptr NobilityLost(){
			return PaqueteServidor_ptr(new cPSNobilityLost());
		}
		
		PaqueteServidor_ptr CantUseWhileMeditating(){
			return PaqueteServidor_ptr(new cPSCantUseWhileMeditating());
		}
		
		PaqueteServidor_ptr UpdateSta(){
			return PaqueteServidor_ptr(new cPSUpdateSta());
		}
		
		PaqueteServidor_ptr UpdateMana(){
			return PaqueteServidor_ptr(new cPSUpdateMana());
		}
		
		PaqueteServidor_ptr UpdateHP(){
			return PaqueteServidor_ptr(new cPSUpdateHP());
		}
		
		PaqueteServidor_ptr UpdateGold(){
			return PaqueteServidor_ptr(new cPSUpdateGold());
		}
		
		PaqueteServidor_ptr UpdateExp(){
			return PaqueteServidor_ptr(new cPSUpdateExp());
		}
		
		PaqueteServidor_ptr ChangeMap(){
			return PaqueteServidor_ptr(new cPSChangeMap());
		}
		
		PaqueteServidor_ptr PosUpdate(){
			return PaqueteServidor_ptr(new cPSPosUpdate());
		}
		
		PaqueteServidor_ptr NPCHitUser(){
			return PaqueteServidor_ptr(new cPSNPCHitUser());
		}
		
		PaqueteServidor_ptr UserHitNPC(){
			return PaqueteServidor_ptr(new cPSUserHitNPC());
		}
		
		PaqueteServidor_ptr UserAttackedSwing(){
			return PaqueteServidor_ptr(new cPSUserAttackedSwing());
		}
		
		PaqueteServidor_ptr UserHittedByUser(){
			return PaqueteServidor_ptr(new cPSUserHittedByUser());
		}
		
		PaqueteServidor_ptr UserHittedUser(){
			return PaqueteServidor_ptr(new cPSUserHittedUser());
		}
		
		PaqueteServidor_ptr ChatOverHead(){
			return PaqueteServidor_ptr(new cPSChatOverHead());
		}
		
		PaqueteServidor_ptr ConsoleMsg(){
			return PaqueteServidor_ptr(new cPSConsoleMsg());
		}
		
		PaqueteServidor_ptr GuildChat(){
			return PaqueteServidor_ptr(new cPSGuildChat());
		}
		
		PaqueteServidor_ptr ShowMessageBox(){
			return PaqueteServidor_ptr(new cPSShowMessageBox());
		}
		
		PaqueteServidor_ptr UserIndexInServer(){
			return PaqueteServidor_ptr(new cPSUserIndexInServer());
		}
		
		PaqueteServidor_ptr UserCharIndexInServer(){
			return PaqueteServidor_ptr(new cPSUserCharIndexInServer());
		}
		
		PaqueteServidor_ptr CharacterCreate(){
			return PaqueteServidor_ptr(new cPSCharacterCreate());
		}
		
		PaqueteServidor_ptr CharacterRemove(){
			return PaqueteServidor_ptr(new cPSCharacterRemove());
		}
		
		PaqueteServidor_ptr CharacterMove(){
			return PaqueteServidor_ptr(new cPSCharacterMove());
		}
		
		PaqueteServidor_ptr CharacterChange(){
			return PaqueteServidor_ptr(new cPSCharacterChange());
		}
		
		PaqueteServidor_ptr ObjectCreate(){
			return PaqueteServidor_ptr(new cPSObjectCreate());
		}
		
		PaqueteServidor_ptr ObjectDelete(){
			return PaqueteServidor_ptr(new cPSObjectDelete());
		}
		
		PaqueteServidor_ptr BlockPosition(){
			return PaqueteServidor_ptr(new cPSBlockPosition());
		}
		
		PaqueteServidor_ptr PlayMIDI(){
			return PaqueteServidor_ptr(new cPSPlayMIDI());
		}
		
		PaqueteServidor_ptr PlayWave(){
			return PaqueteServidor_ptr(new cPSPlayWave());
		}
		
		PaqueteServidor_ptr guildList(){
			return PaqueteServidor_ptr(new cPSguildList());
		}
		
		PaqueteServidor_ptr PlayFireSound(){
			return PaqueteServidor_ptr(new cPSPlayFireSound());
		}
		
		PaqueteServidor_ptr AreaChanged(){
			return PaqueteServidor_ptr(new cPSAreaChanged());
		}
		
		PaqueteServidor_ptr PauseToggle(){
			return PaqueteServidor_ptr(new cPSPauseToggle());
		}
		
		PaqueteServidor_ptr RainToggle(){
			return PaqueteServidor_ptr(new cPSRainToggle());
		}
		
		PaqueteServidor_ptr CreateFX(){
			return PaqueteServidor_ptr(new cPSCreateFX());
		}
		
		PaqueteServidor_ptr UpdateUserStats(){
			return PaqueteServidor_ptr(new cPSUpdateUserStats());
		}
		
		PaqueteServidor_ptr WorkRequestTarget(){
			return PaqueteServidor_ptr(new cPSWorkRequestTarget());
		}
		
		PaqueteServidor_ptr ChangeInventorySlot(){
			return PaqueteServidor_ptr(new cPSChangeInventorySlot());
		}
		
		PaqueteServidor_ptr ChangeBankSlot(){
			return PaqueteServidor_ptr(new cPSChangeBankSlot());
		}
		
		PaqueteServidor_ptr ChangeSpellSlot(){
			return PaqueteServidor_ptr(new cPSChangeSpellSlot());
		}
		
		PaqueteServidor_ptr Atributes(){
			return PaqueteServidor_ptr(new cPSAtributes());
		}
		
		PaqueteServidor_ptr BlacksmithWeapons(){
			return PaqueteServidor_ptr(new cPSBlacksmithWeapons());
		}
		
		PaqueteServidor_ptr BlacksmithArmors(){
			return PaqueteServidor_ptr(new cPSBlacksmithArmors());
		}
		
		PaqueteServidor_ptr CarpenterObjects(){
			return PaqueteServidor_ptr(new cPSCarpenterObjects());
		}
		
		PaqueteServidor_ptr RestOK(){
			return PaqueteServidor_ptr(new cPSRestOK());
		}
		
		PaqueteServidor_ptr ErrorMsg(){
			return PaqueteServidor_ptr(new cPSErrorMsg());
		}
		
		PaqueteServidor_ptr Blind(){
			return PaqueteServidor_ptr(new cPSBlind());
		}
		
		PaqueteServidor_ptr Dumb(){
			return PaqueteServidor_ptr(new cPSDumb());
		}
		
		PaqueteServidor_ptr ShowSignal(){
			return PaqueteServidor_ptr(new cPSShowSignal());
		}
		
		PaqueteServidor_ptr ChangeNPCInventorySlot(){
			return PaqueteServidor_ptr(new cPSChangeNPCInventorySlot());
		}
		
		PaqueteServidor_ptr UpdateHungerAndThirst(){
			return PaqueteServidor_ptr(new cPSUpdateHungerAndThirst());
		}
		
		PaqueteServidor_ptr Fame(){
			return PaqueteServidor_ptr(new cPSFame());
		}
		
		PaqueteServidor_ptr MiniStats(){
			return PaqueteServidor_ptr(new cPSMiniStats());
		}
		
		PaqueteServidor_ptr LevelUp(){
			return PaqueteServidor_ptr(new cPSLevelUp());
		}
		
		PaqueteServidor_ptr AddForumMsg(){
			return PaqueteServidor_ptr(new cPSAddForumMsg());
		}
		
		PaqueteServidor_ptr ShowForumForm(){
			return PaqueteServidor_ptr(new cPSShowForumForm());
		}
		
		PaqueteServidor_ptr SetInvisible(){
			return PaqueteServidor_ptr(new cPSSetInvisible());
		}
		
		PaqueteServidor_ptr DiceRoll(){
			return PaqueteServidor_ptr(new cPSDiceRoll());
		}
		
		PaqueteServidor_ptr MeditateToggle(){
			return PaqueteServidor_ptr(new cPSMeditateToggle());
		}
		
		PaqueteServidor_ptr BlindNoMore(){
			return PaqueteServidor_ptr(new cPSBlindNoMore());
		}
		
		PaqueteServidor_ptr DumbNoMore(){
			return PaqueteServidor_ptr(new cPSDumbNoMore());
		}
		
		PaqueteServidor_ptr SendSkills(){
			return PaqueteServidor_ptr(new cPSSendSkills());
		}
		
		PaqueteServidor_ptr TrainerCreatureList(){
			return PaqueteServidor_ptr(new cPSTrainerCreatureList());
		}
		
		PaqueteServidor_ptr guildNews(){
			return PaqueteServidor_ptr(new cPSguildNews());
		}
		
		PaqueteServidor_ptr OfferDetails(){
			return PaqueteServidor_ptr(new cPSOfferDetails());
		}
		
		PaqueteServidor_ptr AlianceProposalsList(){
			return PaqueteServidor_ptr(new cPSAlianceProposalsList());
		}
		
		PaqueteServidor_ptr PeaceProposalsList(){
			return PaqueteServidor_ptr(new cPSPeaceProposalsList());
		}
		
		PaqueteServidor_ptr CharacterInfo(){
			return PaqueteServidor_ptr(new cPSCharacterInfo());
		}
		
		PaqueteServidor_ptr GuildLeaderInfo(){
			return PaqueteServidor_ptr(new cPSGuildLeaderInfo());
		}
		
		PaqueteServidor_ptr GuildDetails(){
			return PaqueteServidor_ptr(new cPSGuildDetails());
		}
		
		PaqueteServidor_ptr ShowGuildFundationForm(){
			return PaqueteServidor_ptr(new cPSShowGuildFundationForm());
		}
		
		PaqueteServidor_ptr ParalizeOK(){
			return PaqueteServidor_ptr(new cPSParalizeOK());
		}
		
		PaqueteServidor_ptr ShowUserRequest(){
			return PaqueteServidor_ptr(new cPSShowUserRequest());
		}
		
		PaqueteServidor_ptr TradeOK(){
			return PaqueteServidor_ptr(new cPSTradeOK());
		}
		
		PaqueteServidor_ptr BankOK(){
			return PaqueteServidor_ptr(new cPSBankOK());
		}
		
		PaqueteServidor_ptr ChangeUserTradeSlot(){
			return PaqueteServidor_ptr(new cPSChangeUserTradeSlot());
		}
		
		PaqueteServidor_ptr SendNight(){
			return PaqueteServidor_ptr(new cPSSendNight());
		}
		
		PaqueteServidor_ptr SpawnList(){
			return PaqueteServidor_ptr(new cPSSpawnList());
		}
		
		PaqueteServidor_ptr ShowSOSForm(){
			return PaqueteServidor_ptr(new cPSShowSOSForm());
		}
		
		PaqueteServidor_ptr ShowMOTDEditionForm(){
			return PaqueteServidor_ptr(new cPSShowMOTDEditionForm());
		}
		
		PaqueteServidor_ptr ShowGMPanelForm(){
			return PaqueteServidor_ptr(new cPSShowGMPanelForm());
		}
};

#endif
