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

#ifndef paquetec_h
#define paquetec_h
#include "SDL.h"

#include "bytequeue.h"
#include "linked_ptr.h"

#include <string>
#include <vector>

class cPaqueteCliente;
typedef linked_ptr<cPaqueteCliente> PaqueteCliente_ptr;

#ifdef WIN32
#pragma warning (disable : 4305 )
#pragma warning (disable : 4309 )
#endif

enum	PaqueteCliente{
	LoginExistingChar=0,	// *OLOGIN
	ThrowDices,		// *TIRDAD
	LoginNewChar,		// *NLOGIN
	Talk,			// *
	Yell,			// *
	Whisper,		// *
	Walk,			// *M
	RequestPositionUpdate,	// *RPU
	Attack,			// *AT
	PickUp,			// *AG
	CombatModeToggle,	//
	SafeToggle,		//
	RequestGuildLeaderInfo,	//*GLINFO
	RequestAtributes,	//*ATR
	RequestFame,		//*FAMA
	RequestSkills,		//*ESKI
	RequestMiniStats,	//*FEST
	CommerceEnd,		//*FINCOM
	UserCommerceEnd,	//*FINCOMUSU
	BankEnd,		//*FINBAN
	UserCommerceOk,		//*COMUSUOK
	UserCommerceReject,	//*COMUSUNO
	Drop,			//*TI
	CastSpell,		//*LH
	LeftClick,		//*LC
	DoubleClick,		//*RC
	Work,			//*UK
	UseSpellMacro,		//*UMH
	UseItem,		//*USA
	CraftBlacksmith,	//*CNS
	CraftCarpenter,		//*CNC
	WorkLeftClick,		//*WLC
	CreateNewGuild,		//*CIG
	SpellInfo,		//*INFS
	EquipItem,		//*EQUI
	ChangeHeading,		//*CHEA
	ModifySkills,		//*SKSE
	Train,			//*ENTR
	CommerceBuy,		//*COMP
	BankExtractItem,	//*RETI
	CommerceSell,		//*VEND
	BankDeposit,		//*DEPO
	ForumPost,		//*DEMSG
	MoveSpell,		//*DESPHE
	ClanCodexUpdate,	//*DESCOD
	UserCommerceOffer,	//*OFRECER
	GuildAcceptPeace,	//*ACEPPEAT
	GuildRejectAlliance,	//*RECPALIA
	GuildRejectPeace,	//*RECPPEAT
	GuildAcceptAlliance,	//*ACEPALIA
	GuildOfferPeace,	//*PEACEOFF
	GuildOfferAlliance,	//*ALLIEOFF
	GuildAllianceDetails,	//*ALLIEDET
	GuildPeaceDetails,	//*PEACEDET
	GuildRequestJoinerInfo,	//*ENVCOMEN
	GuildAlliancePropList,	//*ENVALPRO
	GuildPeacePropList,	//*ENVPROPP
	GuildDeclareWar,	//*DECGUERR
	GuildNewWebsite,	//*NEWWEBSI
	GuildAcceptNewMember,	//*ACEPTARI
	GuildRejectNewMember,	//*RECHAZAR
	GuildKickMember,	//*ECHARCLA
	GuildUpdateNews,	//*ACTGNEWS
	GuildMemberInfo,	//*1HRINFO<
	GuildOpenElections,	//*ABREELEC
	GuildRequestMembership,	//*SOLICITUD
	GuildRequestDetails,	//*CLANDETAILS
	Online,			//*/ONLINE
	Quit,			//*/SALIR
	GuildLeave,		//*/SALIRCLAN
	RequestAccountState,	//*/BALANCE
	PetStand,		//*/QUIETO
	PetFollow,		//*/ACOMPA�AR
	TrainList,		//*/ENTRENAR
	Rest,			//*/DESCANSAR
	Meditate,		//*/MEDITAR
	Resucitate,		//*/RESUCITAR
	Heal,			//*/CURAR
	Help,			//*/AYUDA
	RequestStats,		//*/EST
	CommerceStart,		//*/COMERCIAR
	BankStart,		//*/BOVEDA
	Enlist,			//*/ENLISTAR
	Information,		//*/INFORMACION
	Reward,			//*/RECOMPENSA
	RequestMOTD,		//*/MOTD
	Uptime,			//*/UPTIME
	PartyLeave,		//*/SALIRPARTY
	PartyCreate,		//*/CREARPARTY
	PartyJoin,		//*/PARTY
	Inquiry,		//*/ENCUESTA	(	with	no	params	)
	GuildMessage,		//*/CMSG
	PartyMessage,		//*/PMSG
	CentinelReport,		//*/CENTINELA
	GuildOnline,		//*/ONLINECLAN
	PartyOnline,		//*/ONLINEPARTY
	CouncilMessage,		//*/BMSG
	RoleMasterRequest,	//*/ROL
	GMRequest,		//*/GM
	bugReport,		//*/_BUG
	ChangeDescription,	//*/DESC
	GuildVote,		//*/VOTO
	Punishments,		//*/PENAS
	ChangePassword,		//*/PASSWD
	Gamble,			//*/APOSTAR
	InquiryVote,		//*/ENCUESTA	(	with	parameters	)
	LeaveFaction,		//*/RETIRAR	(	with	no	arguments	)
	BankExtractGold,	//*/RETIRAR	(	with	arguments	)
	BankDepositGold,	//*/DEPOSITAR
	Denounce,		//*/DENUNCIAR
	GuildFundate,		//*/FUNDARCLAN
	PartyKick,		//*/ECHARPARTY
	PartySetLeader,		//*/PARTYLIDER
	PartyAcceptMember,	//*/ACCEPTPARTY
	GuildMemberList,
	GMMessage,		//*/GMSG
	showName,		//*/SHOWNAME
	OnlineRoyalArmy,	//*/ONLINEREAL
	OnlineChaosLegion,	//*/ONLINECAOS
	GoNearby,		//*/IRCERCA
	comment,		//*/REM
	serverTime,		//*/HORA
	Where,			//*/DONDE
	CreaturesInMap,		//*/NENE
	WarpMeToTarget,		//*/TELEPLOC
	WarpChar,		//*/TELEP
	Silence,		//*/SILENCIAR
	SOSShowList,		//*/SHOW	SOS
	SOSRemove,		//*SOSDONE
	GoToChar,		//*/IRA
	invisible,		//*/INVISIBLE
	GMPanel,		//*/PANELGM
	RequestUserList,	//*LISTUSU
	Working,		//*/TRABAJANDO
	Hiding,			//*/OCULTANDO
	Jail,			//*/CARCEL
	KillNPC,		//*/RMATA
	WarnUser,		//*/ADVERTENCIA
	EditChar,		//*/MOD
	RequestCharInfo,	//*/INFO
	RequestCharStats,	//*/STAT
	RequestCharGold,	//*/BAL
	RequestCharInventory,	//*/INV
	RequestCharBank,	//*/BOV
	RequestCharSkills,	//*/SKILLS
	ReviveChar,		//*/REVIVIR
	OnlineGM,		//*/ONLINEGM
	OnlineMap,		//*/ONLINEMAP
	Forgive,		//*/PERDON
	Kick,			//*/ECHAR
	Execute,		//*/EJECUTAR
	BanChar,		//*/BAN
	UnbanChar,		//*/UNBAN
	NPCFollow,		//*/SEGUIR
	SummonChar,		//*/SUM
	SpawnListRequest,	//*/CC
	SpawnCreature,		//*SPA
	ResetNPCInventory,	//*/RESETINV
	CleanWorld,		//*/LIMPIAR
	ServerMessage,		//*/RMSG
	NickToIP,		//*/NICK2IP
	IPToNick,		//*/IP2NICK
	GuildOnlineMembers,	//*/ONCLAN
	TeleportCreate,		//*/CT
	TeleportDestroy,	//*/DT
	RainToggle,		//*/LLUVIA
	SetCharDescription,	//*/SETDESC
	ForceMIDIToMap,		//*/FORCEMIDIMAP
	ForceWAVEToMap,		//*/FORCEWAVMAP
	RoyalArmyMessage,	//*/REALMSG
	ChaosLegionMessage,	//*/CAOSMSG
	CitizenMessage,		//*/CIUMSG
	CriminalMessage,	//*/CRIMSG
	TalkAsNPC,		//*/TALKAS
	DestroyAllItemsInArea,	//*/MASSDEST
	AcceptRoyalCouncilMember,//*/ACEPTCONSE
	AcceptChaosCouncilMember,//*/ACEPTCONSECAOS
	ItemsInTheFloor,	//*/PISO
	MakeDumb,		//*/ESTUPIDO
	MakeDumbNoMore,		//*/NOESTUPIDO
	DumpIPTables,		//*/DUMPSECURITY"
	CouncilKick,		//*/KICKCONSE
	SetTrigger,		//*/TRIGGER
	AskTrigger,
	BannedIPList,		//*/BANIPLIST
	BannedIPReload,		//*/BANIPRELOAD
	GuildCompleteMemberList,	//*/MIEMBROSCLAN
	GuildBan,		//*/BANCLAN
	BanIP,			//*/BANIP
	UnbanIP,		//*/UNBANIP
	CreateItem,		//*/CI
	DestroyItems,		//*/DEST
	ChaosLegionKick,	//*/NOCAOS
	RoyalArmyKick,		//*/NOREAL
	ForceMIDIAll,		//*/FORCEMIDI
	ForceWAVEAll,		//*/FORCEWAV
	RemovePunishment,	//*/BORRARPENA
	TileBlockedToggle,	//*/BLOQ
	KillNPCNoRespawn,	//*/MATA
	KillAllNearbyNPCs,	//*/MASSKILL
	LastIP,			//*/LASTIP
	ChangeMOTD,		//*/MOTDCAMBIA
	SetMOTD,		//*ZMOTD
	SystemMessage,		//*/SMSG
	CreateNPC,		//*/ACC
	CreateNPCWithRespawn,	//*/RACC
	ImperialArmour,		//*/AI1	-	4
	ChaosArmour,		//*/AC1	-	4
	NavigateToggle,		//*/NAVE
	ServerOpenToUsersToggle,//*/HABILITAR
	TurnOffServer,		//*/APAGAR
	TurnCriminal,		//*/CONDEN
	ResetFactions,		//*/RAJAR
	RemoveCharFromGuild,	//*/RAJARCLAN
	RequestCharMail,	//*/LASTEMAIL
	AlterPassword,		//*/APASS
	AlterMail,		//*/AEMAIL
	AlterName,		//*/ANAME
	ToggleCentinelActivated,//*/CENTINELAACTIVADO
	DoBackUp,		//*/DOBACKUP
	ShowGuildMessages,	//*/SHOWCMSG
	SaveMap,		//*/GUARDAMAPA
	ChangeMapInfoPK,	//*/MODMAPINFO	PK
	ChangeMapInfoBackup,	//*/MODMAPINFO	BACKUP
	ChangeMapInfoRestricted,//*/MODMAPINFO	RESTRINGIR
	ChangeMapInfoNoMagic,	//*/MODMAPINFO	MAGIASINEFECTO
	ChangeMapInfoNoInvi,	//*/MODMAPINFO	INVISINEFECTO
	ChangeMapInfoNoResu,	//*/MODMAPINFO	RESUSINEFECTO
	ChangeMapInfoLand,	//*/MODMAPINFO	TERRENO
	ChangeMapInfoZone,	//*/MODMAPINFO	ZONA
	SaveChars,		//*/GRABAR
	CleanSOS,		//*/BORRAR	SOS
	ShowServerForm,		//*/SHOW	INT
	night,			//*/NOCHE
	KickAllChars,		//*/ECHARTODOSPJS
	RequestTCPStats,	//*/TCPESSTATS
	ReloadNPCs,		//*/RELOADNPCS
	ReloadServerIni,	//*/RELOADSINI
	ReloadSpells,		//*/RELOADHECHIZOS
	ReloadObjects,		//*/RELOADOBJ
	Restart,		//*/REINICIAR
	ResetAutoUpdate,	//*/AUTOUPDATE
	ChatColor,		//*/CHATCOLOR
	Ignored,		//*/IGNORADO
	CheckSlot,		//*/SLOT
	GetClasesInfo,		//*Nuevo paquete
	GetRazasInfo,		//*Nuevo paquete
	GetCiudadesInfo,		//*Nuevo paquete
	Ping	//*Nuevo Paquete
};






