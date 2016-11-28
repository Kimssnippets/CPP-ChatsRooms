#ifndef LOGIN_H_
#define LOGIN_H_

#include <map>
#include <string>
#include "TcpServerMessenger.h"
#include "../SocketUtils/TCPMessengerProtocol.h"
#include "../SocketUtils/TCPMessengerProtocol.h"
/*
 * The dispatcher is in charge of the work with the user list database and to receive new connections
 *
 * the mutex lock is protected on a shareable variable inside a critical section
 * The behavior of the mutex is to lock the way to sone value until one process finish and this process is the one that unlock the mutex
*/
using namespace std;
namespace  npl {
	class LoginDispatcher : public MThread {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Please note you have to change this path respectively to your project direction! otherwise users cannot register OR login*/
		string userList = "/Users/admin/ClionProjects/-CPlusPlus-NetworkProgramingLab/MSA/userList.txt";//file of the userlist (path)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		map<string, TCPSocket *> peers;//map of sockets that can match between the userName to his currently active TCP socket
		bool running;
		MultipleTCPSocketsListener *listener;
		pthread_mutex_t peers_mutx;
		TcpServerMessenger *_serverManager;
		bool login(string userName, string password);
		bool signUp(string userName, string password);

	public:
		LoginDispatcher(TcpServerMessenger *_serverManager);
		void run();
		void addPeer(TCPSocket *peer);
		virtual ~LoginDispatcher();
	};
	class Connection : public MThread {
		LoginDispatcher *registration;
		TCPSocket *clientSocket;
		bool running;

	public:

		Connection(LoginDispatcher *registration);
		void run();
		virtual ~Connection();
	};
}
#endif /* LOGIN_H_ */
