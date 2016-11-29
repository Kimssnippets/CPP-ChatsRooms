#include "UdpClientMessenger.h"
using namespace npl;
UdpClientMessenger::UdpClientMessenger(int port):clientSocket(port) {
	start();
}
void UdpClientMessenger::run(){
	running = true;
	char buf[300];
	while(running)
	{
		for(int i = 0;i<300;i++,buf[i] = 0);
		clientSocket.recv(buf,300);
		cout<<buf<<endl;
	}
}
void UdpClientMessenger::send(string msg,string IP, int port){
	clientSocket.sendTo(msg,IP,port);
}
UdpClientMessenger::~UdpClientMessenger() {
	running = false;
	clientSocket.cclose();
	waitForThread();
}
