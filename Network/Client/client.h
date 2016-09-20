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

namespace xe 
{
	
class Client
{
	public:

		Client(std::string,int); //IP adress & port number
		~Client();
		
		bool cntToServer(); //connect to server
		bool disConnect();
		
		bool sendString(std::string&);
		             				
	private: 
		SOCKET connection;
		SOCKADDR_IN addr;
		
		//helper fnt
		
		bool getSize(int&);
		bool sendSize(int);
		bool getType(Type&);
		bool sendType(Type);
		bool getData(Byte*);
		bool sendData(Type,int,Byte*);
		
	
		static void callThread(void*);
		void clientThread();
	
};

}//end of xe 
 
