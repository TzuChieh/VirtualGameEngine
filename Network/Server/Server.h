#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <string>

using namespace std;

namespace xe {

static const int MAX_USERS = 100 ;

enum Packet
{
	p_info,  //inforamtion
	p_test   //test
};


class Server {
	public:
		Server(int);
		~Server();
		
		bool LisConnection();
	
	private:
		int totalUsers ;
		SOCKET users[MAX_USERS];
		SOCKADDR_IN addr; //Address that we will bind our listening socket to
		SOCKET sListen;
		
		void initialize();
		bool getSize(int,int&);
		bool sendSize(int,int);
		bool getType(int,Packet&);
		bool sendType(int,Packet);
		bool sendString(int,string&);
		bool getString(int,string&);
	
		bool processPacket(int, Packet);
	
		static void callThread(void*);
		void serverThread(int);
	

};

// use for passing param to thread 
struct p_list {    
	Server* s_ptr;
	int id;
};

}
