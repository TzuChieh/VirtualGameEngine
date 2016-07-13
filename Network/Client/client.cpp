//client.cpp
//2016.7.12
//for Visual Sudio
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 


//use window socket
#include <Winsock2.h>
#include <string>
#include <iostream> 
#include "client.h"

using namespace std;
using namespace xe;

void Client::initialize() {
	//initiailized windows socket dll
	WSAData wsaData;
	WORD version = MAKEWORD(2,2); // verion 2.2
	if( WSAStartup(version, &wsaData) != 0) {
		cerr << "Winsock startup failed !" << endl ;
		exit(1);
	}
}

Client::Client(string ip,int port) {
	initialize();
	addr.sin_addr.s_addr = inet_addr(ip.c_str()); // ip convert to char*
	addr.sin_port = htons(port); // port
	addr.sin_family = AF_INET ;  // IPv4
}

Client::~Client() {
	//shoult check whether the thread is stil running
	//TBC
}

bool Client::cntToServer() {
	this->connection = socket(AF_INET, SOCK_STREAM, 0); // IPv4
	if( connect(connection,(SOCKADDR*)&addr,sizeof(addr))) {  
		cerr << "Fail to connect to server!" << endl;
		return false;
	}
	
	cout << "Connected!" << endl;
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)callThread,static_cast<void*>(this),0,0);
	return true;
}

bool Client::disConnect() {
	
	if(closesocket(this->connection) == SOCKET_ERROR && WSAGetLastError() != WSAENOTSOCK) {
		// can not close the socket and the error is not socket have closed.
		cerr << "Failed to close the socket. Winsock Error: " << WSAGetLastError()  << endl ;
		return false;
	}
	return true;
}

void Client::callThread(void* param) {
	Client* myclient = static_cast<Client*>(param);
	myclient->clientThread();
}

void Client::clientThread() {
	Packet packettype;
	while(true) {
		if(!getPacketType(packettype)) {
			break;
		}		
		if(!processPacket(packettype)) {
			break;				
		}
	}
	
	cout << "Lost connection to the server." << std::endl;
	closesocket(this->connection);
}

bool Client::sendSize(int size) {
	//TBC
}

bool Client::getSize(int &size) {
	//TBC
}

bool Client::sendString(string s) {
	//TBC
}

bool Client::getString(string &s) {
	//TBC
}

bool Client::processPacket(Packet packetType) {
	//TBC
}


