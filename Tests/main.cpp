#include "UDPSocketTest.h"
#include "TCPSocketTest.h"
#include "MessengerTest.h"
using namespace npl;
int main()
{
	int test1=0,test2=0;
	MessengerTest* MesTest;
	UDPSocketTest UDPTest;
	TCPSocketTest TCPTest;
	MesTest=new MessengerTest();
	test1=UDPTest.test();
	test2=TCPTest.test();

	if(test1==1)
	{
		cout<<"UDP test was successful!"<<endl;
	}
	else
	{
		cout<<"UDP test failed!"<<endl;
	}

	if(test2==1)
	{
		cout<<"TCP test was successful!"<<endl;
	}
	else
	{
		cout<<"TCP test failed!"<<endl;
	}

	sleep(2);

	MesTest->test();

















}