class cPaqueteCliente{
	public:
		cPaqueteCliente(bool c) : critico(c){}
		virtual ~cPaqueteCliente(){}
		virtual bool serialize(cByteQueue* q){return false;}
		bool escritico(){return critico;}
	private:
		bool critico;
};

/*
-----------------------------------------------------------------------
----------------------Paquetes-del-Cliente-----------------------------
-----------------------------------------------------------------------
*/
//FIXME: los static const aca estan para el culo, deben estar duplicados 30 veces en todo el binario. :D. Fui yo, lo acepto, pero ahora no lo voy a a arreglar.

class cPCLoginExistingChar : public cPaqueteCliente{
	public:
		cPCLoginExistingChar(std::string _user, std::string _passwd,
				Sint8 vM, Sint8 vm, Sint8 vr) : cPaqueteCliente(true), User(_user), Password(_passwd), versionM(vM), versionm(vm), versionr(vr) {
			
		}
		~cPCLoginExistingChar(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = LoginExistingChar;
		std::string User;
		std::string Password;
		Sint8 versionM;
		Sint8 versionm;
		Sint8 versionr;
		Sint16 versiones[7];
};

class cPCWalk : public cPaqueteCliente{
	public:
		cPCWalk(Sint8 _heading) : cPaqueteCliente(true),heading(_heading) {}
		~cPCWalk(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id =  Walk;
		Sint8 heading;
};

class cPCLeftClick : public cPaqueteCliente{
	public:
		cPCLeftClick(Sint8 _x,Sint8 _y) : cPaqueteCliente(true),x(_x),y(_y){}
		~cPCLeftClick(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = LeftClick;
		Sint8 x,y;
};

class cPCDoubleClick : public cPaqueteCliente{
	public:
		cPCDoubleClick(Sint8 _x,Sint8 _y) : cPaqueteCliente(true),x(_x),y(_y){}
		~cPCDoubleClick(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = DoubleClick;
		Sint8 x,y;
};

class cPCAttack : public cPaqueteCliente{
	public:
		cPCAttack() : cPaqueteCliente(true){}
		~cPCAttack(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = Attack;
};

class cPCCombatModeToggle : public cPaqueteCliente{
	public: 
		cPCCombatModeToggle() : cPaqueteCliente(true){}
		~cPCCombatModeToggle(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = CombatModeToggle;
};

class cPCChangeHeading : public cPaqueteCliente{
	public:
		cPCChangeHeading(Sint8 _heading) : cPaqueteCliente(true),heading(_heading){}
		~cPCChangeHeading(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = ChangeHeading;// FIXME: ME CAGO.
		Sint8 heading;
};

class cPCPickUp : public cPaqueteCliente{
	public: 
		cPCPickUp() : cPaqueteCliente(true){}
		~cPCPickUp(){}

