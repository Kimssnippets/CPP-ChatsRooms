

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include <netinet/in.h>
#include <inttypes.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>

using namespace std;
namespace npl {
	class UDPSocket {
	private:
		struct sockaddr_in s_in;
		struct sockaddr_in from;
		unsigned int fsize;
		int socket_fd;

	public:
		UDPSocket(int port = 9999);

		int recv(char *buffer, int length);

		int sendTo(string msg, string ip, int port);

		int reply(string msg);

		void cclose();

		int read(char *buffer, int length);

		int write(char *buffer, int length);

		string fromAddr();
	};
}
#endif /* UDPSOCKET_H_ */
