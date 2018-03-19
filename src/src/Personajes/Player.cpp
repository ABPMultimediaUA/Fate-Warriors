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
#include "../Respawn.h"

#include "../Motor_sonido/Interfaz_sonido.h"

#include "../Game.h"
#include "../Action_Manager.h"
#include "../Network/Cliente.h"
                                                                                                            //  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input, bool _es_jugador_online) : Character(_id, _i_x, _i_y, _i_z, 500, 0.25, 10, 15, Enum_Equipo_A)
                                                                {   
    _motor= Motor::Motor_GetInstance();
    _sonido= Interfaz_sonido::GetInstancia();
    //_tiempo = Time::Instance();
    //crear nodo de personaje del motor

    es_jugador_online = _es_jugador_online;                                                                
    if(!_es_jugador_online){
    const char* cstr  = "models/Personajes/Jugador/Personaje.obj";
   //     const char* cstr  = "models/Personajes/Enemigos/Enemigo.obj";
   
    _objeto_motor = new Objeto_Motor(this, E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,80);
    _motor->poner_camara_a_entidad(_objeto_motor);

    }
    else{
        const char* cstr  = "models/Personajes/Enemigos/Enemigo.obj";
    _objeto_motor = new Objeto_Motor(this, E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,80);
    }

    
    //_id_motor = _motor->crear_objeto(E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);
    //std::cout<<"X player: "<<_motor->getX(_id_motor);
    //std::cout<<"Z player: "<<_motor->getZ(_id_motor)<<std::endl;

    _input = _i_input;
    _motor->set_text_vida(_vida);
    _especial = 0;
    _puede_actualizar = true;
    //_sonido->Play_ambiente(2);
}

Player::~Player(){
}

