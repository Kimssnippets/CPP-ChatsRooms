#include "LoginDispatcher.h"
#include "TcpServerMessenger.h"
using namespace npl;
void printInstructions()
{
	cout<<"----------------------------------------------"<<endl;
	cout<<"To list users: lu"<<endl;
	cout<<"To list connected users: lcu"<<endl;
    cout<<"To list Users in Room: lru <roomname>"<<endl;
    cout<<"To list sessions: ls"<<endl;
	cout<<"To list Rooms: lr"<<endl;
	cout<<"To exit type: x"<<endl;
	cout<<"----------------------------------------------"<<endl;
}

int main()
{
	cout<<"welcome to the TCP server"<<endl;
	printInstructions();

	TcpServerMessenger serverManager;
	LoginDispatcher registration(&serverManager);
	Connection connection(&registration);

	bool loop = true;
	while(loop)
	{
		string chatroom;
		string msg;
		string command;
		cin >> command;

		if(command == string("lcu"))
		{
			serverManager.getListConnectedUsers();
		}

		else if(command == string("ls"))
		{
			serverManager.getListSessions();
		}

		else if(command == string("lu"))
		{
			serverManager.getListUsers();
		}

		else if(command==string("lr"))
		{
			serverManager.getListRooms();
		}

		else if(command == string("lru"))
		{
			cin>>chatroom;
			serverManager.getListChatUsers(chatroom);
		}

		else if(command == string("x"))
		{
			cout<<"SHUTDOWN ALL..."<<endl;

			loop = false;
		}

		else
		{
			cout<<"UNKNOWN command"<<endl;
			printInstructions();
		}
	}

	cout<<"messenger was closed"<<endl;
	return 0;
}
