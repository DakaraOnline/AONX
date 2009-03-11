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

#include "comunicador.h"
#include <iostream>
#include <string>
//#define DEBUG
using namespace std;
cComunicador::cComunicador(csocket* asocket,cByteQueue* ain, cByteQueue* aout) : in(ain),out(aout),socket(asocket){

	paquetes[Logged]=&cServerFactory::Logged;
	paquetes[RemoveDialogs]=&cServerFactory::RemoveDialogs;
	paquetes[RemoveCharDialog]=&cServerFactory::RemoveCharDialog;
	paquetes[NavigateToggle]=&cServerFactory::NavigateToggle;
	paquetes[Disconnect]=&cServerFactory::Disconnect;
	paquetes[CommerceEnd]=&cServerFactory::CommerceEnd;
	paquetes[BankEnd]=&cServerFactory::BankEnd;
	paquetes[CommerceInit]=&cServerFactory::CommerceInit;
	paquetes[BankInit]=&cServerFactory::BankInit;
	paquetes[UserCommerceInit]=&cServerFactory::UserCommerceInit;
	paquetes[UserCommerceEnd]=&cServerFactory::UserCommerceEnd;
	paquetes[ShowBlacksmithForm]=&cServerFactory::ShowBlacksmithForm;
	paquetes[ShowCarpenterForm]=&cServerFactory::ShowCarpenterForm;
	paquetes[NPCSwing]=&cServerFactory::NPCSwing;
	paquetes[NPCKillUser]=&cServerFactory::NPCKillUser;
	paquetes[BlockedWithShieldUser]=&cServerFactory::BlockedWithShieldUser;
	paquetes[BlockedWithShieldOther]=&cServerFactory::BlockedWithShieldOther;
	paquetes[UserSwing]=&cServerFactory::UserSwing;
	paquetes[UpdateNeeded]=&cServerFactory::UpdateNeeded;
	paquetes[SafeModeOn]=&cServerFactory::SafeModeOn;
	paquetes[SafeModeOff]=&cServerFactory::SafeModeOff;
	paquetes[NobilityLost]=&cServerFactory::NobilityLost;
	paquetes[CantUseWhileMeditating]=&cServerFactory::CantUseWhileMeditating;
	paquetes[UpdateSta]=&cServerFactory::UpdateSta;
	paquetes[UpdateMana]=&cServerFactory::UpdateMana;
	paquetes[UpdateHP]=&cServerFactory::UpdateHP;
	paquetes[UpdateGold]=&cServerFactory::UpdateGold;
	paquetes[UpdateExp]=&cServerFactory::UpdateExp;
	paquetes[ChangeMap]=&cServerFactory::ChangeMap;
	paquetes[PosUpdate]=&cServerFactory::PosUpdate;
	paquetes[NPCHitUser]=&cServerFactory::NPCHitUser;
	paquetes[UserHitNPC]=&cServerFactory::UserHitNPC;
	paquetes[UserAttackedSwing]=&cServerFactory::UserAttackedSwing;
	paquetes[UserHittedByUser]=&cServerFactory::UserHittedByUser;
	paquetes[UserHittedUser]=&cServerFactory::UserHittedUser;
	paquetes[ChatOverHead]=&cServerFactory::ChatOverHead;
	paquetes[ConsoleMsg]=&cServerFactory::ConsoleMsg;
	paquetes[GuildChat]=&cServerFactory::GuildChat;
	paquetes[ShowMessageBox]=&cServerFactory::ShowMessageBox;
	paquetes[UserIndexInServer]=&cServerFactory::UserIndexInServer;
	paquetes[UserCharIndexInServer]=&cServerFactory::UserCharIndexInServer;
	paquetes[CharacterCreate]=&cServerFactory::CharacterCreate;
	paquetes[CharacterRemove]=&cServerFactory::CharacterRemove;
	paquetes[CharacterMove]=&cServerFactory::CharacterMove;
	paquetes[CharacterChange]=&cServerFactory::CharacterChange;
	paquetes[ObjectCreate]=&cServerFactory::ObjectCreate;
	paquetes[ObjectDelete]=&cServerFactory::ObjectDelete;
	paquetes[BlockPosition]=&cServerFactory::BlockPosition;
	paquetes[PlayMIDI]=&cServerFactory::PlayMIDI;
	paquetes[PlayWave]=&cServerFactory::PlayWave;
	paquetes[guildList]=&cServerFactory::guildList;
	paquetes[PlayFireSound]=&cServerFactory::PlayFireSound;
	paquetes[AreaChanged]=&cServerFactory::AreaChanged;
	paquetes[PauseToggle]=&cServerFactory::PauseToggle;
	paquetes[RainToggle]=&cServerFactory::RainToggle;
	paquetes[CreateFX]=&cServerFactory::CreateFX;
	paquetes[UpdateUserStats]=&cServerFactory::UpdateUserStats;
	paquetes[WorkRequestTarget]=&cServerFactory::WorkRequestTarget;
	paquetes[ChangeInventorySlot]=&cServerFactory::ChangeInventorySlot;
	paquetes[ChangeBankSlot]=&cServerFactory::ChangeBankSlot;
	paquetes[ChangeSpellSlot]=&cServerFactory::ChangeSpellSlot;
	paquetes[Atributes]=&cServerFactory::Atributes;
	paquetes[BlacksmithWeapons]=&cServerFactory::BlacksmithWeapons;
	paquetes[BlacksmithArmors]=&cServerFactory::BlacksmithArmors;
	paquetes[CarpenterObjects]=&cServerFactory::CarpenterObjects;
	paquetes[RestOK]=&cServerFactory::RestOK;
	paquetes[ErrorMsg]=&cServerFactory::ErrorMsg;
	paquetes[Blind]=&cServerFactory::Blind;
	paquetes[Dumb]=&cServerFactory::Dumb;
	paquetes[ShowSignal]=&cServerFactory::ShowSignal;
	paquetes[ChangeNPCInventorySlot]=&cServerFactory::ChangeNPCInventorySlot;
	paquetes[UpdateHungerAndThirst]=&cServerFactory::UpdateHungerAndThirst;
	paquetes[Fame]=&cServerFactory::Fame;
	paquetes[MiniStats]=&cServerFactory::MiniStats;
	paquetes[LevelUp]=&cServerFactory::LevelUp;
	paquetes[AddForumMsg]=&cServerFactory::AddForumMsg;
	paquetes[ShowForumForm]=&cServerFactory::ShowForumForm;
	paquetes[SetInvisible]=&cServerFactory::SetInvisible;
	paquetes[DiceRoll]=&cServerFactory::DiceRoll;
	paquetes[MeditateToggle]=&cServerFactory::MeditateToggle;
	paquetes[BlindNoMore]=&cServerFactory::BlindNoMore;
	paquetes[DumbNoMore]=&cServerFactory::DumbNoMore;
	paquetes[SendSkills]=&cServerFactory::SendSkills;
	paquetes[TrainerCreatureList]=&cServerFactory::TrainerCreatureList;
	paquetes[guildNews]=&cServerFactory::guildNews;
	paquetes[OfferDetails]=&cServerFactory::OfferDetails;
	paquetes[AlianceProposalsList]=&cServerFactory::AlianceProposalsList;
	paquetes[PeaceProposalsList]=&cServerFactory::PeaceProposalsList;
	paquetes[CharacterInfo]=&cServerFactory::CharacterInfo;
	paquetes[GuildLeaderInfo]=&cServerFactory::GuildLeaderInfo;
	paquetes[GuildDetails]=&cServerFactory::GuildDetails;
	paquetes[ShowGuildFundationForm]=&cServerFactory::ShowGuildFundationForm;
	paquetes[ParalizeOK]=&cServerFactory::ParalizeOK;
	paquetes[ShowUserRequest]=&cServerFactory::ShowUserRequest;
	paquetes[TradeOK]=&cServerFactory::TradeOK;
	paquetes[BankOK]=&cServerFactory::BankOK;
	paquetes[ChangeUserTradeSlot]=&cServerFactory::ChangeUserTradeSlot;
	paquetes[SendNight]=&cServerFactory::SendNight;
	paquetes[SpawnList]=&cServerFactory::SpawnList;
	paquetes[ShowSOSForm]=&cServerFactory::ShowSOSForm;
	paquetes[ShowMOTDEditionForm]=&cServerFactory::ShowMOTDEditionForm;
	paquetes[ShowGMPanelForm]=&cServerFactory::ShowGMPanelForm;
	paquetes[SpellNotSpelled]=&cServerFactory::SpellNotSpelled;
	paquetes[GeneralInfo]=&cServerFactory::GeneralInfo;
	paquetes[Pong]=&cServerFactory::Pong;
	paquetes[ConsoleMessageN] = &cServerFactory::ConsoleMessageN;
	paquetes[ConsoleMessageWithParams] = &cServerFactory::ConsoleMessageWithParams;
	//cout << "voy por: " << SendSkills << " y son: " << ShowGMPanelForm << endl;
}

