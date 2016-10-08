#ifndef CHATROOM_H_
#define CHATROOM_H_

#include "User.h"
#include <vector>
#include <iostream>
#include "../SocketUtils/TCPMessengerProtocol.h"
using namespace std;
namespace  npl{
class User;

class cRoom {
	string chatRoomName;
public:
	const string &getChatRoomName() const;

private:
	vector<User*> charRoomUsers;
	User* _roomOwner;
	pthread_mutex_t mutx_roomUsersVec;
	void updateusers();

public:
	cRoom(User* owner, string chatroom);
	bool  logOffUser(User *usertologof);
	bool  addUser(User* userToAdd);
	User* getOwner();
	int   sendUserList(User *sendto);
	void  printUsers();
	virtual ~cRoom();
};
}
#endif /* CHATROOM_H_ */

