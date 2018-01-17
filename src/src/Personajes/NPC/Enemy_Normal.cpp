#include "Enemy_Normal.h"
#include <iostream>
#include "../../Game.h"
#include "../../Datos_Partida.h"
#include "../Player.h"
#include "../../Interfaz/Motor.h"

Enemy_Normal::Enemy_Normal(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    : Enemy(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte, Enum_Tipo_Enemigo::Normal) {
}

Enemy_Normal::~Enemy_Normal() {
}

void Enemy_Normal::danyar(short _danyo){
    danyar_comun(_danyo);
}

void Enemy_Normal::gestion_ataque(){

    if(this->get_accion() == Accion_pre_atacar){
        std::cout << "PRE-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Atacar);
            
        }
    }
    else if(this->get_accion() == Atacar){
        Player * _player = Game::game_instancia()->game_get_datos()->get_player();
        if(comprobar_colision_teniendo_tambien_radio(this->get_vector(), 3, _player->get_vector(), 3) == true)
        {
            if(this->get_tipo_ataque() == Ataque_Normal){
                _player->danyar(_danyo_ataque_normal);
            }
            else if(this->get_tipo_ataque()  == Ataque_Fuerte){
                _player->danyar(_danyo_ataque_fuerte);
            }   
            else if(this->get_tipo_ataque()  == Ataque_Normal_Normal){
                _player->danyar(_danyo_ataque_normal);
            } 
            else if(this->get_tipo_ataque()  == Ataque_Normal_Fuerte){
                _player->danyar(_danyo_ataque_normal);
            } 
            else if(this->get_tipo_ataque()  == Ataque_Fuerte_Normal){
                _player->danyar(_danyo_ataque_normal);
            } 
            else if(this->get_tipo_ataque()  == Ataque_Fuerte_Fuerte){
                _player->danyar(_danyo_ataque_normal);
            } 
        }

        std::cout << "ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(0,0,255);
        if(esta_bloqueado() == false){
            this->set_accion(Accion_post_atacar);
        }
    }
    else if(this->get_accion() == Accion_post_atacar){
        std::cout << "POST-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,20,147);
        if(esta_bloqueado() == false){
            this->set_accion(Nada);
        }
    }
}