#include "TcpServerMessenger.h"
using namespace npl;


TcpServerMessenger::TcpServerMessenger() {

	pthread_mutex_init(&users_mutx,NULL);
	pthread_mutex_init(&chatroom_mutx,NULL);
	multiUserListener = NULL;
	running = true;

	start();
	cout<<"server manager is now up"<<endl;
}
void TcpServerMessenger::run(){
	running = true;
		User* currUser = NULL;
		multiUserListener = NULL;
		long command = 0;
		string msg;
		while (running)
		{
			// Create listener
			if (multiUserListener != NULL)
			{
				delete(multiUserListener);
			}
			multiUserListener = new MultipleTCPSocketsListener();


			//---------------------------------lock--------------------------------
			pthread_mutex_lock(&users_mutx);

			// convert User to Socket before adding to list
			map<string,TCPSocket*> toSocket;
			for (map<string,User*>::iterator biter = usersMap.begin(); biter != usersMap.end(); biter++)
			{
				toSocket[biter->first] = (biter->second->getSocket());
			}

			// Add socket
			multiUserListener->addSockets1(toSocket);

			//----------------------------free lock------------------------------
			pthread_mutex_unlock(&users_mutx);
			//-------------------------------------------------------------------



			// listen to socket
			TCPSocket* readyPeer = multiUserListener->listenToSocket(2);
			if (!readyPeer){
				continue;
			}

			// ------------------------- lock --------------------------------------
			pthread_mutex_lock(&users_mutx);

			//found user from tcpsocket list
			for (map<string,User*>::iterator iter = usersMap.begin(); iter != usersMap.end(); iter++)
			{
				if (readyPeer == iter->second->getSocket())
				{
					currUser = iter->second;
					break;
				}
			}

			// ----------------------free lock---------------------------------------
			pthread_mutex_unlock(&users_mutx);
			//-----------------------------------------------------------------------

			// READ command from the user
			command = currUser->readCommand();

			switch(command)
			{
			case 0:
				exitServer(currUser);
				break;
			case SESSION_CREATE:
				msg = currUser->readMsg();
				if (!usersMap[msg])
				{
					currUser->writeCommand(SESSION_CREATE_REFUSED);
					currUser->writeMsg(string("there is no  such user"));
					break;
				}
				else if (usersMap[msg]->inChat())
				{
					currUser->writeCommand(SESSION_CREATE_REFUSED);
					currUser->writeMsg(string("the wanted user in chat"));
					break;
				}
				createSession(currUser,usersMap[msg]);
				cout<<"Session was created between: "<<currUser->getusername()<<" AND "<<msg<<endl;
				break;
			case EXIT:
				exitServer(currUser);
				break;
			case SESSION_CLOSE:
				currUser->closeSession(true);
				break;
			case CHAT_ROOM_CREATE:
				createChatRoom(currUser);
				break;
			case CHAT_ROOM_CLOSE:
				deleteChatRoom(currUser);
				break;
			case CHAT_ROOM_LOGIN:
				loginChatRoom(currUser);
				break;
			case CHAT_ROOM_EXIT:
				currUser->disconnectFromChatRom(false);
				break;
			case LIST_CONNECTED_USERS:
				getListConnectedUsers(currUser);
				break;
			case LIST_ROOMS:
				getListRooms(currUser);
			break;
			case LIST_CONNECTED_USERS_IN_ROOM:
				getListChatUsers(currUser);
				break;
			case LIST_USERS:
				getListUsers(currUser);
				break;
			}
		}
	}
