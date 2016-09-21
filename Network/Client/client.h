//client.h
//2016.7.12

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 

#ifndef Type
typedef int Type;
#endif

#ifndef Byte
typedef int Byte;
#endif

#include <Winsock2.h>
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
		SOCKET connection;
		SOCKADDR_IN addr;
		
		//helper fnt
		
		bool getSize(int&);
		bool sendSize(int);
		bool getType(int&);
		bool sendType(int);
		
		static void callThread(void*);
		void clientThread();
	
};

}//end of xe 
 
