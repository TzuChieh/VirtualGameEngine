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
	m_addr.sin_addr.s_addr = inet_addr(ip.c_str());// ip convert to char*
	m_addr.sin_port = htons(port); 			     // port
	m_addr.sin_family = AF_INET ; 				 // IPv4
	m_connectionState = false;
}

Client::~Client()
{
	//wait for the thread
	if(m_sender.joinable())
	{
		m_sender.join();
		std::cout << "the sender stop." << std::endl;
	}
}

bool Client::cntToServer()
{
	m_connection = socket(AF_INET, SOCK_STREAM, 0); 
	if( connect(m_connection,(SOCKADDR*)&m_addr,sizeof(m_addr))) 
	{  
		std::cerr << "Fail to connect to server!" << std::endl;
		return false;
	}
	m_connectionState = true;
	std::cout << "Connected!" << std::endl;
	
	m_sender = std::thread (&Client::callThread, static_cast<void*>(this)); 
	return true;
}

bool Client::disConnect() 
{
	if(closesocket(m_connection) == SOCKET_ERROR && WSAGetLastError() != WSAENOTSOCK) {
		// can not close the socket and the error is not socket have closed.
		std::cerr << "Failed to close the socket. Winsock Error: " << WSAGetLastError()  << std::endl;
		return false;
	}
	m_connectionState = false;
	return true;
}

void Client::callThread(void* param) 
{
	Client* myclient = static_cast<Client*>(param);
	myclient->clientThread();
}

void Client::clientThread()
{
	while(m_connectionState);
	
	// send close msg
}

bool Client::sendSize(int size) {
	if(send(m_connection,(char*)&size,sizeof(int),0) == SOCKET_ERROR)
	{ 
		return false;
	}
	return true;
}

bool Client::getSize(int &size) {
	if(recv(m_connection, (char*)&size,sizeof(int),0) == SOCKET_ERROR) 
	{ 
		return false;
	}
	return true;
}

bool Client::sendType(int ID) 
{
	if(send(m_connection,(char*)&ID,sizeof(Type),0) == SOCKET_ERROR) { 
		return false;
	}
	return true;
}

bool  Client::getType(int &ID) {
	if(recv(m_connection,(char*)&ID,sizeof(Type),0) == SOCKET_ERROR) { 
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
	if(send(m_connection,(char*)bytes,size,0) == SOCKET_ERROR) 
	{
		return false;
	}
	return true;
}

bool Client::getData(int& ID,int& size,Byte* bytes)
{
	if( recv(m_connection, (char*)&ID, sizeof(int), 0) == SOCKET_ERROR)
	{
		return false;
	}
	if( recv(m_connection, (char*)&size, sizeof(int), 0) == SOCKET_ERROR)
	{
		return false;
	}
	bytes = new Byte [size];
	if( recv(m_connection, (char*)bytes, size, 0) == SOCKET_ERROR)
	{
		return false;
	}
	
	return true;
}

int main()
{
	Client testClient("127.0.0.1", 8787);
	testClient.cntToServer();
	for(int i = 0 ; i < 1000000000 ; i++);
	testClient.disConnect();
}

