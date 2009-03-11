
// Fast port of clsByteQueue.cls - FIFO list of bytes
// Designed by Juan Martín Sotuyo Dodero (Maraxus)
// Implemented in C++ by Esteban Torre (Piluex)


#ifndef _bytequeue_h_
#define _bytequeue_h_

#include <SDL.h>

//#define DEBUG

/*The error number thrown when there  is not enough data in the buffer
to be read or not enough space to write.*/
#define NOT_ENOUGH_DATA	-1
#define NOT_ENOUGH_SPACE -2

//Default size of a data buffer
#define DATA_BUFFER	8129


/// @author: Esteban Torre <esteban.torre@gmail.com>
/// @note: Los templates son tan hermosos como peligrosos,
///	si no se tiene cuidado a la hora de escribir el 
///	protocolo (te equivocas de tipo en la variable 
///	que pases) se va todo al carajo. Pero son tan cómodos...
/// @todo: Falta Soporte unicode, len*2?, no se.

class cByteQueue {
	private:
		unsigned char* data;
		int lqueue;
		
	public:
		cByteQueue();
		~cByteQueue();
		void printStatus();
		int WriteData(const char* buf, const Uint32 len);
		int ReadData(char* buf, const Uint32 len, bool peek=false);
		template <typename D1>
		int Write(const D1 d){
			if(lqueue>(DATA_BUFFER-sizeof(D1))) return NOT_ENOUGH_SPACE;
			memcpy(&data[lqueue],(void *)&d,sizeof(D1));
			int i;
			char tmp;
			/*for(i=0;i<(sizeof(D1)/2);i++){
				memcpy((void*)(&tmp),&data[lqueue+i],1);
				memcpy(&data[lqueue+i],&data[lqueue+sizeof(D1)-i-1],1);
				memcpy(&data[lqueue+sizeof(D1)-i-1],(void*)(&tmp),1);
			}*/
			lqueue+=sizeof(D1);
			return sizeof(D1);
		}

		int WriteString(const char* str, int len=0, bool fixed=false);

		template <typename D2>
		int Read(D2 *d){
			if(lqueue<sizeof(D2)) return NOT_ENOUGH_DATA;
			memcpy(d,data,sizeof(D2));
			RemoveData(sizeof(D2));
			return sizeof(D2);
		}

		int ReadString(char* str, int len, unsigned int peek=0, bool fixed=false);

		template <typename D3>
		int Peek(D3 *d, unsigned int offset=0){
			if((lqueue-offset)<sizeof(D3)) return NOT_ENOUGH_DATA;
			memcpy(d,&data[offset],sizeof(D3));
			return sizeof(D3);	
		}

		int RemoveData(const Uint32 howmuch);
		
		int len(){return lqueue;}
		int capacity(){return (DATA_BUFFER-lqueue);}
		void clear(){lqueue=0;}
		unsigned char* raw(){return data;}
		///void flush();
		///void fill();
};

#endif
