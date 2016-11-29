#include "LoginDispatcher.h"
using namespace npl;


LoginDispatcher::LoginDispatcher(TcpServerMessenger* serverManager)
{
	listener = NULL;//MultipleTCPSocketsListener object->need to initialize after initialize the server local variable
	_serverManager = serverManager;
	pthread_mutex_init(&peers_mutx,NULL);//initialize mutex variable->NULL beacuse we dont need special properties for are mutex,
	running = true;
	start();//Start the thread->GO to the run() function bellow
	cout<<"LoginAndSignUP is on"<<endl;

}

void LoginDispatcher::run(){
	TCPSocket* socktotalk = NULL;
	int commandreceved = 0;
	string username;
	string password;
	while(running)
	{
		delete (listener);
		listener = new MultipleTCPSocketsListener();
		pthread_mutex_lock(&peers_mutx);
		listener->addSockets1(peers);
		pthread_mutex_unlock(&peers_mutx);

		socktotalk = listener->listenToSocket(2);
		if (!socktotalk)
			continue;

		commandreceved = socktotalk->readCommand();
		switch  (commandreceved)
		{
		case LOGIN_REQUEST:
			username =  socktotalk->readMsg();
			password =  socktotalk->readMsg();
			if(login(username, password))
			{
				_serverManager->addUser(socktotalk, username);
				pthread_mutex_lock(&peers_mutx);
				peers.erase(socktotalk->destIpAndPort());
				pthread_mutex_unlock(&peers_mutx);
				socktotalk->writeCommand(LOGIN_REQUEST_APPROVED);
			}
			else
				socktotalk->writeCommand(LOGIN_REQUEST_DENIED);
			break;
		case SIGNUP_REQUEST:
			username =  socktotalk->readMsg();
			password =  socktotalk->readMsg();
			if (signUp(username,password))
				socktotalk->writeCommand(SIGNUP_REQUEST_APPROVED);
			else
				socktotalk->writeCommand(SIGNUP_REQUEST_DENIED);
			break;
		}
	}
}
void LoginDispatcher::addPeer(TCPSocket* peer){
	pthread_mutex_lock(&peers_mutx);
	peers[peer->destIpAndPort()] = peer;
	pthread_mutex_unlock(&peers_mutx);
}
LoginDispatcher::~LoginDispatcher(){
	running = false;

	for (map<string,TCPSocket*>::iterator iter = peers.begin(); iter != peers.end(); iter++)
	{
		iter->second->cclose();
	}
	waitForThread();
}
bool LoginDispatcher::login(string userName,string password){
	string line;
	fstream loginFile;
	loginFile.open(userList,ios::in|ios::out|ios::binary);

	if(loginFile.is_open()){
		while ( !loginFile.eof() )
		{
		  getline (loginFile,line);
		  if (line == userName+string("-") +password)
			  return true;
		}
		loginFile.close();
   }
   else
   {
	   cout <<"Error - could not open file!" << endl;
   }
		return false;
}
bool LoginDispatcher::signUp(string userName,string password){
	string line;
	string userFromFile;
	fstream loginFile;
	loginFile.open(userList,ios::in|ios::out|ios::binary);

	if (!loginFile.is_open()){
		   cout <<"Error - could not open file!" << endl;
		return false;
	}

	while ( !loginFile.eof() )
	{
		getline (loginFile,line);
		istringstream liness( line );
		getline( liness, userFromFile, '-' );

		if (userFromFile == userName)
		{
			cout <<"Error - This user name is already exist!" << endl;
		    loginFile.close();
			return false;
		}
	}
	cout <<"New user:" <<userName<< endl;
	loginFile.close();

	ofstream loginFile1;
	loginFile1.open(userList,ios::app);
	loginFile1<<userName+string("-")+password<<endl;
    loginFile1.close();
	return true;
}
Connection::Connection(LoginDispatcher* registration) {

	this->registration = registration;
	running = true;
	clientSocket = new TCPSocket(MSNGR_PORT);
	start();
	cout<<"server connection is up!"<<endl;

}
void Connection::run(){
	TCPSocket* temp;
	while (running)
	{
		temp = clientSocket->listenAndAccept();
		if(!temp)
			break;
		registration->addPeer(temp);
		cout<<"new peer has connected"<<endl;
	}
	cout<<"the connection with server has stopped"<<endl;
}
Connection::~Connection() {
	running = false;
	clientSocket->cclose();
	waitForThread();
}

