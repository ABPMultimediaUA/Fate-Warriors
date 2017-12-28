#include "Enemy.h"
#include <iostream>
#include "../Entrada/Input.h"
#include "../Entrada/Controles.h"
#include "../Interfaz/Motor.h"

#include "../Tiempo/Time.h"
                                                                                              //  vida_prota, velocidad 
Enemy::Enemy(short _id, float _i_x, float _i_y, float _i_z) : Character(_id,_i_x, _i_y, _i_z, 15, 2) 
                                                                ,_motor(Motor::Motor_GetInstance())
                                                                {

    _tiempo = Time::Instance();
   //_nodoId = _interface->Interfaz_cargaCaja(_i_x,_i_y,_i_z);
    //std::cout<<"eso: "<<_interface<<std::endl;
    //crear nodo de personaje del motor
}

Enemy::~Enemy(){
}

void Enemy::update(){
    //Interfaz* interface = Interfaz::Interfaz_getInstance();
    if(_interface!=nullptr){
       // float miX = _interface->Interfaz_GetNode(_nodoId)->getPosition().X;
        //float miY = getY();
       // float miZ = _interface->Interfaz_GetNode(_nodoId)->getPosition().Z;
        float miX = 0;
        float miZ = 0;
        
        float speed = 5.f;
     //   _tiempo->updateAhora();
    //  double deltaTime = _tiempo->getDeltaTime();

        //setPosition(miX, miY, miZ);
        setX(miX);
        setZ(miZ);
       // _interface->Interfaz_moverProta(miX, miZ);
      //  _tiempo->set_start_time();
        
        //PA ACTUALISAH
       // _interface->Interfaz_moverModelo(_variable_modelo,miX,miX,miZ);
  }
}
			
void Enemy::render(){
  
}