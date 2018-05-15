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

#include "../Motor_sonido/Interfaz_sonido.h"

#include <iostream>

NPC::NPC(float _i_x, float _i_z, int16_t _i_vida, float _i_velocidad,
    int16_t _i_danyo_ataque_normal, int16_t _i_danyo_ataque_fuerte, Enum_Equipo equipo) 
    : Character(0, _i_x, 0, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte, Enum_Equipo_A){

    const char* cstr;
    const char* cstr2;
    if(equipo == Enum_Equipo_A){
        cstr = "NPC1";
        cstr2 = "Anim_idle_npc1";
        _tipo_npc = 1;
    }
    else{
        cstr = "NPC2";
        cstr2 = "Anim_idle_npc2";
        _tipo_npc = 2;
    }
    _blackboard = new Blackboard(this);
    
    _objeto_motor =new Objeto_Motor(true, this,E_BoundingCapsule, cstr, cstr2, _i_x, 0, _i_z, 69);
    //exit(0);
}

NPC::~NPC() {
    delete _blackboard;
}

void NPC::morir(){
    _sonido->Play_voces(4);

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
    //MIRAR AQUI (ANTES LLAMABA A SETY)
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

void NPC::danyar(int16_t _danyo){
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

void NPC::play_voces_ataque() {
    _sonido->Play_voces(3);
} 

void NPC::play_animaciones_ataque() {
    // ANIMACIONES
    _sonido->Stop_pasos();
    if(_tipo_npc == 1)
        anim_ataque_tipo_1();
    else
        anim_ataque_tipo_2();
}

void NPC::play_animaciones_recibir_danyo() {
    _sonido->Play_personaje(1);
    _sonido->Play_voces(5);
    switch(_tipo_npc) {
        case 1:
            _objeto_motor->cambiar_modelado("Anim_recibirdanyo_npc1", 16);
        break;

        case 2:
            _objeto_motor->cambiar_modelado("Anim_recibirdanyo_1_npc2", 16);
        break;
    }
}


void NPC::anim_ataque_tipo_1() {
    switch(_tipo_ataque)  
    {  
        case Ataque_Normal:
            _objeto_motor->cambiar_modelado("Anim_ataque_d1_npc1", 10);
            break;

        case Ataque_Normal_Normal:
            _objeto_motor->cambiar_modelado("Anim_ataque_d2_npc1", 12);
            break;

        case Ataque_Normal_Fuerte:
            _objeto_motor->cambiar_modelado("Anim_ataque_d3_npc1", 13);
            break;

        case Ataque_Fuerte:
            _objeto_motor->cambiar_modelado("Anim_ataque_f1_npc1", 11);
            break;

        case Ataque_Fuerte_Normal: 
            _objeto_motor->cambiar_modelado("Anim_ataque_f2_npc1", 14);
            break;

        case Ataque_Fuerte_Fuerte:
            _objeto_motor->cambiar_modelado("Anim_ataque_f3_npc1", 15);
            break;
    }
}


void NPC::anim_ataque_tipo_2() {
    switch(_tipo_ataque)  
    {  
        case Ataque_Normal:
            _objeto_motor->cambiar_modelado("Anim_ataque_d1_npc2", 10);
            break;

        case Ataque_Normal_Normal:
            _objeto_motor->cambiar_modelado("Anim_ataque_d2_npc2", 12);
            break;

        case Ataque_Normal_Fuerte:
            _objeto_motor->cambiar_modelado("Anim_ataque_d3_npc2", 13);
            break;

        case Ataque_Fuerte:
            _objeto_motor->cambiar_modelado("Anim_ataque_f1_npc2", 11);
            break;

        case Ataque_Fuerte_Normal: 
            _objeto_motor->cambiar_modelado("Anim_ataque_f2_npc2", 14);
            break;

        case Ataque_Fuerte_Fuerte:
            _objeto_motor->cambiar_modelado("Anim_ataque_f3_npc2", 15);
            break;
    }
}

void NPC::aparecer_muerto() {
    _vida = 0;

    _inventario->soltar_armas(getX(), getZ()); 

    Respawn::posiciones_instancia()->anyadir_character_y_tiempo_para_reaparecer(this, _tiempo->get_current()+9000);

    if(_zona_en_la_que_se_encuentra != nullptr){
        _zona_en_la_que_se_encuentra->eliminar_npc_de_zona(this);

        Game* punterito         = Game::game_instancia();
        Datos_Partida * datos   = punterito->game_get_datos();
        Consumible_Manager* _consumibles_manager    = datos->get_Consumible_Manager();
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

void NPC::animacion_idle() {
    switch(_tipo_npc) {
        case 1:
            _objeto_motor->cambiar_modelado("Anim_idle_npc1", 0);
        break;

        case 2:
            _objeto_motor->cambiar_modelado("Anim_idle_npc2", 0);
        break;
    }
}

void NPC::animacion_andar() {
    switch(_tipo_npc) {
        case 1:
            _objeto_motor->cambiar_modelado("Anim_andar_npc1", 1);

        break;

        case 2:
            _objeto_motor->cambiar_modelado("Anim_andar_npc2", 1);

        break;
    }
}

void NPC::animacion_correr() {
    switch(_tipo_npc) {
        case 1:
            _objeto_motor->cambiar_modelado("Anim_correr_npc1", 2);
            Motor::Motor_GetInstance()->_interfaz->Crear_particulas_Suelo(getX(),1, getZ(), get_direccion_actual()); 
        break;

        case 2:
            _objeto_motor->cambiar_modelado("Anim_correr_npc2", 2);
            Motor::Motor_GetInstance()->_interfaz->Crear_particulas_Suelo(getX(),1, getZ(), get_direccion_actual()); 
        break;
    }
}