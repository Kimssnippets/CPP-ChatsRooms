#ifndef SERVERMANAGER_H_
#define SERVERMANAGER_H_

#include <map>
#include "User.h"
#include "../SocketUtils/MThread.h"
#include "../SocketUtils/MultipleTCPSocketListener.h"
#include "../SocketUtils/MultipleTCPSocketListener.h"
#include "../SocketUtils/TCPMessengerProtocol.h"
namespace npl{
class User;

class TcpServerMessenger: public MThread {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Please note you have to change this path respectively to your project direction! otherwise users cannot register OR login*/
string userList = "/Users/admin/ClionProjects/-CPlusPlus-NetworkProgramingLab/MSA/userList.txt";//file of the userlist (path)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultipleTCPSocketsListener *multiUserListener;//socket listener for
pthread_mutex_t users_mutx;
pthread_mutex_t chatroom_mutx;
map<string, User*> usersMap;
map<string, cRoom*> chatRoomsMap;
bool running;
bool activeRoom=false;
void createSession(User* initiatingUser, User* targetUser);



public:

	TcpServerMessenger();
	void run();
	bool addUser(TCPSocket*  userSocket, string LoginUserName);
	void exitServer(User* clientName);
	void readFromFile(User *clientName);
	void readfromChatRoom(User *clientName);
	void readfromUsers(User *clientName);
	void printToSreen(string msgToScreen);
	int  numOfUsersFromFile();
	int  numOfUserFromList();
	int  getListConnectedUsers();
	int  getListConnectedUsers(User *client);
	void getListSessions();
	void getListRooms();
	void getListRooms(User *clientName);
	int  getListChatUsers(string ChatRoomName);
	int  getListChatUsers(User *clientName);
	void getListUsers();
	void getListUsers(User *clientName);
	void createChatRoom(User* creator);
	void deleteChatRoom(User* creator);
	void loginChatRoom(User* creator);

	virtual ~TcpServerMessenger();

    bool createSession(string userToChatWith);
    bool createCR(string chatRoomName);
    bool closeCR(string chatRoomName);
    bool loginToChatRoom(string chatRoomName);
    bool chatRoomExists(string chatRoomName);
    map<string,User*>::iterator getBeginIter();
    map<string,User*>::iterator getEndIter();

};
}
#endif /* SERVERMANAGER_H_ */
