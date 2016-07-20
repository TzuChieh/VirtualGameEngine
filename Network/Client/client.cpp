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
		if(!getType(packettype)) {
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
	if(send(connection,(char*)&size,sizeof(int),0) == SOCKET_ERROR) { //check data tranfer
		return false;
	}
	return true;
}

bool Client::getSize(int &size) {
	if(recv(connection, (char*)&size,sizeof(int),0) == SOCKET_ERROR) { //check data tranfer
		return false;
	}
	return true;
}

bool Client::sendType(Packet packetType) {
	if(send(connection,(char*)&packetType,sizeof(Packet),0) == SOCKET_ERROR) { //check data tranfer
		return false;
	}
	return true;
}

bool  Client::getType(Packet &packetType) {
	if(recv(connection,(char*)&packetType,sizeof(Packet),0) == SOCKET_ERROR) { //check data tranfer
		return false;
	}
	return true;
}

bool Client::sendString(string &s) {
	if (!sendType(p_info)){
		return false;
	}
	int length = s.length();
	if(!sendSize(length)){
		return false;
	}
	if(send(connection, s.c_str(),length,0) ==SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool Client::getString(string &s) {
	int length;
	if(!getSize(length)){
		return false;
	}
	char* buffer = new char [length+1]; //with '\0'
	int retnCheck = recv(connection, buffer, length, 0);
	s = buffer; //char array to string
	delete[] buffer;
	if (retnCheck == SOCKET_ERROR) //If connection is lost while getting message
		return false; 
	return true;
}

bool Client::processPacket(Packet packetType) {
	switch(packetType) {
		case p_info:{
			//TBC
			break;
		}
		case p_test:{
			//TBC
			break;
		}
		default:
			break;
	}
}


