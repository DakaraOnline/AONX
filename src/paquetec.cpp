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

#include "paquetec.h"


bool cPCLoginExistingChar::serialize(cByteQueue* q){
	q->Write(id);
	q->WriteString(User.c_str());
	q->WriteString(Password.c_str());
	q->Write(versionM);
	q->Write(versionm);
	q->Write(versionr);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	return true;
}



bool cPCWalk::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(heading);
	return true;
}



bool cPCLeftClick::serialize(cByteQueue* q)
{
	q->Write(id);
	q->Write(x);
	q->Write(y);
	return true;
}


bool cPCDoubleClick::serialize(cByteQueue* q)
{
	q->Write(id);
	q->Write(x);
	q->Write(y);
	return true;
}



bool cPCAttack::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}


bool cPCCombatModeToggle::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}

bool cPCChangeHeading::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(heading);
	return true;
}

bool cPCPickUp::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}

bool cPCEquipItem::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	return true;
}

bool cPCUseItem::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	return true;
}

bool cPCDrop::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	q->Write(amount);
	return true;
}

bool cPCBankEnd::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}

bool cPCBankDeposit::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	q->Write(amount);
	return true;
}

bool cPCBankExtractItem::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	q->Write(amount);
	return true;
}

bool cPCCommerceEnd::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}

bool cPCCommerceBuy::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	q->Write(amount);
	return true;
}

bool cPCCommerceSell::serialize(cByteQueue* q){
	q->Write(id);
	q->Write(slot);
	q->Write(amount);
	return true;
}

bool cPCThrowDices::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}

bool cPCLoginNewChar::serialize(cByteQueue* q){
	q->Write(id);
	//Versiones las bypasseo..
	q->WriteString(name.c_str());
	q->WriteString(password.c_str());
	q->Write(versionM);
	q->Write(versionm);
	q->Write(versionr);
	//Versiones......
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write((Sint16)1);
	q->Write(raza);
	q->Write(genero);
	q->Write(clase);
	for(int i=0;i<21;i++){
		q->Write(skills[i]);
	}
	q->WriteString(email.c_str());
	q->Write(ciudad);
	q->printStatus();
	return true;
}

bool cPCTalk::serialize(cByteQueue* q){
	q->Write(id);
	q->WriteString(what.c_str());
	return true;
}

bool cPCOnline::serialize(cByteQueue* q){
	q->Write(id);
	return true;
}
