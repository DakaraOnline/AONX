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


#ifndef __sock_h_
#define __sock_h_

#include <vector>

#include <string.h>
#include <errno.h>
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <winsock2.h>
#define EINPROGRESS WSAEINPROGRESS 
#define EWOULDBLOCK WSAEWOULDBLOCK
#else
typedef int SOCKET;
#endif


class csocket{
	public:
		class EventListener {
		public:
			enum SocketEventsTypes {
				SOCKEVENT_CONNECT,
				SOCKEVENT_READ,
				SOCKEVENT_WRITE,
				SOCKEVENT_CLOSE
			};
			virtual void socket_onEvent(csocket* sock, SocketEventsTypes ev_type, int param1) = 0;
		};
	public:
		csocket(EventListener* evListener);
		~csocket();

		void cerrar();
		bool conectar(const char *direccion,int puerto);
		bool is_conectado();

		int recibir(char* data, int len);
		void enviar(const char* data, int len);

		void poll_status();

	private:

		void setnonblock(bool nonblock);
		void flush_output();
		void flush_input();

		bool select_write();
		bool select_read();

		int getlasterror()
		{
			#ifdef WIN32
			return WSAGetLastError();
			#else
			return errno;
			#endif
		}

		#ifdef WIN32
		WSADATA wsaData;
		WSAEVENT wsaEv;
		#endif

		std::vector<char> tempBufferIn;
		unsigned int tempBufferInLen;

		std::vector<char> tempBufferOut;
		unsigned int tempBufferOutLen;

		bool _conectado;
		bool _conectandose;

		fd_set readfds;

		SOCKET sockfd;
		int port;
		char *r_ip;
		EventListener* eventListener;
};

#endif
