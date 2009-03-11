#include "bytequeue.h"
#include <cstring>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

cByteQueue::cByteQueue() : lqueue(0){
	data = new unsigned char[DATA_BUFFER];
}

cByteQueue::~cByteQueue(){
	delete data;
}

void cByteQueue::printStatus(){
	#ifdef DEBUG
	cout << "- Estado de un ByteQueue en: " << this <<  " -" << endl;
	cout << "Puntero de escritura en: " << lqueue << endl;
	if(lqueue){
	cout << "- Dump -" << endl;
	int i;
	cout << " |";
	for(int i=0;i<lqueue;i++){
		cout << " ";
		if(((int) data[i])<10) cout << " ";
		if(((int) data[i])<100) cout << " ";
		cout << (int) data[i];
		if((i+1)%20==0) cout << " | " << (i+1) << endl << " |";
	}
	cout << endl;
	}
	cout << "- Fin -" << endl;
	#endif
}

int cByteQueue::RemoveData(const Uint32 howmuch){
	if((howmuch<=0)||(howmuch>lqueue)) return -1;
	memcpy(data,&data[howmuch],(lqueue-howmuch));
	lqueue-=howmuch;
	return howmuch;
}

int cByteQueue::WriteData(const char* buf, const Uint32 len){
	if(len>DATA_BUFFER-lqueue) return NOT_ENOUGH_SPACE;
	memcpy(&data[lqueue],buf,len);
	lqueue+=len;
	return len;
}

int cByteQueue::ReadData(char* buf, const Uint32 len,bool peek){
	if(len>lqueue) return NOT_ENOUGH_DATA;

	memcpy(buf,data,len);

	if(!peek) RemoveData(len);

	return len;
}


int cByteQueue::WriteString(const char* str, int len, bool fixed){
	if(!len) len=strlen(str);
	if(!fixed){
		if(lqueue>(DATA_BUFFER-(len+2))) return NOT_ENOUGH_SPACE;
		Sint16 lens=len;
		Write(lens);

	}else{
		if(lqueue>(DATA_BUFFER-len)) return NOT_ENOUGH_SPACE;
	}
	memcpy(&data[lqueue],str,len);
	lqueue+=len;
	return len;
}

int cByteQueue::ReadString(char* str, int len, unsigned int peek,bool fixed){
	if(!len) return -3;
	Sint16 nlen;
	if(fixed){
		if(len>(lqueue-peek)) return NOT_ENOUGH_DATA;
		nlen=len;
	}else{
		if(2>(lqueue-peek)) return NOT_ENOUGH_DATA;
		Peek(&nlen,peek);
		if(nlen>=len) return -3;
		if(nlen>(lqueue-peek)) return NOT_ENOUGH_DATA; //ESTAMOS EN EL HORNO
	}
	memcpy(str,&data[peek+2],nlen);
	str[nlen]=0;//Warn, en cadenas fixed el buffer tiene que ser len+1.
	if(!peek){
		if(!fixed)
			RemoveData(nlen+2);
		else
			RemoveData(nlen);
	}
	
	if(fixed) 
		return nlen;
	else
		return nlen+2;
}

