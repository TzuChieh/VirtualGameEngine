//client.h
//2016.7.12

#pragma once

//for Visual Sudio
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 


#include "Common/type.h"
//use window socket
#include <Winsock2.h>
//standard lib
#include <string>

using namespace std;

namespace xe {

enum Packet
{
	P_ChatMessage,
	P_Test
};

class Client{
	public:

		Client(string,int32); //IP adress & port number
		~Client();
		
		bool cntToServer(); //connect to server
		bool disConnect();
		
		bool sendString(string&);
		             				
	private: 
		SOCKET connection;
		SOCKADDR_IN addr;
		
		//helper fnt
		
		bool getSize(int32);
		bool sendSize(int32);
		bool getType(Packet);
		bool sendType(Packet);

		bool getString(string);
		
		void initialize(); // initialize winsocl api 
		bool processPacket(Packet);
		static void callThread(void*);
		void clientThread();
		
	
};

}//end of xe 
 