		bool serialize(cByteQueue* q);

	private:
		static const Uint8 id = PickUp;
};

class cPCEquipItem : public cPaqueteCliente{
	public: 
		cPCEquipItem(Sint8 _slot) : slot(_slot),cPaqueteCliente(true){}
		~cPCEquipItem(){}

		bool serialize(cByteQueue* q);

	private:
		Sint8 slot;
		static const Uint8 id = EquipItem;
};


class cPCUseItem : public cPaqueteCliente{
	public: 
		cPCUseItem(Sint8 _slot) : slot(_slot),cPaqueteCliente(true){}
		~cPCUseItem(){}

		bool serialize(cByteQueue* q);

	private:
		Sint8 slot;
		static const Uint8 id = UseItem;
};

class cPCDrop : public cPaqueteCliente{
	public:
		cPCDrop(Sint8 _slot, Sint16 _amount) : slot(_slot), amount(_amount), cPaqueteCliente(true){}
		~cPCDrop(){}

		bool serialize(cByteQueue* q);
	
	private:
		Sint8 slot;
		Sint16 amount;
		static const Uint8 id = Drop;
};

class cPCBankEnd : public cPaqueteCliente{
	public:
		cPCBankEnd() : cPaqueteCliente(false){}
		~cPCBankEnd(){}
		