bool TcpServerMessenger::addUser(TCPSocket* userSocket, string LoginUserName){
	bool added = true;
	User* userToAdd = new User(LoginUserName,userSocket);

	int numBefor = this->getListConnectedUsers();
	pthread_mutex_lock(&users_mutx);
	usersMap.insert(pair<string,User*>(LoginUserName,userToAdd));
	pthread_mutex_unlock(&users_mutx);
	cout << "user " << LoginUserName << " has connected" << endl;

	return added;
}
int TcpServerMessenger::getListConnectedUsers(){
	cout<<"The Connected users are:"<<endl;

		map<string,User*>::iterator iter ;

		string name;
		int count = 0;
		for (iter = usersMap.begin() ; iter != usersMap.end();iter++)
			{
				name = iter->first;
				printToSreen(name);
				count++;
			}
		return count;
}
int TcpServerMessenger::getListConnectedUsers(User *client){

	client->writeCommand(LIST_CONNECTED_USERS);
	client->writeCommand(usersMap.size());

	map<string,User*>::iterator iter ;

	string name;
	int count = 0;
	for (iter = usersMap.begin() ; iter != usersMap.end();iter++)
	{
		name = iter->first;
		client->writeMsg( name);
		count++;
	}

	return count;
}
void TcpServerMessenger::getListSessions(){
	cout<<"All the connected users that in Session:"<<endl;
	std::map<string,User*>::iterator iter;

	string name;
	for (iter = usersMap.begin() ; iter != usersMap.end();iter++)
	{
		if(iter->second->inSession())
		{
			name = iter->first;
			printToSreen(name);
		}
	}
}
void TcpServerMessenger::getListRooms(){

	cout<<"the rooms list:"<<endl;
	this->readfromChatRoom(NULL);

}
void TcpServerMessenger::getListRooms(User *client){
	client->writeCommand(LIST_ROOMS);
	client->writeCommand((int) chatRoomsMap.size());

	this->readfromChatRoom(client);
}
int TcpServerMessenger::getListChatUsers(string ChatRoomName){
	cout<<"Users list in Room:"<<endl;
		int numOfUsers = 0;
		bool checker=false;
		for (map<string,cRoom*>::iterator iter = chatRoomsMap.begin(); iter !=  chatRoomsMap.end();iter++)
		{
			if (ChatRoomName == iter->first){
				checker=true;
				iter->second->printUsers();
				numOfUsers++;
			}
		}
	if (checker==false)
		cout<<"The room:"<<ChatRoomName<<" not found"<<endl;

		return numOfUsers;
}
int TcpServerMessenger::getListChatUsers(User *client){
	int numOfUsers = 0;
	string ChatRoomName = client->readMsg();
	for (map<string,cRoom*>::iterator iter = chatRoomsMap.begin(); iter !=  chatRoomsMap.end();iter++)
	{
		if (ChatRoomName == iter->first)
		{
			client->writeCommand(LIST_CONNECTED_USERS_IN_ROOM);
			(iter)->second->sendUserList(client);
			break;
		}
	}
	return numOfUsers;
}
void TcpServerMessenger::getListUsers(User *client){
	int numOfusers = 0;
	numOfusers = numOfUsersFromFile();

	client->writeCommand(LIST_USERS);
	client->writeCommand(numOfusers -1);

	//cout << "the users:"<< endl;
	if (client != NULL)
		readFromFile(client);
	else
		readFromFile(NULL);

}
void TcpServerMessenger::getListUsers(){
	cout << "the users:"<< endl;
	readFromFile(NULL);
}
void TcpServerMessenger::exitServer(User* clientName){
	clientName->closeSession(true);
	clientName->disconnectFromChatRom(false);

	cout<<"the Client  : "<< clientName->getusername() << " was  disconnect" <<endl;

	pthread_mutex_lock(&users_mutx);
    deleteChatRoom(clientName);///////////
	usersMap.erase(clientName->getusername());
	pthread_mutex_unlock(&users_mutx);
}
void TcpServerMessenger::createSession(User* fromUser, User* toUser) {
	// login the two users
	toUser->loginUsertoSession(fromUser);
	fromUser->loginUsertoSession(toUser);

	// send communication details
	toUser->writeCommand(SESSION_ESTABLISHED);
	toUser->writeMsg(fromUser->getusername());
	toUser->writeMsg(fromUser->getIP());
	toUser->writeCommand(fromUser->getport());
	toUser->writeCommand(toUser->getport());

	fromUser->writeCommand(SESSION_ESTABLISHED);
	fromUser->writeMsg(toUser->getusername());
	fromUser->writeMsg(toUser->getIP());
	fromUser->writeCommand(toUser->getport());
	fromUser->writeCommand(fromUser->getport());

}
void TcpServerMessenger::createChatRoom(User* creator){
	string msg;
	bool exist = false;
	msg = creator->readMsg();

	// Checking that the name does not exist

	pthread_mutex_lock(&chatroom_mutx);
	for (map<string,cRoom*>::iterator iter = chatRoomsMap.begin(); iter !=  chatRoomsMap.end();iter++)
	{
		if (iter->first == msg)
		{
			pthread_mutex_unlock(&chatroom_mutx);
			exist = true;
		}
	}
	pthread_mutex_unlock(&chatroom_mutx);


	if (exist)
	{
		creator->writeCommand(CHAT_ROOM_CREATE_DENIED);
		creator->writeMsg(string("Chat Room name already exists"));
		return;
	}

	//Add new caht room
	pthread_mutex_lock(&chatroom_mutx);
	chatRoomsMap[msg] = new cRoom(creator, msg);
	pthread_mutex_unlock(&chatroom_mutx);
	creator->writeCommand(CHAT_ROOM_CREATED);
    activeRoom=true;
	cout << "Room : "<< msg <<" was created" << endl;
}
void TcpServerMessenger::deleteChatRoom(User* creator){
	string msg;
	msg = creator->readMsg();

	bool exist = false;

	pthread_mutex_lock(&chatroom_mutx);
	for (map<string,cRoom*>::iterator iter = chatRoomsMap.begin(); iter !=  chatRoomsMap.end();iter++)

	{
		if (iter->first == msg)
		{
			pthread_mutex_unlock(&chatroom_mutx);
			exist = true;
		}
	}
	pthread_mutex_unlock(&chatroom_mutx);


	if(!exist){
		return;
	}

	pthread_mutex_lock(&chatroom_mutx);
	if(chatRoomsMap[msg]->getOwner()->getusername() == creator->getusername())
	{
        cout<<"The room:"<<creator->getChatRoom()->getChatRoomName()<<" was closed!\n";
		delete(chatRoomsMap[msg]);
		creator->writeCommand(CHAT_ROOM_CLOSED);
		chatRoomsMap.erase(msg);

	}
	else
	{
		creator->writeCommand(CHAT_ROOM_UNCLOSED);
	}
	pthread_mutex_unlock(&chatroom_mutx);


}
void TcpServerMessenger::loginChatRoom(User* loginUser){
	string roomname = loginUser->readMsg();
	bool exist = false;
	pthread_mutex_lock(&chatroom_mutx);
	for (map<string,cRoom*>::iterator iter = chatRoomsMap.begin(); iter !=  chatRoomsMap.end();iter++)
	{
		if (iter->first == roomname)
		{
			pthread_mutex_unlock(&chatroom_mutx);
			exist = true;
		}
	}
	pthread_mutex_unlock(&chatroom_mutx);


	if (!exist)
	{
		loginUser->writeCommand(CHAT_ROOM_LOGED_IN_DENIED);
		loginUser->writeMsg(string("Room does not exist"));
		return;
	}

	loginUser->loginUserToChatRoom(chatRoomsMap[roomname]);
	if (chatRoomsMap[roomname]->addUser(loginUser))
	{
		loginUser->writeCommand(CHAT_ROOM_LOGED_IN);
		loginUser->writeCommand(loginUser->getport());
	}
	else
	{
		loginUser->writeCommand(CHAT_ROOM_LOGED_IN_DENIED);
		loginUser->writeMsg(string("you are already logged in"));
	}


}
int TcpServerMessenger::numOfUsersFromFile(){
	string line;
	fstream loginFile;
	string userFromFile;
	int counter = 0;

		loginFile.open(userList,ios::in|ios::out|ios::binary);

	    while ( !loginFile.eof() )
	    {
	      getline (loginFile,line);
	      counter++;

	    }
	    loginFile.close();
	 return counter;
}
void TcpServerMessenger::readFromFile(User *clientName){
	string line;
		fstream loginFile;
		string userFromFile;
		loginFile.open(userList,ios::in|ios::out|ios::binary);
		if (loginFile.is_open()){

			while (!loginFile.eof() )
			{
			  getline (loginFile,line);
			  istringstream liness( line );
			  getline( liness, userFromFile, '-' );
			  if (clientName != NULL)
			  {
				  clientName->writeMsg(userFromFile);
				  //printToSreen(userFromFile);

			  }
			  else
			  {
				  printToSreen(userFromFile);
			  }

			}
			loginFile.close();
		}
		else
		{
			 printToSreen("Error - could not open the file");
		}

}
void TcpServerMessenger::printToSreen(string msgToScreen){
    cout << msgToScreen << endl;
}
void TcpServerMessenger::readfromChatRoom(User *clientName){
	string name;
	pthread_mutex_lock(&chatroom_mutx);
		for (map<string,cRoom*>::iterator iter = chatRoomsMap.begin(); iter !=  chatRoomsMap.end();iter++)
		{
			name = iter->first;
			if (clientName != NULL)
			{
			clientName->writeMsg(name);
			}
			else
			{
				printToSreen(name);
			}

		}
    if (activeRoom==false)
    {
        if (clientName != NULL)
         clientName->writeMsg("  No rooms!");

    }
		pthread_mutex_unlock(&chatroom_mutx);
}
TcpServerMessenger::~TcpServerMessenger() {
	running = false;
	waitForThread();
}
