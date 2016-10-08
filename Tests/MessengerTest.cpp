


#include "MessengerTest.h"
#include "../MSA/LoginDispatcher.h"

using namespace npl;
MessengerTest::MessengerTest()
{
	//this->server=new TcpServerMessenger();
	//sleep(2);
	//this->client1=new ClientManager();
	//this->client2=new ClientManager();
	//this->client3=new ClientManager();
	//this->client4=new ClientManager();

}


void MessengerTest::test()
{
	TcpServerMessenger server;
	LoginDispatcher reg(&server);
	Connection con(&reg);
	sleep(2);
	TcpCLientMessenger client1;
	TcpCLientMessenger client2;
	TcpCLientMessenger client3;
	TcpCLientMessenger client4;



	//Checking Connect command
	client1.connectToServer("127.0.0.1",MSNGR_PORT);	sleep(2);
	client2.connectToServer("127.0.0.1",MSNGR_PORT);	sleep(2);
	client3.connectToServer("127.0.0.1",MSNGR_PORT);	sleep(2);
	client4.connectToServer("127.0.0.1",MSNGR_PORT);	sleep(2);
	//Checking Register command for 4 users

	client1.sign("Israel","1234",SIGNUP_REQUEST);sleep(2);
	client2.sign("Guy","1234",SIGNUP_REQUEST);sleep(2);
	client3.sign("Maya","1234",SIGNUP_REQUEST);sleep(2);
	client4.sign("Mery","1234",SIGNUP_REQUEST);sleep(2);

	//Checking LoginDispatcher command for 3 uers

	client1.log("Israel","1234",LOGIN_REQUEST);sleep(2);
	client2.log("Guy","1234",LOGIN_REQUEST);sleep(2);
	client3.log("Maya","1234",LOGIN_REQUEST);sleep(2);
	//Checking lu and lcu commands
	client1.listUsers();sleep(2);
	client1.prinCtonnectedUsers();sleep(2);

	//Checking O command (client1 with client2)

	client1.openSession("Guy");
	cout<<"Israel opened session with Guy"<<endl;
	sleep(2);
	//Checking creating room command
	client3.createChatRoom("Room1");
	cout<<"Maya opened Room1"<<endl;
	sleep(2);
	//Checking enter to a room command
	client2.loginToChatRoom("Room1");
	cout<<"Guy entered Room1"<<endl;
	sleep(2);
	//Checking lr and lru commands
	cout<<"Room List:"<<endl;

	client3.RoomsList();
	sleep(2);
	client3.listConnectedUsersInRoom("Room1");
	sleep(2);
	//Checking exit chatRoom/Session
	client2.exitRoomOrCloseSession();
	sleep(2);
	//Checking l command - Status for each user
	client1.printCurrentInfo();
	sleep(2);
	client2.printCurrentInfo();
	sleep(2);
	client3.printCurrentInfo();
	sleep(2);
	client4.printCurrentInfo();
	sleep(2);

	//Checking X command
	client1.exitAll();
	client2.exitAll();
	client3.exitAll();
	client4.exitAll();

}

void MessengerTest::connectionTest(TcpCLientMessenger client) {

}

void MessengerTest::loginTest(TcpCLientMessenger client, string Name, string Pass) {

}

void MessengerTest::registerTest(TcpCLientMessenger client, string Name, string Pass) {

}




