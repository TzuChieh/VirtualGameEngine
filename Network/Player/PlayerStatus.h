#pragma once

namespace xe
{

class PlayerStatus{
	public:
		PlayerStatus();
		~PlayerStatus();
		
		update(); // a test function to stimulate real action
		
	private:
		int id;
		//position
		float pos_x;
		float pos_y;
		float pos_z;
		//direction
		float dir_x;
		float dir_y;
		float dir_z;
		
		unsigned int health;
		unsigned int armor;
		
		
};

}
