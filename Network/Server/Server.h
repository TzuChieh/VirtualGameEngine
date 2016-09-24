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
		void LisConnection();

	private:	
		bool wsaSetup();
		void connectionHandler(SOCKET,SOCKADDR_IN,int);
		bool getSize(int,int&);
		bool sendSize(int,int);
//		bool getType(int,Packet&);
//		bool sendType(int,Packet);

//		void check();
//		bool processPacket(int, Packet);
	
		static void callThread(Server*, int);
		void serverThread(int);

	private:
		int m_totalUsers ;
		SOCKADDR_IN m_addr;     // Server Address of our listening socket 
		SOCKET m_listenSocket;  
		SOCKET m_users[MAX_USERS];
		bool m_clientState[MAX_USERS];
		std::thread m_clientManager[MAX_USERS]; 

};

}
