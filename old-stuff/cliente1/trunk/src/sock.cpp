/***************************************************************************
 *   Copyright (C) 2006 by Esteban Torren, Alejandro Santos                *
 *   esteban.torre@gmail.com alejolp@gmail.com                             *
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


#include "sock.h"
//#define DEBUG
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#ifdef WIN32

#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#endif

#define SOCKET_TMP_BUFFER_SIZE 16384

csocket::csocket(EventListener* evListener) 
: eventListener(evListener), tempBufferInLen(0), tempBufferOutLen(0),
  tempBufferIn(SOCKET_TMP_BUFFER_SIZE), tempBufferOut(),
  _conectado(false), _conectandose(false)
{
	#ifdef WIN32
	WSAStartup(MAKEWORD(2, 1), &wsaData);
	#endif	
}

csocket::~csocket()
{
	cerrar();
}

void csocket::cerrar()
{
	if ( is_conectado() )
	{
		_conectado = false;

		eventListener->socket_onEvent(this, EventListener::SOCKEVENT_CLOSE, 0);
		#ifdef DEBUG
		cout << "Lost connection." << endl;
		#endif
		#ifdef WIN32
		closesocket(sockfd);
		#else
		close(sockfd);
		#endif
	}
}

bool csocket::conectar(const char *direccion,int puerto)
{
	sockaddr_in dest_addr;
	hostent *h;
	int ret;
	int errorn;

	_conectado = false;
	_conectandose = true;

	tempBufferOutLen = 0;
	tempBufferInLen = 0;

	if((h=gethostbyname(direccion))==NULL) 
	{
		_conectandose = false;
		return false;
	}
	if((sockfd=socket(PF_INET,SOCK_STREAM,0))==(-1)) 
	{
		_conectandose = false;
		return false;
	}

	setnonblock(true);

	FD_ZERO(&readfds);
	FD_SET(sockfd, &readfds);

	memset(&dest_addr, 0, sizeof(dest_addr));

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(puerto);
	dest_addr.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)h->h_addr)));

	ret = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
	if ( ret == -1 )
	{
		errorn = getlasterror();
		if ( errorn != EINPROGRESS && errorn != EWOULDBLOCK )
		{
			_conectandose = false;
			return false;
		}
	}

	return true;
}


bool csocket::is_conectado()
{
	return _conectado;
};

void csocket::enviar(const char* data, int len)
{
	if (len + tempBufferOutLen > tempBufferOut.size())
		tempBufferOut.resize(len + tempBufferOutLen);
	tempBufferOut.insert(tempBufferOut.begin() + tempBufferOutLen, data, data + len);
	tempBufferOutLen += len;
}

int csocket::recibir(char* data, int len)
{
	unsigned int ret_len;

	if ( (unsigned int)len >= tempBufferInLen )
	{
		memcpy(data, &tempBufferIn[0], tempBufferInLen );

		ret_len = tempBufferInLen;
		tempBufferInLen = 0;
	}
	else
	{
		memcpy(data, &tempBufferIn[0], len );

		for( unsigned int i = 0; i < tempBufferInLen - (unsigned int)len; i++ )
			tempBufferIn[i] = tempBufferIn[i + len];

		ret_len = len;
		tempBufferInLen -= len;
	}

	return ret_len;
}

void csocket::flush_output()
{
	unsigned int total = 0;
	int ret;

	#ifdef DEBUG
	cout << "Enviando: " << bytesleft << " bytes...";
	outbuff->printStatus();
	#endif

	while (total < tempBufferOutLen)
	{
		ret = send(sockfd, &tempBufferOut[total], tempBufferOutLen - total, 0);
		if(ret == -1) 
		{
			if ( getlasterror() == EWOULDBLOCK )
			{
				break;
			}
			else
			{
				//herror("send");
				cerrar();
				return;
			}
		}
		else if (ret == 0)
		{
			// Uh? Ocurre esto?
			break;
		}
		else
		{
			total += ret;
		}
	}

	tempBufferOutLen -= total;

	if (tempBufferOutLen > 0)
	{
		std::vector<char> tmp(tempBufferOut.begin() + total, tempBufferOut.end());
		tempBufferOut.swap(tmp);
		tempBufferOut.reserve(SOCKET_TMP_BUFFER_SIZE);
	}
	else
	{
		tempBufferOut.erase(tempBufferOut.begin(), tempBufferOut.end());
		eventListener->socket_onEvent(this, EventListener::SOCKEVENT_WRITE, 0);
	}

	#ifdef DEBUG
	cout << "OK." << endl;
	#endif
}

void csocket::flush_input()
{
	int n = 0;
	int maxlen = (int)tempBufferIn.size() - tempBufferInLen;

	if ( maxlen > 0 )
	{
		n = recv(sockfd, &tempBufferIn[tempBufferInLen], maxlen, 0);
		if (n <= 0)
		{
			int errorn = getlasterror();
			if (errorn)
			{
				cerrar();
				return;
			}
		}
	}

	tempBufferInLen += n;
	if ( tempBufferInLen > 0 )
		eventListener->socket_onEvent(this, EventListener::SOCKEVENT_READ, tempBufferInLen);

	#ifdef DEBUG
	cout << "Se recibieron: " << n << "bytes" << endl;
	inbuff->printStatus();
	#endif
}

void csocket::setnonblock(bool nonblock)
{
#ifdef WIN32
	u_long arg = nonblock ? 1 : 0;
	ioctlsocket(sockfd, FIONBIO, &arg);
#else
	int opts;

	opts = fcntl(sockfd,F_GETFL);
	if (opts < 0) {
		perror("fcntl(F_GETFL)");
		exit(EXIT_FAILURE);
	}
	opts = (opts | O_NONBLOCK);
	if (fcntl(sockfd,F_SETFL,opts) < 0) {
		perror("fcntl(F_SETFL)");
		exit(EXIT_FAILURE);
	}
#endif
}

void csocket::poll_status()
{
	if ( _conectandose )
	{
		if ( select_write() )
		{
			_conectado = true;
			_conectandose = false;

			eventListener->socket_onEvent(this, EventListener::SOCKEVENT_CONNECT, 0);
		}
	}
	else if ( _conectado )
	{
		if ( select_read() )
			flush_input();

		// Tengo que preguntar si sigue conectado porque select_read
		// puede cerrar el socket.
		if ( _conectado && tempBufferOutLen > 0 )
			flush_output();
	}
}

bool csocket::select_write()
{
	struct timeval tv;
	fd_set fdtest;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fdtest);
	FD_SET(sockfd, &fdtest);
	if(select((int)(sockfd+1),NULL,&fdtest,NULL,&tv)>0)
	{
		if(FD_ISSET(sockfd,&fdtest))
		{
			return true;
		}
	}
	return false;
}

bool csocket::select_read()
{
	struct timeval tv;
	fd_set fdtest_r, fdtest_e;
	int ret;
	
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	
	FD_ZERO(&fdtest_r);
	FD_ZERO(&fdtest_e);
	
	FD_SET(sockfd, &fdtest_r);
	FD_SET(sockfd, &fdtest_e);
	
	ret = select((int)(sockfd+1),&fdtest_r, NULL, &fdtest_e, &tv);
	
	if (ret > 0) {
		// Primero verifico si llegaron datos, y luego
		// si hubo algun error. Lo hago en este orden porque 
		// pueden ocurrir las dos cosas y si no recibo antes
		// de cerrar, puedo perder datos.
		
		if(FD_ISSET(sockfd, &fdtest_r)) {
			return true;
		}
		
		if(_conectado && FD_ISSET(sockfd, &fdtest_e)) {
			cerrar();
		}
	} else if (ret == -1) {
		cerrar();
	}
	
	return false;
}

