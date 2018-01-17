#include "Player.h"
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


#include "../Game.h"
#include "../Action_Manager.h"
//  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input) : Character(_id, _i_x, _i_y, _i_z, 500, 1, 10, 15)
                                                                {   
    _motor= Motor::Motor_GetInstance();
    //_tiempo = Time::Instance();
    //crear nodo de personaje del motor

    const char* cstr  = "models/Personaje.obj";

    _objeto_motor =new Objeto_Motor(E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,80);
    
    //_id_motor = _motor->crear_objeto(E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);
    _motor->poner_camara_a_entidad(_objeto_motor);
    
    //std::cout<<"X player: "<<_motor->getX(_id_motor);
    //std::cout<<"Z player: "<<_motor->getZ(_id_motor)<<std::endl;

    _input = _i_input;
    _motor->set_text_vida(_vida);
    _especial = 0;

}

Player::~Player(){
}

void Player::update(){
    // Procesa los inputs para poder utilizarlos
    _input->procesar_inputs();

    gestion_acciones();

    // Esto hay que borrarlo
    Controles* controles = Controles::Instance();

    // Recoge si ha habido movimiento y la direccion de el mismo
    uint16_t _direccion;

    if(_input->get_mover(_direccion) && esta_bloqueado() == false) {
       // _motor->VelocidadDireccion(_id_motor, _direccion,_velocidad);
       
       _objeto_motor->VelocidadDireccion(_direccion,_velocidad,_tiempo->get_tiempo_desde_ultimo_update());
    }

    if(_input->get_dash()){
        esquivar(_direccion);
    }

    if(_input->get_interactuar()){
       
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

    if(_input->get_centrar_camara()) {
            _motor->resetear_camara();
    }


    if(controles->estaPulsada(Input_key::Escape)){
        _motor->apagar();
    }


    bool _atk_normal, _atk_fuerte;
    bool _atacar = _input->get_atacar(_atk_normal, _atk_fuerte);

    if(_atacar) {
        if(_atk_normal){
            atacar(Ataque_Normal);
        }

        if(_atk_fuerte){
            //std::cout<< "MOUSER" <<std::endl;
            this->atacar(Ataque_Fuerte);
            //danyar(1);
            
        }
    }
  

    if(_input->get_saltar()){
        saltar();

	}

   
    //set level of detail del nivel
    Nivel* nivel=Nivel::nivel_instancia();
    nivel->nivel_set_lod(nivel->nivel_get_id_vertice(getX(),getZ()));


    if(_input->get_pausa() && Time::Instance()->get_tiempo_inicio_pausa() > 250) {
        Game* _game = Game::game_instancia();
        _game->cambio_a_update_pausa();
    }
}
			
void Player::render(){
  
}


void Player::modificar_vida_en(short _i_vida){
	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida < 0){
        morir();
    }
    else{
        _vida+=_i_vida;
    }
    _motor->set_text_vida(_vida);
}

void Player::danyar(short _danyo){
    danyar_comun(_danyo);
    
    _motor->set_text_vida(_vida);
}

void Player::set_vida(short _i_vida){
	_vida=_i_vida;
    _motor->set_text_vida(_vida);
}

bool Player::puede_subir_especial(){
    if(_especial+1<3)
        return true;
    return false;
}

void Player::aumentar_especial(){
    _especial+=1;
}

void Player::disminuir_especial(){
    _especial-=1;
}