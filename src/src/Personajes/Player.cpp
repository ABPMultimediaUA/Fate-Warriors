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

#include "../Game.h"
#include "../Action_Manager.h"
//  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z, Input* _i_input) : Character(_id,_i_x, _i_y, _i_z, 15, 10000,10,15)
                                                                {   

    //_tiempo = Time::Instance();
    //crear nodo de personaje del motor
    _otro_tiempo = _tiempo->get_start();
    _tiempo_anterior = _tiempo->get_start();

    std::string str = "models/Personaje.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    _id_motor = _motor->crearObjeto(cstr, _i_x,0,_i_z);
    _motor->poner_camara_a_entidad(_id);
    
    std::cout<<"X player: "<<_motor->getX(_id_motor);
    std::cout<<"Z player: "<<_motor->getZ(_id_motor)<<std::endl;

    _input = _i_input;
}

Player::~Player(){

}

void Player::update(){
    // Procesa los inputs para poder utilizarlos
    _input->procesar_inputs();

    bucle_ataque();

    // Esto hay que borrarlo
    Controles* controles = Controles::Instance();


    // Recoge si ha habido movimiento y la direccion de el mismo
    uint16_t _direccion;

    if(_input->get_mover(_direccion)) {
        _motor->VelocidadDireccion(_id_motor,_direccion);
    }


    if(_input->get_interactuar()){
        std::cout<< "Pulsa E"<< std::endl;

        if(esta_bloqueado() == false){
            this->interactuar_con_objeto();
            this->bloquear_input(1000);
            std::cout<< "SÍ INTERACTUA ----------------------------------"<< std::endl;
        }
        else{
            std::cout<< "No puede INTERACTUAR "<< std::endl;
        }
        
        //std::cout<< "Tiempo actual: "<< this->_tiempo->get_current() << std::endl;
        //std::cout<< "Tiempo almacenado: "<< this->get_tiempo_inicio_bloqueado() << std::endl;
    }


    if(controles->estaPulsada(Input_key::Escape)){
      
        //interface->Interfaz_Apagar();
    }


    bool _atk_normal, _atk_fuerte;
    bool _atacar = _input->get_atacar(_atk_normal, _atk_fuerte);

    if(_atacar) {
        if(_atk_normal){
            this->atacar(Ataque_Normal);
        }

        if(_atk_fuerte){
            //std::cout<< "MOUSER" <<std::endl;
            //this->atacar(Ataque_Fuerte);
            danyar(0);
        }
    }
  

    if(_input->get_saltar()){
        _motor->saltar(_id_motor);
        //exit(0);
	}


    // En cuanto se agrege al Input se borrara de aqui
    // Deteccion del movimiento con mando
    /*
    sf::Joystick::update();
    if(sf::Joystick::isConnected(0)){
        float _x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float _y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

        // Minimo de movimiento de Joystick
        if(std::abs(_x) > 20 || std::abs(_y) > 20) {
            unsigned short _direccion = lib_math_angulo_2_puntos(_y, -_x, 0, 0);
            _motor->VelocidadDireccion(_id_motor,_direccion);
        }
    }
    */

   
    //set level of detail del nivel
    Nivel* nivel=Nivel::nivel_instancia();
    nivel->nivel_set_lod(nivel->nivel_get_id_vertice(getX(),getZ()));
        
  
    // Reinicia el procesado y lectura de inputs
    _input->reiniciar_inputs();
}
			
void Player::render(){
  
}
