

#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include "TCPSocket.h"
#include <map>

using namespace std;
namespace npl {

	class MultipleTCPSocketsListener {
		typedef vector<TCPSocket *> tSocketsContainer;
		tSocketsContainer sockets;

	public:
		/*
         * Add the given socket to the socket list to be listen on
         */
		void addSocket(TCPSocket *socket);

		void addSockets1(map<string, TCPSocket *> socketMap);

		TCPSocket *listenToSocket(int timeout = 0);
	};

}
#endif /* MULTIPLETCPSOCKETSLISTENER_H_ */
