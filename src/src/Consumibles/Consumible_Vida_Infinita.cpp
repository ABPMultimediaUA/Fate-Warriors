#include "Consumible_Vida_Infinita.h"

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"
#include "../Tiempo/Time.h"

Consumible_Vida_Infinita::Consumible_Vida_Infinita(short _id, float _i_x, float _i_y, float _i_z) : Consumible_Power_Up(_id,_i_x, _i_y, _i_z){
    const char* cstr  = "models/Consumibles/Carne/Carne.obj";
    
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    _personaje = nullptr;

}

Consumible_Vida_Infinita::~Consumible_Vida_Infinita(){
}

bool Consumible_Vida_Infinita::usar(Character* _i_personaje){
    if(_personaje!=nullptr){
        if(comprobar_tiempo_power_up()){
            _personaje->desactivar_inmunidad_a_danyos();
            _personaje->eliminar_power_up_puntero();
          return true;
        }
        std::cout << "Vida infinita \n";
    }
    else{
        if(comprobar_colision(_i_personaje)){
            activar_tiempo();
            _personaje=_i_personaje;
            _personaje->activar_inmunidad_a_danyos();
          _personaje->anyadir_power_up(this);
            setY(-50);
        }
    }
	return false;	
}

void Consumible_Vida_Infinita::activar_tiempo(){
        _duracion_power_up = _reloj->get_current() + 5000;
}

bool Consumible_Vida_Infinita::comprobar_tiempo_power_up(){
    if(_reloj->get_current() > _duracion_power_up){
        return true;
    }    
    return false;
}


void Consumible_Vida_Infinita::cambiar_modelado(){
    if(!_esta_lejos){
        _esta_lejos=true;
    }else{
        _esta_lejos=false;
    }

}