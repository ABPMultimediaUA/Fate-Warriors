#include "NPC.h"

#include "../IA/Blackboard.h"
#include "../Interfaz_Libs/Lib_Math.h"

#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"

#include "../Tiempo/Time.h"

#include <iostream>
//#include "../Interfaz/Objeto_Motor.h"



NPC::NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte, Enum_Tipo_Enemigo _i_tipo_npc) 
    : Character(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte),
    _blackboard(nullptr) {
    _tipo_npc = _i_tipo_npc;
    
    //std::cout << "Tipo NPC = " << _tipo_npc << "\n";

    const char* cstr  = "models/Personajes/Enemigos/Enemigo.obj";

   // _id_motor = _motor->crear_objeto(E_BoundingCapsule,cstr,_i_x,_i_y,_i_z,60);
    
    _objeto_motor =new Objeto_Motor(this,E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);

}

NPC::~NPC() {
}

void NPC::stop() {
    //_motor->Mover(_id_motor,0, 0, 0);
}

void NPC::update() {

}

void NPC::render() {

}

void NPC::danyar(short _danyo){
    danyar_comun(_danyo);
}

void NPC::set_blackboard(Blackboard* _i_blackboard) {
    _blackboard = _i_blackboard;
}

Blackboard* NPC::get_blackboard() {
    return _blackboard;
}
