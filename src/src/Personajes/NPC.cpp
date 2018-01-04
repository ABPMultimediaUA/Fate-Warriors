#include "NPC.h"

#include "../IA/Blackboard.h"
#include "../Interfaz_Libs/Lib_Math.h"

#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"

#include <iostream>



NPC::NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    : Character(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte),
    _blackboard(nullptr) {
    _tipo_npc=Enum_Tipo_Enemigo::Normal;
    _motor = Motor::Motor_GetInstance();
    std::string str = "models/Enemigo.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    _id = _motor->crearObjeto(cstr,_i_x,_i_y,_i_z);

}

NPC::~NPC() {
    delete _motor;
}

void NPC::move(unsigned long _i_direccion) {
    //std::cout<<"move direccion: "<<_i_direccion<<std::endl;
    float _desp_x = cos(_i_direccion*PI/180);
    _desp_x = roundf(_desp_x * 200) / 100;
    float _desp_z = sin(_i_direccion*PI/180);
    _desp_z = roundf(_desp_z * 200) / 100;
    //std::cout << "Personaje se mueve en la x " << _desp_x << std::endl;
    //std::cout << "Personaje se mueve en la y " << _desp_y << std::endl;
    _x = _x + _desp_x;
    _z = _z + _desp_z;
    //std::cout << "Personaje se ha movido a la posicion (" << _x << "," << _z << ")" << std::endl;
    _motor->Mover(_id, _desp_x*100,0,_desp_z*100);
    //_motor->setPositionXZ(_id,_desp_x*100,_desp_z*100);
    //_motor->moverXZ(_id,0,0);
    //std::cout << "sin(direccion) = " << std::cos(_i_direccion*PI/180) << '\n';
}


void NPC::stop() {
    _motor->Mover(_id,0, 0, 0);
}

float NPC::getX(){
    return(_motor->getX(_id));
}

float NPC::getY(){
    return(_motor->getY(_id));
}

float NPC::getZ(){
    return(_motor->getZ(_id));
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
void NPC::setPositionXZ(float _i_x, float _i_z){
    _motor->setPositionXZ(_id,_i_x,_i_z);
}
