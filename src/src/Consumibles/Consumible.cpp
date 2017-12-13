#include "Consumible.h"
#include <iostream>

#include "../Interfaz/Interfaz.h"

Consumible::Consumible(short _id, float _i_x, float _i_y, float _i_z, short _i_valor) : Objeto(_id, _i_x, _i_y, _i_z), _valor(_i_valor), _interface(Interfaz::Interfaz_getInstance()) {
    _interface->Interfaz_cargaCaja(_i_x, _i_y, _i_z);
    _interface->Interfaz_collisionEnable();
}

Consumible::~Consumible() {
    std::cout << "esta aqui " << std::endl;
}


void Consumible::render(){

}

short Consumible::get_valor(){
	return _valor;
}