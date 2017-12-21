#include "NPC.h"

#include "../IA/Blackboard.h"
#include "../Interfaz_Libs/Lib_Math.h"

#include "../Interfaz/Matcher.h"
#include "../Utilidades/Modelados.h"

#include <iostream>



NPC::NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    : Character(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte),
    _blackboard(nullptr) {
    _matcher = new Matcher(PERSONAJE_R, PERSONAJE_M, _i_x, _i_y, _i_z, 1, false);
}

NPC::~NPC() {

}

void NPC::move(unsigned long _i_direccion) {
    
    float _desp_x = cos(_i_direccion*PI/180);
    _desp_x = roundf(_desp_x * 100) / 100;
    float _desp_z = sin(_i_direccion*PI/180);
    _desp_z = roundf(_desp_z * 100) / 100;
    //std::cout << "Personaje se mueve en la x " << _desp_x << std::endl;
    //std::cout << "Personaje se mueve en la y " << _desp_y << std::endl;
    _x = _x + _desp_x;
    _z = _z + _desp_z;
    //std::cout << "Personaje se ha movido a la posicion (" << _x << "," << _z << ")" << std::endl;
    _matcher->Mover(_desp_x*100, 0, _desp_z*100);
    //std::cout << "sin(direccion) = " << std::cos(_i_direccion*PI/180) << '\n';
}

float NPC::getX(){
    return(_matcher->getPosition()._x);
}

float NPC::getY(){
    return(_matcher->getPosition()._y);
}

float NPC::getZ(){
    return(_matcher->getPosition()._z);
}

void NPC::update() {

}

void NPC::render() {

}

void NPC::set_blackboard(Blackboard* _i_blackboard) {
    _blackboard = _i_blackboard;
}

Blackboard* NPC::get_blackboard() {
    return _blackboard;
}
