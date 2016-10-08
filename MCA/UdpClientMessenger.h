
#ifndef CLIENTLINKER_H_
#define CLIENTLINKER_H_

#include "../SocketUtils/MThread.h"
#include "../SocketUtils/UDPSocket.h"
namespace  npl{
class UdpClientMessenger: public MThread {
	UDPSocket clientSocket;
	bool running;
public:
	void send(string msg,string IP, int port);
	UdpClientMessenger(int port);
	void run();
	virtual ~UdpClientMessenger();
};
}
#endif /* CLIENTLINKER_H_ */
