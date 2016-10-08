#include "cRoom.h"
using namespace npl;





cRoom::cRoom(User* owner, string chatRoom) {
	pthread_mutex_init(&mutx_roomUsersVec,NULL);
	_roomOwner = owner;
	chatRoomName = chatRoom;
}
void cRoom::updateusers(){
	pthread_mutex_lock(&mutx_roomUsersVec);
	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
	{
		(*iter)->writeCommand(CHAT_ROOM_UPDATED);
		(*iter)->writeMsg(chatRoomName);
		(*iter)->writeCommand(charRoomUsers.size());

		for(vector<User*>::iterator iter2 = charRoomUsers.begin(); iter2 != charRoomUsers.end(); iter2++)
		{
			(*iter)->writeMsg((*iter2)->getusername());
			(*iter)->writeMsg((*iter2)->getIP());
			(*iter)->writeCommand((*iter2)->getport());
		}
	}
	pthread_mutex_unlock(&mutx_roomUsersVec);
}
void cRoom::printUsers(){
	pthread_mutex_lock(&mutx_roomUsersVec);
	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
	{
		cout<<(*iter)->getusername()<<endl;
	}
	pthread_mutex_unlock(&mutx_roomUsersVec);
}
int cRoom::sendUserList(User *sendto){
	int numOfUsers = 0;

	pthread_mutex_lock(&mutx_roomUsersVec);

	sendto->writeCommand(charRoomUsers.size());
	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
	{
		sendto->writeMsg((*iter)->getusername());
		numOfUsers++;
	}

	pthread_mutex_unlock(&mutx_roomUsersVec);
	return numOfUsers;
}
bool cRoom::addUser(User* userToAdd){
	bool exist = false;

	// check if exist
	pthread_mutex_lock(&mutx_roomUsersVec);

	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
	{
		if ((*iter) == userToAdd)
		{
			pthread_mutex_unlock(&mutx_roomUsersVec);
			exist = true;
		}

	}
	pthread_mutex_unlock(&mutx_roomUsersVec);


	if(exist)
	{
		cout << "User already exist" <<endl;
		return false;
	}

	pthread_mutex_lock(&mutx_roomUsersVec);
	charRoomUsers.push_back(userToAdd);
	pthread_mutex_unlock(&mutx_roomUsersVec);
	updateusers();

	return true;
}
User* cRoom::getOwner(){
	return _roomOwner;
}
bool cRoom::logOffUser(User *usertologof){
	bool exist = false;

	// check if exist
	pthread_mutex_lock(&mutx_roomUsersVec);

	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
	{
		if ((*iter) == usertologof)
		{
			pthread_mutex_unlock(&mutx_roomUsersVec);
			exist = true;
		}

	}
	pthread_mutex_unlock(&mutx_roomUsersVec);


	if(!exist){
		return false;
	}

	pthread_mutex_lock(&mutx_roomUsersVec);
	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
		{
		if ((*iter) == usertologof)
		{
			charRoomUsers.erase(iter);
			break;
		}
	}
	pthread_mutex_unlock(&mutx_roomUsersVec);
	updateusers();
	return true;
}
cRoom::~cRoom() {

	pthread_mutex_lock(&mutx_roomUsersVec);
	for(vector<User*>::iterator iter = charRoomUsers.begin(); iter != charRoomUsers.end(); iter++)
	{
		(*iter)->disconnectFromChatRom(true);
	}
	pthread_mutex_unlock(&mutx_roomUsersVec);

}

const string &cRoom::getChatRoomName() const {
	return chatRoomName;
}