		bool serialize(cByteQueue* q);
	private:
		static const Uint8 id = BankEnd;
};

class cPCBankDeposit : public cPaqueteCliente{
	public:
		cPCBankDeposit(Sint8 _slot, Uint16 _amount) : slot(_slot), amount(_amount), cPaqueteCliente(true){}
		~cPCBankDeposit(){}

		bool serialize(cByteQueue* q);
	
	private:
		Sint8 slot;
		Uint16 amount;
		static const Uint8 id = BankDeposit;
};

class cPCBankExtractItem : public cPaqueteCliente{
	public:
		cPCBankExtractItem(Sint8 _slot, Uint16 _amount) : slot(_slot), amount(_amount), cPaqueteCliente(true){}
		~cPCBankExtractItem(){}

		bool serialize(cByteQueue* q);
	
	private:
		Sint8 slot;
		Uint16 amount;
		static const Uint8 id = BankExtractItem;
};

class cPCCommerceEnd : public cPaqueteCliente{
	public:
		cPCCommerceEnd() : cPaqueteCliente(false){}
		~cPCCommerceEnd(){}
		
		bool serialize(cByteQueue* q);
	private:
		static const Uint8 id = CommerceEnd;
};


class cPCCommerceBuy : public cPaqueteCliente{
	public:
		cPCCommerceBuy(Sint8 _slot, Uint16 _amount) : slot(_slot), amount(_amount), cPaqueteCliente(true){}
		~cPCCommerceBuy(){}

		bool serialize(cByteQueue* q);
	
