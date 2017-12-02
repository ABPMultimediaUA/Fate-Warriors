#include "Player.h"
#include <iostream>

Player::Player(short _id, float _i_x, float _i_y, float _i_z, short vida) : Character(_id,_i_x, _i_y, _i_z, vida){
}

Player::~Player(){
}

void Player::update(){
    /*
   switch (_KeyMan->getLastKeyPressed()) {
      case 'a': std::cout << "holaa"; break;
      case 'w': std::cout << "holaw"; break;
      case 's': std::cout << "holas"; break;
      case 'd': std::cout << "holad"; break;
      default: break;
	}
	*/
}
			
void Player::render(){

}
