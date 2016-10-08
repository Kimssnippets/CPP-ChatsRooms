#ifndef MESSENGERTEST_H_
#define MESSENGERTEST_H_
#include "../SocketUtils/TCPSocket.h"
#include "../MSA/TcpServerMessenger.h"
#include "../MCA/TcpCLientMessenger.h"

namespace npl{

class MessengerTest {
	TcpCLientMessenger* client1;
	TcpCLientMessenger* client2;
	TcpCLientMessenger* client3;
	TcpCLientMessenger* client4;
	TcpServerMessenger* server;




public:
	MessengerTest();
	void test();
	void connectionTest(TcpCLientMessenger client);
	void loginTest(TcpCLientMessenger client,string Name,string Pass);
	void registerTest(TcpCLientMessenger client,string Name,string Pass);

};


 }


#endif /* MESSENGERTEST_H_ */
