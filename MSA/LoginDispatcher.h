#ifndef LOGIN_H_
#define LOGIN_H_

#include <map>
#include <string>
#include "TcpServerMessenger.h"
#include "../SocketUtils/TCPMessengerProtocol.h"
#include "../SocketUtils/TCPMessengerProtocol.h"

using namespace std;
namespace  npl {
	class LoginDispatcher : public MThread {
		
		string userList = "/Users/admin/ClionProjects/-CPlusPlus-NetworkProgramingLab/MSA/userList.txt";
		map<string, TCPSocket *> peers;//
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
