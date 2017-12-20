#include "Character.h"
#include "../Inventario.h"
#include <iostream>

Character::Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad) : Objeto_Movil(_id, _i_x, _i_y, _i_z), _vida(_i_vida), _vida_maxima(_i_vida), _velocidad(_i_velocidad) {
    _inventario = new Inventario();
}

Character::~Character() {
    delete _inventario;
}

short Character::get_vida(){
	return _vida;
}

void Character::modificar_vida_en(short _i_vida){
	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else{
        _vida+=_i_vida;
    }
}

void Character::poner_vida_a(short _i_vida){
	_vida=_i_vida;
}

Inventario* Character::get_inventario(){
    return _inventario;
}

bool Character::isDead(){
    if(_vida>0){
        return false;
    }
    return true;
}

bool Character::puede_subir_vida_(short _i_vida){
    if(_vida==_vida_maxima){
        return false;
    }
    return true;
}
