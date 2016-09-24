#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 

#include <Winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono> // for test
#include "Server.h"
using namespace ve;

Server::Server(int port) 
{
	if(!wsaSetup())
		std::cerr << "Winsock startup fail!" << std::endl;
	m_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	m_addr.sin_port = htons(port); // port
	m_addr.sin_family = AF_INET;   // IPv4
	m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(bind(m_listenSocket,(SOCKADDR*)&m_addr,sizeof(m_addr)) == SOCKET_ERROR) {
		std::cerr << "Failed to bind the address to ListenSocket.!" << std::endl;
		exit(1);
	}
	if(listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Failed to listen on ListenSocket." << std::endl;
		exit(1);
	}
	std::cout << "Server start! : ";
	std::cout << inet_ntoa(m_addr.sin_addr) << '/' << ntohs(m_addr.sin_port) << std::endl;  
}

Server::~Server() 
{
	// TBC
	// close all of the client thread set all state false
}

bool Server::wsaSetup()
{
	WSAData wsaData;
	WORD version = MAKEWORD(2,2); // verion 2.2
	if( WSAStartup(version, &wsaData) != 0) 
	{
		return false;
	}
	return true;
}

void Server::LisConnection() 
{
	SOCKET newConnection;
	SOCKADDR_IN client_addr; 
	int addrlen = sizeof(m_addr);
	for(int i = 0 ; i < MAX_USERS ; i++){
		newConnection = accept(m_listenSocket,(SOCKADDR*)&client_addr, &addrlen);
		if(newConnection == 0)
		{
			std::cerr << "Failed to accept the client's connention." << std::endl;
			return;
		}
		else
		{
			connectionHandler(newConnection,client_addr,i);
		}
	}
	return;
}

void Server::connectionHandler(SOCKET newConnection,SOCKADDR_IN client_addr,int index)
{
	std::cout << "New client connect!"; 
	std::cout << " IP:" << inet_ntoa(client_addr.sin_addr) << '/' <<ntohs(client_addr.sin_port)  << std::endl;
	m_users[index] = newConnection; 
	m_totalUsers++;
	
	m_clientState[index] = true;
	m_clientManager[index] = std::thread(callThread,this,index); //Move assignment
}


void Server::callThread(Server* myServer,int index) 
{
	myServer->serverThread(index);
}

void Server::serverThread(int clientId) 
{
	while(m_clientState[clientId])
	{
//		int size;
//		if(!getSize(clientId,size))
//			break;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
		//if server doesn't get response from client
	std::cout << "Lost connction to client " << clientId << std::endl;
	closesocket(m_users[clientId]);
}

bool Server::sendSize(int clientId, int size) {
	if(send(m_users[clientId],(char*)&size,sizeof(int),0) == SOCKET_ERROR) { //check data tranfer
		return false;
	}
	return true;
}

bool Server::getSize(int clientId,int &size) {
	if(recv(m_users[clientId], (char*)&size,sizeof(int),0) == SOCKET_ERROR) { //check data tranfer
		return false;
	}
	return true;
}

//bool Server::sendType(int clientId,int packetType) {
//	if(send(m_users[clientId],(char*)&packetType,sizeof(Packet),0) == SOCKET_ERROR) { //check data tranfer
//		return false;
//	}
//	return true;
//}
//
//bool  Server::getType(int clientId,Packet &packetType) {
//	if(recv(m_users[clientId],(char*)&packetType,sizeof(Packet),0) == SOCKET_ERROR) { //check data tranfer
//		return false;
//	}
//	return true;
//}


int main()
{
	Server testServer(8787);
	testServer.LisConnection();
	 
}
