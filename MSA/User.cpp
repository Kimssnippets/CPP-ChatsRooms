#include "User.h"
using namespace npl;

User::User(string name, TCPSocket* sock){
	userSocket = sock;
	string tempport;
	istringstream liness( userSocket->destIpAndPort() );
	getline( liness, _ip, ':' );
	getline( liness, tempport,  ':' );
	_port= atoi(tempport.c_str());

	_inChatRoom = false;
	_inSession = false;
	_name = name;
}
TCPSocket* User::getSocket(){
	return userSocket;
}
bool User::inChat(){
	return inChatRoom() || inSession();
}
bool User::inChatRoom(){
	return _inChatRoom;
}
bool User::inSession(){
	return _inSession;
}
void User::loginUsertoSession(User* partner){
	_inSession = true;
	P2PUser = partner;

}
void User::disconnectFromChatRom(bool fromchatroom){
	if(inChatRoom())
	{
		if (!fromchatroom)
			onChatRoom->logOffUser(this);
		writeCommand(CHAT_ROOM_LEAVED);
		onChatRoom = NULL;
		_inChatRoom = false;
	}

}
void User::loginUserToChatRoom(cRoom* logtoroom){
	_inChatRoom = true;
	onChatRoom = logtoroom;
}
bool User::closeSession(bool isinitiating){
	if (!inSession())
		return true;
	if (isinitiating)
		P2PUser->closeSession(false);

	writeCommand(SESSION_CLOSED);
	_inSession = false;
	P2PUser = NULL;
	return true;
}
int User::readCommand(){
	return userSocket->readCommand();
}
string User::readMsg(){
	return userSocket->readMsg();
}
void User::writeMsg(string msg){
	userSocket->writeMsg(msg);
}
void User::writeCommand(int command){
	userSocket->writeCommand(command);
}
string User::getDestandport(){
	return userSocket->destIpAndPort();
}
string User::getusername(){
	return _name;
}
string User::getIP(){
	return _ip;
}
int User::getport(){
	return _port;
}
cRoom* User::getChatRoom(){
	return onChatRoom;
}
User::~User() {
	delete(userSocket);
}
