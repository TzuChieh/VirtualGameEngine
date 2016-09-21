#include "client.h"
#include <iostream>
#include <thread>
using namespace ve;

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
//	sender.join();
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

bool Client::sendType(int ID) 
{
	if(send(connection,(char*)&ID,sizeof(Type),0) == SOCKET_ERROR) { 
		return false;
	}
	return true;
}

bool  Client::getType(int &ID) {
	if(recv(connection,(char*)&ID,sizeof(Type),0) == SOCKET_ERROR) { 
		return false;
	}
	return true;
}

bool Client::sendData(int ID,int size,Byte* bytes)
{
	if(!sendType(ID))
	{
		return false;
	}
	if(!sendSize(size))
	{
		return false;
	}
	if(send(connection,(char*)bytes,size,0) == SOCKET_ERROR) 
	{
		return false;
	}
	return true;
}

bool Client::getData(int& ID,int& size,Byte* bytes)
{
	if( recv(connection, (char*)&ID, sizeof(int), 0) == SOCKET_ERROR)
	{
		return false;
	}
	if( recv(connection, (char*)&size, sizeof(int), 0) == SOCKET_ERROR)
	{
		return false;
	}
	bytes = new Byte [size];
	if( recv(connection, (char*)bytes, size, 0) == SOCKET_ERROR)
	{
		return false;
	}
	
	return true;
}

int main()
{
	Client testClient("127.0.0.1", 8787);
	testClient.cntToServer();
	
}

