#include "Character.h"
#include <iostream>

Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida) : Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida) {

}

Character::~Character() {

}

short Character::get_vida(){
	return _vida;
}