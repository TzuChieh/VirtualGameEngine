#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 

#include <Winsock2.h>
#include <iostream>
#include <string>
#include <thread>
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
		std::cerr << "Failed to bind the address to our listening socket.!" << std::endl;
		exit(1);
	}
	if(listen(m_listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "Failed to listen on listening socket." << std::endl;
		exit(1);
	}
	std::cout << "Server start! : ";
	std::cout << inet_ntoa(m_addr.sin_addr) << '/' << ntohs(m_addr.sin_port) << std::endl;  
}

Server::~Server() 
{
	// TBC
	// close all of the client thread
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

bool Server::LisConnection() 
{
	SOCKET newConnection;
	SOCKADDR_IN client_addr; 
	int addrlen = sizeof(m_addr);
	for(int i = 0 ; i < MAX_USERS ; i++){
		newConnection = accept(m_listenSocket,(SOCKADDR*)&client_addr, &addrlen);
		if(newConnection == 0)
		{
			std::cerr << "Failed to accept the client's connention." << std::endl;
			return false;
		}
		else
		{
			connectionHandler(newConnection,client_addr,i);
		}
	}
}

void Server::connectionHandler(SOCKET newConnection,SOCKADDR_IN client_addr,int index)
{
	std::cout << "New client connect!"; 
	std::cout << " IP:" << inet_ntoa(client_addr.sin_addr) << '/' <<ntohs(client_addr.sin_port)  << std::endl;
	m_users[index] = newConnection; 
	m_totalUsers++;
	std::thread temp(callThread,this,index);
//	std::thread temp(callThread,this,index);
	m_clientManager.push_back(temp);
//	m_clientManager.back() = std::thread(callThread,this,index);
//	string data = "Welcome to Server ! Have a nice day!";
//	sendString(i,data);
}


void Server::callThread(Server* myServer,int index) 
{
	myServer->serverThread(index);
}

void Server::serverThread(int id) 
{
	while(1)
	{
		//if server doesn't get response from client
	
	}
	std::cout << "Lost connction to client " << id << std::endl;
	closesocket(m_users[id]);
}

//
//bool Server::sendSize(int id, int size) {
//	if(send(this->users[id],(char*)&size,sizeof(int),0) == SOCKET_ERROR) { //check data tranfer
//		return false;
//	}
//	return true;
//}
//
//bool Server::getSize(int id,int &size) {
//	if(recv(this->users[id], (char*)&size,sizeof(int),0) == SOCKET_ERROR) { //check data tranfer
//		return false;
//	}
//	return true;
//}
//
//bool Server::sendType(int id,Packet packetType) {
//	if(send(this->users[id],(char*)&packetType,sizeof(Packet),0) == SOCKET_ERROR) { //check data tranfer
//		return false;
//	}
//	return true;
//}
//
//bool  Server::getType(int id,Packet &packetType) {
//	if(recv(this->users[id],(char*)&packetType,sizeof(Packet),0) == SOCKET_ERROR) { //check data tranfer
//		return false;
//	}
//	return true;
//}
//
//bool Server::sendString(int id,string &s) {
//	if (!sendType(id,p_info)){
//		return false;
//	}
//	int length = s.length();
//	if(!sendSize(id,length)){
//		return false;
//	}
//	if(send(this->users[id], s.c_str(),length,0) == SOCKET_ERROR) {
//		return false;
//	}
//	return true;
//}
//
//bool Server::getString(int id,string &s) {
//	int length;
//	if(!getSize(id,length)){
//		return false;
//	}
//	char* buffer = new char [length+1]; //with '\0'
//	int retnCheck = recv(this->users[id], buffer, length, 0);
//	s = buffer; //char array to string
//	delete[] buffer;
//	if (retnCheck == SOCKET_ERROR) //If connection is lost while getting message
//		return false; 
//	return true;
//}

int main()
{
	Server testServer(8787);
	testServer.LisConnection();
	 
}
