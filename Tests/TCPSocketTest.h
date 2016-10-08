
#ifndef TCPSOCKETTEST_H_
#define TCPSOCKETTEST_H_
#include <string.h>
#include "../SocketUtils/MThread.h"
#include "../SocketUtils/TCPSocket.h"


namespace  npl{
class TCPSocketTest: public MThread {
	char Buffer[255];
	char* MSG;
	int len;
public:
	void run();
	int test();








};
}


#endif /* TCPSOCKETTEST_H_ */
