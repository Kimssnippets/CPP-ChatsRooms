

#ifndef UDPSOCKETTEST_H_
#define UDPSOCKETTEST_H_
#include <string.h>
#include <array>
#include <iostream>
#include "UDPSocketTest.h"
#include "../SocketUtils/UDPSocket.h"
namespace  npl{
using namespace std;

class UDPSocketTest {
	char Buffer[255];
	string MSG;
	string ip;
	int rc;
public:
	int test();

};

}

#endif /* UDPSOCKETTEST_H_ */
