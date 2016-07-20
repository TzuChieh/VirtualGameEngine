#pragma once

namespace xe
{

class Client;
class PlayerStatus;

class Player{
	public:
		Player();
		~Player();
		
		
	private:
		int numOfplayers;
		Client myClient;
		PlayerStatus localPlayer;
		PlayerStatus* otherPlayer;
};

}

