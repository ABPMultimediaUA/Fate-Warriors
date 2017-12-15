#include "Character.h"
#include <iostream>

Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad) : Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _velocidad(_i_velocidad) {

}

Character::~Character() {

}

short Character::get_vida(){
	return _vida;
}

void Character::modificar_vida_en(short _i_vida){
	_vida+=_i_vida;
}

void Character::poner_vida_a(short _i_vida){
	_vida=_i_vida;
}

