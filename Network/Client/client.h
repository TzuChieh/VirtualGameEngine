//client.h
//2016.7.12

#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 

//use window socket
#include <Winsock2.h>
//standard lib
#include <string>

using namespace std;

namespace xe {

enum Packet
{
	p_info,  //inforamtion
	p_test   //test
};

class Client{
	public:

		Client(string,int); //IP adress & port number
		~Client();
		
		bool cntToServer(); //connect to server
		bool disConnect();
		
		bool sendString(string&);
		             				
	private: 
		SOCKET connection;
		SOCKADDR_IN addr;
		
		//helper fnt
		
		bool getSize(int&);
		bool sendSize(int);
		bool getType(Packet&);
		bool sendType(Packet);

		bool getString(string&);
		
		void initialize(); // initialize winsocl api 
		bool processPacket(Packet);
		static void callThread(void*);
		void clientThread();
		
	
};

}//end of xe 
 
