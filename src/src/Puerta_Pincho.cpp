#include "Puerta_Pincho.h"
#include "Trampas/Pinchos.h"
#include "Tiempo/Time.h"
#include "Interfaz/Objeto_Motor.h"
#include "Datos_Partida.h"
#include "Game.h"

Puerta_Pincho::Puerta_Pincho(short id, float _i_x, float _i_y,float _i_z, Zona* _i_asociada_1, Zona* _i_asociada_2){
    _zona_asociada1 = _i_asociada_1;
    _zona_asociada2 = _i_asociada_2;
    _reloj = Time::Instance();

    _pinchos = new Pinchos(0,_i_x, _i_y, _i_z);
    _activado = false;
}

Puerta_Pincho::~Puerta_Pincho() {
    delete _pinchos;
}

void Puerta_Pincho::activar(){
    _activado = true;
    _tiempo_restante = _reloj->get_current() + 5000;
    _pinchos->get_objeto_motor()->setPositionY(0);
}

void Puerta_Pincho::desactivar(){
    _activado = false;
    _pinchos->get_objeto_motor()->setPositionY(-20);
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
    if(comprobar_si_finalizo_el_tiempo()==true){
        desactivar();
    }
    else if(_activado){
        comprobar_a_quien_danya();
    }
}

void Puerta_Pincho::comprobar_a_quien_danya(){
    Game* game 		= Game::game_instancia();
	Datos_Partida * _datos	= game->game_get_datos();
    Character** todos_personajes = _datos->get_characters();
	uint16_t _num_characters = _datos->get_num_characters();
    Motor* motor = Motor::Motor_GetInstance();
    if(_pinchos->puede_quitar_vida()){
        for (uint16_t num_character=0; num_character<_num_characters; num_character++){
        if(motor->comprobar_colision(_pinchos->get_objeto_motor()->getRigidBody(), todos_personajes[num_character]->get_objeto_motor()->getRigidBody()) == true){
                todos_personajes[num_character]->danyar(_pinchos->get_danyo());
        }   
        }
    }
}