void Player::update(){
    //std::cout<< "ACCION_ACTUAL: "<< _accion << "\n";
    if (_vida>0){

    gestion_acciones();

    // Esto hay que borrarlo
    Controles* controles = Controles::Instance();

    // Recoge si ha habido movimiento y la direccion de el mismo
    uint16_t _direccion;

    if(_input->get_mover(_direccion)){
        // Direccion buena con respecto de la camara
        uint16_t _direccion_buena = _direccion + Motor::Motor_GetInstance()->angulo_camara();
        while(_direccion_buena >= 360) _direccion_buena -= 360;
        mover(_direccion_buena);
        //s_sonido->Play_ambiente(2);
    }

    if(_input->get_dash()){
        _sonido->Play_ambiente(2);
        esquivar(_direccion); // Habra que pasar la direccion buena
    }

    if(_input->get_interactuar()){
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

    if(_input->get_centrar_camara()) {
        _motor->resetear_camara();
    }


    auto _cambio = _input->get_cambiar_arma();
    if(std::get<0>(_cambio)) {
        if(std::get<1>(_cambio))
            cambiar_arma_seleccionada_a_la_anterior();
        else
            cambiar_arma_seleccionada_a_la_siguiente();
    }

    auto _ataques = _input->get_atacar();

    if(std::get<0>(_ataques)) {
        if(std::get<1>(_ataques)) {    // Ataque especial
            atacar(Ataque_Especial);
            //std::cout << "Ataque Especial\n";
        }
        else if(std::get<2>(_ataques)){      // Ataque normal
            atacar(Ataque_Normal);
            //std::cout << "Ataque Normal\n";
        }
        else {                          // Ataque fuerte
            this->atacar(Ataque_Fuerte);
            //std::cout << "Ataque Fuerte\n";
        }
    }
  

    if(_input->get_saltar()){
        saltar();
	}

    if(esta_bloqueado() == false && !_input->get_mover(_direccion) && !_input->get_dash() && !_input->get_interactuar()
        && !std::get<0>(_ataques) && !_input->get_saltar() && _accion != Atacar && _accion != Saltar){
        set_accion(Nada);
    }
   
    //set level of detail del nivel
    Nivel* nivel=Nivel::nivel_instancia();
    nivel->nivel_set_lod(nivel->nivel_get_id_vertice(getX(),getZ()));
    //std::cout << "id vertice set lod: " <<nivel->nivel_get_id_vertice(getX(),getZ()) << std::endl;
    }
    else{
        //std::cout<<"sigo muerto" << std::endl;
        Respawn::posiciones_instancia()->comprobar_si_renace_y_renacer_personaje(this);
    }

}




void Player::update_online(){
    //std::cout<< "ACCION_ACTUAL: "<< _accion << "\n";
    	std::vector<Enum_Inputs> inputs;
    if (_vida>0){
     if(/*Motor::Motor_GetInstance()->motor_envia_inputs() &&*/  Cliente::getInstance()->_puede_actualizar){

    gestion_acciones();

    // Esto hay que borrarlo
    Controles* controles = Controles::Instance();

    // Recoge si ha habido movimiento y la direccion de el mismo
    uint16_t _direccion;

    if(_input->get_mover(_direccion)){
        // Direccion buena con respecto de la camara
        uint16_t _direccion_buena = _direccion + Motor::Motor_GetInstance()->angulo_camara();
        while(_direccion_buena >= 360) _direccion_buena -= 360;
        std::cout<< "me voy a mover desde el player \n";
        //s_sonido->Play_ambiente(2);
     //   mover(_direccion_buena, _tiempo->get_tiempo_desde_ultimo_update());
        if(!es_jugador_online){
            Cliente::getInstance()->send_desplazamiento(0,_direccion_buena,_tiempo->get_tiempo_desde_ultimo_update());
        }
        
    }
    

    if(_input->get_dash()){
  /*      _sonido->Play_ambiente(2);
        esquivar(_direccion); // Habra que pasar la direccion buena
        */
        if(!es_jugador_online){
        	inputs.push_back(Input_Dash);
        }
    }

    if(_input->get_interactuar()){
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

       if(!es_jugador_online){
        	inputs.push_back(Input_Interact);
       }

    }



    if(_input->get_centrar_camara()) {
        _motor->resetear_camara();
    }


    auto _cambio = _input->get_cambiar_arma();
    if(std::get<0>(_cambio)) {
        if(std::get<1>(_cambio)){
        	inputs.push_back(Input_Arma_Izquierda);
            cambiar_arma_seleccionada_a_la_anterior();
        }
        else{
        	inputs.push_back(Input_Arma_Derecha);
            cambiar_arma_seleccionada_a_la_siguiente();
        }
    }

    auto _ataques = _input->get_atacar();


    if(std::get<0>(_ataques)) {
        if(std::get<1>(_ataques)) {    // Ataque especial
         //   atacar(Ataque_Especial);
            inputs.push_back(Input_Ataque_Especial);
            std::cout << "Ataque Especial\n";
        }
        else if(std::get<2>(_ataques)){      // Ataque normal
         //   atacar(Ataque_Normal);
            inputs.push_back(Input_Ataque_Normal);
            std::cout << "Ataque Normal\n";
        }
        else {                          // Ataque fuerte
          //  this->atacar(Ataque_Fuerte);
            inputs.push_back(Input_Ataque_Fuerte);
            std::cout << "Ataque Fuerte\n";
        }
    }
  
//    Cliente::getInstance()->send_player_move (inputs, inputs.size());

    if(_input->get_saltar()){
        saltar();
        inputs.push_back(Input_Salto);
	}

    if(esta_bloqueado() == false && !_input->get_mover(_direccion) && !_input->get_dash() && !_input->get_interactuar()
        && !std::get<0>(_ataques) && !_input->get_saltar() && _accion != Atacar && _accion != Saltar){
        set_accion(Nada);
    }
   
    //set level of detail del nivel
    Nivel* nivel=Nivel::nivel_instancia();
    nivel->nivel_set_lod(nivel->nivel_get_id_vertice(getX(),getZ()));
    //std::cout << "id vertice set lod: " <<nivel->nivel_get_id_vertice(getX(),getZ()) << std::endl;
    
    if(inputs.size()>0){
     Cliente::getInstance()->send_player_move(inputs, inputs.size());
    }



    }
    }
    else{
        //std::cout<<"sigo muerto" << std::endl;
        Respawn::posiciones_instancia()->comprobar_si_renace_y_renacer_personaje(this);
    }
    //Cliente::getInstance()->send_desplazamiento(0,getX(),getZ());
    

}

void Player::comprobar_input(Enum_Inputs key_press){
        gestion_acciones();

    
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
            std::cout << "Ataque Especial\n";
        }
    else if(key_press==Input_Ataque_Normal){      // Ataque normal
            atacar(Ataque_Normal);
            std::cout << "Ataque Normallllll\n";
        }
    else if(key_press==Input_Ataque_Fuerte){                          // Ataque fuerte
            atacar(Ataque_Fuerte);
            std::cout << "Ataque Fuerte\n";
        }


///// CAMBIO DE ARMAS /////

    if(key_press==Input_Arma_Izquierda) {
            cambiar_arma_seleccionada_a_la_anterior();
        }
    else if(key_press==Input_Arma_Derecha){
        cambiar_arma_seleccionada_a_la_siguiente();
    }
}


			
void Player::render(){
  
}


void Player::modificar_vida_en(short _i_vida){
	if(_vida+_i_vida>_vida_maxima){
        _vida=_vida_maxima;
    }
    else if(_vida + _i_vida <= 0){
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