
#include "UDPSocketTest.h"


using  namespace npl;

int UDPSocketTest::test()
{
	UDPSocket* socket1 = new UDPSocket(3333);
	UDPSocket* socket2=new UDPSocket(4444);
	this->ip="127.0.0.1";
	this->MSG="UDP Send Test: MSG1";
	socket1->sendTo(MSG,ip,4444);
	memset((void*)Buffer,0,255);
	this->rc=socket2->read(Buffer,255);
	cout<< "Message Received: "<<Buffer<<endl;
	if(MSG != Buffer)
	{
		cout<<"ERROR#1: The message that was sent is different than the message that was received";
		return -1;
	}
	else
	{
		cout<<"the message was sent successfully"<<endl;
	}

	this->MSG="UDP Replay Test: MSG2";
	socket2->reply(MSG);
	cout<< "Message Sent: "<<MSG<<endl;
	memset((void*)Buffer,0,255);
	rc = socket1->read(Buffer, 255);
	cout<< "Message Received: "<<Buffer<<endl;

	if(MSG != Buffer)
	{
		cout<<"ERROR#1: The message that was sent is different than the message that was received";
		return -1;
	}
	else
	{
		cout<<"The message was replayed successfully"<<endl;
	}

	socket1->cclose();
	socket2->cclose();
	delete socket1;
	delete socket2;
	return true;

}




 /* namespace std */
