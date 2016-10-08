
#include <unistd.h>
#include "TCPSocketTest.h"

using namespace npl;
using namespace std;

void TCPSocketTest::run()
{
	TCPSocket* serverSocket=new TCPSocket(5555);
	TCPSocket* clientSocket= serverSocket->listenAndAccept();
	this->len=clientSocket->recv(Buffer,255);
	Buffer[len]='\0';
	clientSocket->send(Buffer,len);
	clientSocket->cclose();
	serverSocket->cclose();
	delete clientSocket;
	delete serverSocket;
}

int TCPSocketTest:: test(){
	start();
	sleep(1);
	TCPSocket* clientSocket= new TCPSocket("127.0.0.1",5555);
	this->MSG="TCP Test: Message 1";
	clientSocket->send(MSG,19);
	Buffer[clientSocket->recv(Buffer, 255)]='\0';
	clientSocket->cclose();
	delete clientSocket;

	if(strcmp(Buffer, MSG)==0)
	{
			cout<<"Message was sent successfully"<<endl;
			return 1;
	}

	else
	{
		cout<<"ERROR#1: The message that was sent is different than the message that was received";
	}
	waitForThread();
	return -1;


}
