#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") 

//use window socket
#include <Winsock2.h>

//standard lib
#include <iostream>
#include <cstring>
#include <thread>
#include "Server.h"
using namespace std;
using namespace xe;


Server::Server(int port) 
{
	WSAData wsaData;
	WORD version = MAKEWORD(2,2); // verion 2.2
	if( WSAStartup(version, &wsaData) != 0) {
		cerr << "Winsock startup failed !" << endl ;
		exit(1);
	}	
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(port); // port
	addr.sin_family = AF_INET;   // IPv4
	
	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if(bind(sListen,(SOCKADDR*)&addr,sizeof(this->addr)) == SOCKET_ERROR) {
		cerr << "Failed to bind the address to our listening socket.!" << endl;
		exit(1);
	}
	if(listen(sListen, SOMAXCONN) == SOCKET_ERROR) {
		cerr << "Failed to listen on listening socket." << endl;
		exit(1);
	}
}

Server::~Server() {
	//need to check thread
}

bool Server::LisConnection() {
	SOCKET newConnection;
	SOCKADDR_IN client_addr; 
	int addrlen = sizeof(this->addr);
	for(int i = 0 ; i < MAX_USERS ; i++){
		newConnection = accept(sListen,(SOCKADDR*)&client_addr, &addrlen);
		if(newConnection == 0){
			cerr << "Failed to accept the client's connention." << endl;
			return false;
		}
		else{
			cout << "Client Connect!" << endl; 
//			cout << "IP addr :" << client_addr.sin_addr.s_addr << endl;
			this->users[i] = newConnection; 
			this->totalUsers++;
//			thread clientManager(callThread,this);
//			CreateThread(0,0,(LPTHREAD_START_ROUTINE)callThread,(LPVOID)(i),0,0);
//			string data = "Welcome to Server ! Have a nice day!";
//			sendString(i,data);
		}
	}
}



void Server::callThread(void* param) {
	Server* myServer = static_cast<Server*>(param);
	myServer->serverThread(0);
}

void Server::serverThread(int id) {
	while(1){
		//if server doesn't get response from client
	
	}
	cout << "Lost connction to client " << id << endl;
	closesocket(this->users[id]);
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
