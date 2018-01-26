#include "Enemy_Normal.h"
#include <iostream>
#include "../../Game.h"
#include "../../Datos_Partida.h"
#include "../Player.h"
#include "../../Interfaz/Motor.h"
#include "../../Interfaz_Libs/Lib_Math.h"

Enemy_Normal::Enemy_Normal(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad,
    short _i_danyo_ataque_normal, short _i_danyo_ataque_fuerte) 
    : Enemy(_i_id, _i_x, _i_y, _i_z, _i_vida, _i_velocidad, _i_danyo_ataque_normal, _i_danyo_ataque_fuerte, Enum_Tipo_Enemigo::Normal) {
}

Enemy_Normal::~Enemy_Normal() {
}

void Enemy_Normal::danyar(short _danyo){
    danyar_comun(_danyo);
}


void Enemy_Normal::gestion_ataque(){ // CONTROLAR GESTION DE ENEMIGO, que esta OVERRIDE

    if(this->get_accion() == Accion_pre_atacar){
        std::cout << "PRE-ATACANDO" << std::endl;
        _objeto_motor->colorear_nodo(255,255,0);
        if(esta_bloqueado() == false){
            this->set_accion(Atacar);
            Motor::Motor_GetInstance()->posicionar_y_escalar_rb(_rb_ataque, this->get_objeto_motor()->get_posicion_rb(), btVector3(5,1,5));
        }
    }
    else if(this->get_accion() == Atacar){

        Player * _player = Game::game_instancia()->game_get_datos()->get_player();


        if(Motor::Motor_GetInstance()->comprobar_colision(_rb_ataque, _player->get_objeto_motor()->getRigidBody()) == true)
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
            std::cout << "----- " << _player->get_vida() << "------" << std::endl;


            // Impulsa al atacado

            float x = _player->getX() - this->getX();
            float z = _player->getZ() - this->getZ();

            Vector2 direccion_impulso(x,z);
            direccion_impulso.Normalize();

            float valor = lib_math_distancia_2_puntos(_player->getX(), _player->getZ(), this->getX(), this->getZ());

            Vector3 a(direccion_impulso._x*(50000/valor),0,direccion_impulso._y*(50000/valor));
            _player->get_objeto_motor()->Impulso_explosion(a);
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
























