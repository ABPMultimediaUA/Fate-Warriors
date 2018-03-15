#include "Player_Online.h"
#include <iostream>
#include "../Entrada/Input.h"
#include "../Input.h"
#include "../Entrada/Controles.h"
#include "../Camara/Camara.h"
#include "../Tiempo/Time.h"
#include "../Interfaz/Motor.h"
#include "../Utilidades/Modelados.h"

#include "../Nivel/Nivel.h"

#include "../Interfaz_Libs/Lib_Math.h"
#include "../Interfaz/Motor.h"
//#include "../Interfaz/Objeto_Motor.h"
#include "../Respawn.h"

#include "../Motor_sonido/Interfaz_sonido.h"

#include "../Game.h"
#include "../Action_Manager.h"
#include "../Network/Cliente.h"
                                                                                                            //  vida_prota, velocidad
Player_Online::Player_Online(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input, bool _es_jugador_online) : Player(_id, _i_x, _i_y, _i_z, _i_input, true)
                                                                {   
    _motor= Motor::Motor_GetInstance();
    _sonido= Interfaz_sonido::GetInstancia();
    //_tiempo = Time::Instance();
    //crear nodo de personaje del motor

    es_jugador_online = _es_jugador_online;                                                                

    const char* cstr  = "models/Personajes/Enemigos/Enemigo.obj";
    _objeto_motor = new Objeto_Motor(this, E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,80);
    
    
    //_id_motor = _motor->crear_objeto(E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);
    //std::cout<<"X Player_Online: "<<_motor->getX(_id_motor);
    //std::cout<<"Z Player_Online: "<<_motor->getZ(_id_motor)<<std::endl;

    _input = _i_input;
    _motor->set_text_vida(_vida);
    _especial = 0;
    _puede_actualizar = true;
    //_sonido->Play_ambiente(2);
}

Player_Online::~Player_Online(){
}

void Player_Online::update(){
    //std::cout<< "ACCION_ACTUAL: "<< _accion << "\n";
    if (_vida>0){

        gestion_acciones();

      //set level of detail del nivel
        Nivel* nivel=Nivel::nivel_instancia();
        nivel->nivel_set_lod(nivel->nivel_get_id_vertice(getX(),getZ()));
        //std::cout << "id vertice set lod: " <<nivel->nivel_get_id_vertice(getX(),getZ()) << std::endl;
        
    }
    else{
        //std::cout<<"sigo muerto" << std::endl;
        Respawn::posiciones_instancia()->comprobar_si_renace_y_renacer_personaje(this);
    }
    //Cliente::getInstance()->send_desplazamiento(0,getX(),getZ());
    

}



void Player_Online::comprobar_input(Enum_Inputs key_press){
    
    
    if(key_press==Input_Dash){
        _sonido->Play_ambiente(2);
        esquivar(_direccion_actual); // Habra que pasar la direccion buena
        //setY(10);
    }

    else if(key_press==Input_Salto){
        saltar();
	}


    if(key_press==Input_Interact){
       _sonido->Stop_game();
        if(esta_bloqueado() == false){
            std::cout<< "Pulsa E\n";
            if(!interactuar_con_objeto()){
            std::cout<< "No encuentra objeto\n";
                intentar_recoger_arma();
            }
            //this->bloquear_input(1000);
            //std::cout<< "Interactuando..."<< std::endl;
        }
        else{
           // std::cout<< "No puede INTERACTUAR "<< std::endl;
        }
    }

///// ATAQUES ///// 

    if(key_press==Input_Ataque_Especial) {    // Ataque especial
            atacar(Ataque_Especial);
            //std::cout << "Ataque Especial\n";
        }
    else if(key_press==Input_Ataque_Normal){      // Ataque normal
            atacar(Ataque_Normal);
            //std::cout << "Ataque Normal\n";
        }
    else if(key_press==Input_Ataque_Fuerte){                          // Ataque fuerte
            atacar(Ataque_Fuerte);
            //std::cout << "Ataque Fuerte\n";
        }


///// CAMBIO DE ARMAS /////

    if(key_press==Input_Arma_Izquierda) {
            cambiar_arma_seleccionada_a_la_anterior();
        }
    else if(key_press==Input_Arma_Derecha){
        cambiar_arma_seleccionada_a_la_siguiente();
    }
}


			
void Player_Online::render(){
  
}


void Player_Online::modificar_vida_en(short _i_vida){
	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida <= 0){
        morir();
    }
    else{
        _vida+=_i_vida;
    }
}

void Player_Online::danyar(short _danyo){
    danyar_comun(_danyo);
}

void Player_Online::set_vida(short _i_vida){
	_vida=_i_vida;
}
