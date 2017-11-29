#include "Consumible.h"
#include <iostream>

Consumible::Consumible(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_valor) : Objeto(_id, _i_x, _i_y, _i_z,  _i_ancho, _i_alto), _valor(_i_valor) {
}

Consumible::~Consumible() {
}

void Consumible::update(){

}

void Consumible::render(){

}

bool Consumible::usar(){
	return true;
}

short Consumible::get_valor(){
	return _valor;
}