void cComunicador::Recibir(){
	
	char tmp[8192];
	int len = socket->recibir(tmp, 8192);
	#ifdef DEBUG
	cout << "len: " << len << endl;
	#endif
	in->WriteData(tmp, len);

	if(in->len()){
		Sint8 id;
		while(in->Peek(&id)>0){
			#ifdef DEBUG
			cout << "ID:" <<(int) id << endl;
			#endif
			PaqueteServidor_ptr elpaquete = (factory.*paquetes[id])();
			if(!elpaquete->unserialize(in)) {
				#ifdef DEBUG
				cout << "Buffer insuficiente, paquete: " << (int) id << " esperando datos..." << endl;
				#endif
				break;
			}
			//TODO: eso tiene q tirar una exception o algo mejorcito jiji
			elpaquete->exec();
		}
	}
}

void cComunicador::Enviar(){
	if(out->len())
	{
		this->socket->enviar((const char*)out->raw(), out->len());
		out->clear();
	}
}

void cComunicador::Login(std::string u, std::string p, Sint8 M, Sint8 m, Sint8 r) {
	PaqueteCliente_ptr paquete(new cPCLoginExistingChar(u,p,M,m,r));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::LoginNew(std::string u, std::string p, std::string e, Sint8 M, Sint8 m, Sint8 r, Sint8* s, Sint8 R, Sint8 Ci, Sint8 G, Sint8 Cl){
	PaqueteCliente_ptr paquete(new cPCLoginNewChar(u,p,e,M,m,r,s,R,Ci,G,Cl));
paquete->serialize(out);
	Enviar();
}

void cComunicador::Walk(Sint8 heading){
	PaqueteCliente_ptr paquete(new cPCWalk(heading));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::ChangeHeading(Sint8 heading){
	PaqueteCliente_ptr paquete(new cPCChangeHeading(heading));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::LeftClick(Sint8 x, Sint8 y){
	PaqueteCliente_ptr paquete(new cPCLeftClick(x,y));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::DoubleClick(Sint8 x, Sint8 y){
	PaqueteCliente_ptr paquete(new cPCDoubleClick(x,y));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Attack(){
	PaqueteCliente_ptr paquete(new cPCAttack);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::CombatModeToggle(){
	PaqueteCliente_ptr paquete(new cPCCombatModeToggle);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::PickUp(){
	PaqueteCliente_ptr paquete(new cPCPickUp);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Equip(Sint8 slot){
	PaqueteCliente_ptr paquete(new cPCEquipItem(slot));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Use(Sint8 slot){
	PaqueteCliente_ptr paquete(new cPCUseItem(slot));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Drop(Sint8 slot, Sint16 amount){
	PaqueteCliente_ptr paquete(new cPCDrop(slot,amount));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::EndBank(){
	PaqueteCliente_ptr paquete(new cPCBankEnd);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::BankDeposit(Sint8 slot, Uint16 amount){
	PaqueteCliente_ptr paquete(new cPCBankDeposit(slot,amount));
	paquete->serialize(out);
	Enviar();
}


void cComunicador::BankExtractItem(Sint8 slot, Uint16 amount){
	PaqueteCliente_ptr paquete(new cPCBankExtractItem(slot,amount));
	paquete->serialize(out);
	Enviar();
}


void cComunicador::EndCommerce(){
	PaqueteCliente_ptr paquete(new cPCCommerceEnd);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::CommerceSell(Sint8 slot, Uint16 amount){
	PaqueteCliente_ptr paquete(new cPCCommerceSell(slot,amount));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::CommerceBuy(Sint8 slot, Uint16 amount){
	PaqueteCliente_ptr paquete(new cPCCommerceBuy(slot,amount));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Dados(){
	PaqueteCliente_ptr paquete(new cPCThrowDices);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Talk(std::string what)
{
	PaqueteCliente_ptr paquete(new cPCTalk(what));
	paquete->serialize(out);
	Enviar();
}


void cComunicador::Online(){
	PaqueteCliente_ptr paquete(new cPCOnline);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Magia(Sint8 slot, Sint8 x, Sint8 y)
{
	PaqueteCliente_ptr paquete(new cPCCastSpell(slot,x,y));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Meditar(){
	PaqueteCliente_ptr paquete(new cPCMeditate);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::GetClasesInfo()
{
	PaqueteCliente_ptr paquete(new cPCGetClasesInfo);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::GetRazasInfo()
{
	PaqueteCliente_ptr paquete(new cPCGetRazasInfo);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::GetCiudadesInfo()
{
	PaqueteCliente_ptr paquete(new cPCGetCiudadesInfo);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::GoToChar(std::string who)
{
	PaqueteCliente_ptr paquete(new cPCGoToChar(who));
	paquete->serialize(out);
	Enviar();
}


void cComunicador::RequestSkills()
{
	PaqueteCliente_ptr paquete(new cPCRequestSkills);
	paquete->serialize(out);
	Enviar();
}

void cComunicador::ModifySkills(std::vector<Sint8> *skills)
{
	PaqueteCliente_ptr paquete(new cPCModifySkills(skills));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::WarpChar(std::string who, Uint16 map, Uint8 x, Uint8 y)
{
	PaqueteCliente_ptr paquete(new cPCWarpChar(who,map,x,y));
	paquete->serialize(out);
	Enviar();
}

void cComunicador::Ping()
{
	PaqueteCliente_ptr paquete(new cPCPing);
	paquete->serialize(out);
	Enviar();
}
