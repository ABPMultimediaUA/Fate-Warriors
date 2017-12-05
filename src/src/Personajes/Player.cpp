#include "Player.h"
#include <iostream>
#include "../Entrada/Input.h"
#include "../Entrada/Controles.h"
#include "../Interfaz/Interfaz.h"
#include "../Camara/Camara.h"
#include "../Tiempo/Time.h"
                                                                                              //  vida_prota, velocidad
Player::Player(short _id, float _i_x, float _i_y, float _i_z) : Character(_id,_i_x, _i_y, _i_z, 15, 175) 
                                                                ,_interface(Interfaz::Interfaz_getInstance())
                                                                {
    _tiempo = Time::Instance();
    //std::cout<<"eso: "<<_interface<<std::endl;
    //crear nodo de personaje del motor
    _otro_tiempo = _tiempo->get_start();
    _tiempo_anterior = _tiempo->get_start();

   _nodoId = _interface->Interfaz_crearProtaZip("models/Personaje.zip", "Personaje.obj",false,
                        _i_x,_i_y,_i_z);
}

Player::~Player(){
}

void Player::update(){
    
    Controles* controles = Controles::Instance();
    Interfaz* interface = Interfaz::Interfaz_getInstance();
    if(interface!=nullptr){
        
        float direccionX = interface->Interfaz_getCamara()->Camara_getDirection().X;
        float direccionY = interface->Interfaz_getCamara()->Camara_getDirection().Y;
        float direccionZ = interface->Interfaz_getCamara()->Camara_getDirection().Z;
        
        float miX = interface->Interfaz_GetNode(_nodoId)->getPosition().X;
        float miZ = interface->Interfaz_GetNode(_nodoId)->getPosition().Z;

        _otro_tiempo = _tiempo->get_current();


        double _time = _tiempo->get_tiempo_desde_ultimo_update_segundos();

        std::cout << "Direccion X " << direccionX << std::endl;
        std::cout << "Direccion Z " << direccionZ << std::endl;

        if(controles->estaPulsada(Input_key::W)){
            miZ += direccionZ * _velocidad * _time;
            miX += direccionX * _velocidad * _time;
        }
        
        if(controles->estaPulsada(Input_key::S)){
            miZ -= direccionZ * _velocidad * _time;
            miX -= direccionX * _velocidad * _time;
        }

        if(controles->estaPulsada(Input_key::A)){
            miZ -= -direccionX * _velocidad * _time; 
            miX -=  direccionZ * _velocidad * _time;
        }

        if(controles->estaPulsada(Input_key::D)){
            miZ += -direccionX * _velocidad * _time;
            miX +=  direccionZ * _velocidad * _time;
        }

        if(controles->estaPulsada(Input_key::Escape)){
            interface->Interfaz_Apagar();
        }

        setX(miX);
        setZ(miZ);
        interface->Interfaz_moverProta(miX, miZ);

        _tiempo_anterior = _otro_tiempo;
  }
}
			
void Player::render(){
  
}