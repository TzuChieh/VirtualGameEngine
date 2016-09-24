#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <thread>
#include <vector>
#include <string>


namespace ve {

static const int MAX_USERS = 100 ;

class Server 
{
	public:
		Server(int); // port number 
		~Server();
		
		bool LisConnection();
	
	private:
		int m_totalUsers ;
		SOCKET m_users[MAX_USERS];
		SOCKET m_listenSocket;  
		SOCKADDR_IN m_addr;     // Server Address of our listening socket 
		std::vector<bool> m_clientState;
		std::vector<std::thread> m_clientManager; 
		
		
		void check();
		bool wsaSetup();
		void connectionHandler(SOCKET,SOCKADDR_IN,int);
//		bool getSize(int,int&);
//		bool sendSize(int,int);
//		bool getType(int,Packet&);
//		bool sendType(int,Packet);
//		bool sendString(int,string&);
//		bool getString(int,string&);
	
//		bool processPacket(int, Packet);
	
		static void callThread(Server*, int);
		void serverThread(int);
	

};

// use for passing param to thread 
struct p_list {    
	Server* s_ptr;
	int id;
};

}
