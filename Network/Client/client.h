//client.h
//2016.7.12

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 

#ifndef VE_NETWORK
#define VE_NETWORK
typedef int  Type;
typedef char Byte;
#endif

#include <Winsock2.h>
#include <thread>
#include <string>

namespace ve 
{
	
class Client
{
	public:

		Client(std::string,int); //IP adress & port number
		~Client();
		
		bool cntToServer(); //connect to server
		bool disConnect();
		
		bool sendData(int, int, Byte*);
		bool getData(int&, int&, Byte*);
	
	
	private:
		bool wsaSetup();
		bool getSize(int&);
		bool sendSize(int);
		bool getType(int&);
		bool sendType(int);
		
		static void callThread(void*);
		void clientThread();	             				

	private: 
		SOCKET m_connection;
		SOCKADDR_IN m_addr;
		std::thread m_sender;
		bool m_connectionState;
};

}//end of xe 
 
