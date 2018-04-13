#include "NPC.h"

#include "Inventario.h"

#include "../IA/Blackboard.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"
#include "../Zonas/Respawn.h"
#include "../Interactuables/Interruptor.h"
#include "../Tiempo/Time.h"

#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Consumibles/Consumible_Manager.h"



#include <iostream>

NPC::NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte, Enum_Equipo equipo) 
    : Character(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte, equipo){

    const char* cstr;
    if(equipo == Enum_Equipo_B)
        cstr = "models/Personajes/Enemigos/NPC2/NPC2.obj";
    else
        cstr = "models/Personajes/Enemigos/NPC1/NPC1.obj";

    _blackboard = new Blackboard(this);
    
    _objeto_motor =new Objeto_Motor(this,E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);

}

NPC::~NPC() {
    delete _blackboard;
}

void NPC::morir(){
    //float mult = 4.9212625;
    //std::cout << "He muerto :("<< std::endl;
    _inventario->soltar_armas(getX(), getZ()); 

    Respawn::posiciones_instancia()->anyadir_character_y_tiempo_para_reaparecer(this, _tiempo->get_current()+9000);

    
    if(_zona_en_la_que_se_encuentra != nullptr){
        _zona_en_la_que_se_encuentra->eliminar_npc_de_zona(this);

        Game* punterito 		= Game::game_instancia();
        Datos_Partida * datos	= punterito->game_get_datos();
        Consumible_Manager* _consumibles_manager 	= datos->get_Consumible_Manager();
        _consumibles_manager->anyadir_consumible(Vector2(getX(), getZ()));

    }
  
    setY(99999999999);

    _zona_en_la_que_se_encuentra = nullptr;

    if(_blackboard->_enemigo_mas_cerca != nullptr){
        _blackboard->_enemigo_mas_cerca->decrementar_npcs_persiguiendome();
        _blackboard->_enemigo_mas_cerca = nullptr;
        _blackboard->_enemigo_mas_cerca_esta_cerca = false;
        _blackboard->_enemigo_mas_cerca_esta_muy_cerca = false;
        _blackboard->_distancia_enemigo_mas_cerca =  10000000000;
    }

}

void NPC::stop() {
    //_motor->Mover(_id_motor,0, 0, 0);
}

void NPC::danyar(short _danyo){
    danyar_comun(_danyo);
}

void NPC::set_blackboard(Blackboard* _i_blackboard) {
    _blackboard = _i_blackboard;
}

void NPC::comprobar_si_asignar_arma_y_asignarla(Armas_Manager* _armas_manager){ 
    if ((rand() % 100) < 1000){ 
        _inventario->crear_un_arma_al_azar_asignar_y_equipar(_armas_manager); 
    } 
} 