#include "NPC.h"

#include "../Interfaz_Libs/Lib_Math.h"

#include <iostream>

NPC::NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad) : Character(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad) {}

NPC::~NPC() {}


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


void NPC::update(){}
void NPC::render(){}