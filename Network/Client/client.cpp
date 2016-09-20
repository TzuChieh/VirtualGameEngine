#include "sender.h"
#include <iostream>
#include <thread>
using namespace xe;

Client::Client(std::string ip,int port)
{
	WSAData wsaData;
	WORD version = MAKEWORD(2,2); // verion 2.2
	if( WSAStartup(version, &wsaData) != 0) 
	{
		std::cerr << "Winsock startup failed !" << std::endl ;
		exit(1);
	}
	addr.sin_addr.s_addr = inet_addr(ip.c_str()); // ip convert to char*
	addr.sin_port = htons(port); // port
	addr.sin_family = AF_INET ;  // IPv4
}

Client::~Client()
{
	//TBC
}

bool Client::cntToServer()
{
	this->connection = socket(AF_INET, SOCK_STREAM, 0); // IPv4
	if( connect(connection,(SOCKADDR*)&addr,sizeof(addr))) 
	{  
		std::cerr << "Fail to connect to server!" << std::endl;
		return false;
	}
	
	std::cout << "Connected!" << std::endl;
	std::thread sender(callThread, static_cast<void*>(this)); 
	return true;
}

bool Client::disConnect() 
{
	
	if(closesocket(this->connection) == SOCKET_ERROR && WSAGetLastError() != WSAENOTSOCK) {
		// can not close the socket and the error is not socket have closed.
		std::cerr << "Failed to close the socket. Winsock Error: " << WSAGetLastError()  << std::endl;
		return false;
	}
	return true;
}

void Client::callThread(void* param) 
{
	Client* myclient = static_cast<Client*>(param);
	myclient->clientThread();
}

void Client::clientThread()
{
	//do stuff 
}

bool Client::sendSize(int size) {
	if(send(connection,(char*)&size,sizeof(int),0) == SOCKET_ERROR)
	{ 
		return false;
	}
	return true;
}

bool Client::getSize(int &size) {
	if(recv(connection, (char*)&size,sizeof(int),0) == SOCKET_ERROR) 
	{ 
		return false;
	}
	return true;
}

bool Client::sendType(Type classType) 
{
	if(send(connection,(char*)&classType,sizeof(Type),0) == SOCKET_ERROR) { 
		return false;
	}
	return true;
}

bool  Client::getType(Type &classType) {
	if(recv(connection,(char*)&classType,sizeof(Type),0) == SOCKET_ERROR) { 
		return false;
	}
	return true;
}

bool Client::sendData(Type classType,int size,Byte* bytes)
{
	if(!sendType(classType))
	{
		return false;
	}
	if(!sendSize(size))
	{
		return false;
	}
	if(send(connection,(char*)bytes,size,0) == SOCKET_ERROR) {
		return false;
	}
	return true;
}


