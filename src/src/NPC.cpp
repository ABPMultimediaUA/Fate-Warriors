#include "NPC.h"

#include "Lib_Math.h"

#include <iostream>

NPC::NPC(float _i_vida, float _i_x, float _i_y) : Character(_i_vida, _i_x, _i_y) {
	_accion_actual = Nada;
}

NPC::~NPC() {
}


void NPC::set_action(enum Enum_Acciones _i_accion) {
	_accion_actual = _i_accion;
}

void NPC::do_action() {

}

enum Enum_Acciones NPC::get_action() {
	return _accion_actual;
}

void NPC::move(unsigned long _i_direccion) {
    //std::cout << "Personaje se encuentra en la posicion (" << _x << "," << _y << ")" << std::endl;
    float _desp_x = cos(_i_direccion*PI/180);
    _desp_x = roundf(_desp_x * 100) / 100;
    float _desp_y = sin(_i_direccion*PI/180);
    _desp_y = roundf(_desp_y * 100) / 100;
    //std::cout << "Personaje se mueve en la x " << _desp_x << std::endl;
    //std::cout << "Personaje se mueve en la y " << _desp_y << std::endl;
    _x = _x + _desp_x;
    _y = _y + _desp_y;
    std::cout << "Personaje se ha movido a la posicion (" << _x << "," << _y << ")" << std::endl;

    //std::cout << "sin(direccion) = " << std::cos(_i_direccion*PI/180) << '\n';
}
