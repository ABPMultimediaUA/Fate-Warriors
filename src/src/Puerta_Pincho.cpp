#include "Puerta_Pincho.h"
#include "Trampas/Pinchos.h"
#include "Tiempo/Time.h"
#include "Interfaz/Objeto_Motor.h"
#include "Datos_Partida.h"
#include "Game.h"
#include "Nivel/Nivel.h"

Puerta_Pincho::Puerta_Pincho(short id, float _i_x, float _i_y,float _i_z,float _i_rotacion, Zona* _i_asociada_1, Zona* _i_asociada_2,  uint8_t _i_pasillo_asociado) : Objeto(id, _i_x, _i_y, _i_z){
    _zona_asociada1 = _i_asociada_1;
    _zona_asociada2 = _i_asociada_2;
    _reloj = Time::Instance();
    _pasillo_asociado = _i_pasillo_asociado;
    _tiempo_restante = 100;
    _siguiente_tiempo_hace_danyo =_reloj->get_current();
    _tiempo_hasta_posible_proxima_activacion= _reloj->get_current();
 
    const char* cstr  = "Puerta";

  //  _id=_id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z, 9999999);
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    desactivar();   
     _objeto_motor->rotar_nodo(_i_rotacion);
     Nivel::nivel_instancia()->nivel_abrir_pasillo(_pasillo_asociado);

}

Puerta_Pincho::~Puerta_Pincho() {
}

void Puerta_Pincho::activar(){
    _activado = true;
    _tiempo_restante = _reloj->get_current() + 10000;
    _tiempo_hasta_posible_proxima_activacion= _reloj->get_current() + 20000;
    setY(6);
    Nivel::nivel_instancia()->nivel_cerrar_pasillo(_pasillo_asociado);
    comprobar_a_quien_danya();
      //  _objeto_motor->rotar_nodo(125);

}

bool Puerta_Pincho::ha_pasado_tiempo_suficiente(){
    if(_reloj->get_current() > _tiempo_hasta_posible_proxima_activacion){
        return true;
    }
    return false;
}

void Puerta_Pincho::desactivar(){
    _activado = false;
    setY(-5.95);
    Nivel::nivel_instancia()->nivel_abrir_pasillo(_pasillo_asociado);
}

bool Puerta_Pincho::comprobar_si_finalizo_el_tiempo(){

    if(_reloj->get_current()>_tiempo_restante){
        return true;
    }
    return false;
}

bool Puerta_Pincho::get_activado(){
    return _activado;
}

void Puerta_Pincho::update(){
    if(_activado && comprobar_si_finalizo_el_tiempo()==true){
        desactivar();
    }

}

void Puerta_Pincho::comprobar_a_quien_danya(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();

    for (uint16_t num_character=0; num_character<_num_characters; num_character++){
        if(todos_personajes[num_character]->get_vida_actual()>0 && 
            motor->comprobar_colision(_objeto_motor->getRigidBody(), todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
                todos_personajes[num_character]->danyar(900);
        }   
    }
}

bool Puerta_Pincho::puede_quitar_vida(){ 
    if(_reloj->get_current() > _siguiente_tiempo_hace_danyo){
        _siguiente_tiempo_hace_danyo = _reloj->get_current() + 600;
        return true;
    }
    return false;
}