	private:
		Sint8 slot;
		Uint16 amount;
		static const Uint8 id = CommerceBuy;
};

class cPCCommerceSell : public cPaqueteCliente{
	public:
		cPCCommerceSell(Sint8 _slot, Uint16 _amount) : slot(_slot), amount(_amount), cPaqueteCliente(true){}
		~cPCCommerceSell(){}

		bool serialize(cByteQueue* q);
	
	private:
		Sint8 slot;
		Uint16 amount;
		static const Uint8 id = CommerceSell;
};

class cPCThrowDices : public cPaqueteCliente{
	public:
		cPCThrowDices() : cPaqueteCliente(true){}
		~cPCThrowDices(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = ThrowDices;
};

class cPCLoginNewChar : public cPaqueteCliente{
	public:
		cPCLoginNewChar(std::string n, std::string p, std::string e, Sint8 M, Sint8 m, Sint8 r, Sint8* s, Sint8 R, Sint8 Ci, Sint8 G, Sint8 Cl) : name(n),password(p),email(e),versionM(M),versionm(m),versionr(r),skills(s),raza(R),ciudad(Ci),genero(G),clase(Cl), cPaqueteCliente(true){}
		~cPCLoginNewChar(){}

		bool serialize(cByteQueue* q);
	
	private:
		std::string name;
		std::string password;
		std::string email;
		Sint8 versionM;
		Sint8 versionm;
		Sint8 versionr;
		Sint16 versiones[7];
		Sint8* skills;
		Sint8 raza;
		Sint8 ciudad;
		Sint8 genero;
		Sint8 clase;	
		static const Uint8 id = LoginNewChar;
};

class cPCTalk : public cPaqueteCliente{
	public:
		cPCTalk(std::string _what) : cPaqueteCliente(true), what(_what){}
		~cPCTalk(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = Talk;
		std::string what;
};


class cPCOnline: public cPaqueteCliente{
	public:
		cPCOnline() : cPaqueteCliente(true){}
		~cPCOnline(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = Online;
};

class cPCCastSpell: public cPaqueteCliente{
	public:
		cPCCastSpell(Sint8 _slot, Sint8 _x, Sint8 _y) : cPaqueteCliente(true), slot(_slot), x(_x), y(_y){}
		~cPCCastSpell(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = CastSpell;
		Sint8 slot;
		Sint8 x;
		Sint8 y;
};

class cPCMeditate: public cPaqueteCliente{
	public:
		cPCMeditate() : cPaqueteCliente(true){}
		~cPCMeditate(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = Meditate;
};


class cPCGetClasesInfo: public cPaqueteCliente{
	public:
		cPCGetClasesInfo() : cPaqueteCliente(true){}
		~cPCGetClasesInfo(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = GetClasesInfo;
};

class cPCGetRazasInfo: public cPaqueteCliente{
	public:
		cPCGetRazasInfo() : cPaqueteCliente(true){}
		~cPCGetRazasInfo(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = GetRazasInfo;
};

class cPCGetCiudadesInfo: public cPaqueteCliente{
	public:
		cPCGetCiudadesInfo() : cPaqueteCliente(true){}
		~cPCGetCiudadesInfo(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = GetCiudadesInfo;
};

class cPCGoToChar: public cPaqueteCliente{
public:
	cPCGoToChar(std::string _what) : cPaqueteCliente(true), what(_what){}
	~cPCGoToChar(){}

	bool serialize(cByteQueue* q);

private:
	std::string what;
	static const Uint8 id = GoToChar;
};

class cPCRequestSkills: public cPaqueteCliente{
	public:
		cPCRequestSkills() : cPaqueteCliente(true){}
		~cPCRequestSkills(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = RequestSkills;
};

class cPCModifySkills : public cPaqueteCliente{
	public:
		cPCModifySkills(std::vector<Sint8> *skills) : cPaqueteCliente(true), _skills(skills){}
		~cPCModifySkills(){}

		bool serialize(cByteQueue* q);
	
	private:
		std::vector<Sint8> *_skills;
		static const Uint8 id = ModifySkills;
};

class cPCWarpChar : public cPaqueteCliente{
public:
	cPCWarpChar(std::string _what, Uint16 _map, Uint8 _x, Uint8 _y) 
		: cPaqueteCliente(true), what(_what), x(_x), y(_y), map(_map)
		{}
	~cPCWarpChar(){}

	bool serialize(cByteQueue* q);

private:
	std::string what;
	Uint8 x,y;
	Uint16 map;
	static const Uint8 id = WarpChar;
};

class cPCPing : public cPaqueteCliente{
	public:
		cPCPing() : cPaqueteCliente(true){}
		~cPCPing(){}

		bool serialize(cByteQueue* q);
	
	private:
		static const Uint8 id = Ping;
};

#endif
