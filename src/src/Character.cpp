#include "Character.h"

#include <iostream>

Character::Character( float _i_vida, float _i_x, float _i_y) {
	_vida = _i_vida;
	_x = _i_x;
	_y = _i_y;

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}


float Character::get_x() {
	return _x;
}

float Character::get_y() {
	return _y;
}
