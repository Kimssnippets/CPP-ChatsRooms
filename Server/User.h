#ifndef USER_H_
#define USER_H_

#include "cRoom.h"
#include "../SocketUtils/TCPSocket.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "../SocketUtils/TCPMessengerProtocol.h"
namespace  npl{
class cRoom;

class User{

	string _name;
	string _ip;
	int _port;
	bool _inChatRoom;
	bool _inSession;
	TCPSocket* userSocket;
	User *P2PUser;
	cRoom *onChatRoom;

public:
	User(string name, TCPSocket* basesock);

	bool inChat();//True if on active chat
	bool inSession();//true if on session p2p user
	bool inChatRoom();
	void loginUsertoSession(User* partner);
	void loginUserToChatRoom(cRoom* name);
	void disconnectFromChatRom(bool fromchatroom);
	bool closeSession(bool isinitiating);
	string getusername();
	string getIP();
	int getport();
	cRoom* getChatRoom();

	TCPSocket* getSocket();
	string getDestandport();
	int readCommand();
	string readMsg();
	void writeMsg(string msg);
	void writeCommand(int command);

	virtual ~User();
};
}
#endif /* USER_H_ */
