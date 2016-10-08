#ifndef CLIENTMANAGER_H_
#define CLIENTMANAGER_H_

#include "UdpClientMessenger.h"
#include "../SocketUtils/MThread.h"
#include "../SocketUtils/TCPSocket.h"
#include <vector>
using namespace std;
namespace  npl{
class usersSockets
{
public:
	string _sideB_name;
	string _IP;
	int _port;
	void Clean()//CLEAN TO IP+PORT+USERNAME OF SIDE B
	{
		_sideB_name.clear();
		_IP.clear();
		_port = 0;
	}
};

class TcpCLientMessenger : public MThread{
	TCPSocket* serverSocket;
	bool running;
	usersSockets udpChatSideB;//IF ON SESSION SO THE IP+PORT WILL BE HERE
	string _username;//USER NAME
	vector<usersSockets*> chatUsers;//THE USERS ON THE CHATS
	string chatRoomName;//IF THE USER ON CHAT SO THIS VAR INSTALL WITH ROOM NAME
	UdpClientMessenger *clientLinker;
	bool sessionOn;//TRUE IF USER IS ON SESSION
	bool roomOn;//IF THE USER ON CHAT ROOM
	bool login;
public:
    bool isLogin() const;

private:
//IF ALLREADY LOGIN IS TRUE

	void run();

	void clearRoomUsers();
	void addRoomUser(string roomate, string IP, int port);

public:
	bool connectToServer(string ip,int port);
	void sign(string username,string password,int oper);
	void log(string username,string password,int oper);
	bool openSession(string chatSideBName);
	void printCurrentInfo();
	bool sendMsg(string msg);

	bool createChatRoom(string name);
	bool loginToChatRoom(string msg);

	void prinCtonnectedUsers();
	void printConnectedUsers();
	void printListUsers();

	void RoomsList();
	void listConnectedUsersInRoom(string roomName);
	void listUsers();

	//bool closeSession();
	bool exitRoomOrCloseSession();
	bool deleteChatRoom(string msg);

	//bool isConnectedToServer();
	bool isInChat();
	void exitAll();
	TcpCLientMessenger();
	virtual ~TcpCLientMessenger();
	//handling server responses
	void chatRoomLeaved();
	void chatRoomUpdate();
	void printRoomsList();

};
}
#endif /* CLIENTMANAGER_H_ */
