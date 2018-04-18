#include "Consumible_Power_Up.h"

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"
#include "../Tiempo/Time.h"

Consumible_Power_Up::Consumible_Power_Up(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 0){
    _reloj = Time::Instance();
}

Consumible_Power_Up::~Consumible_Power_Up(){
}

bool Consumible_Power_Up::usar(Character* _i_personaje){
	return false;	
}

void Consumible_Power_Up::activar_tiempo(){
        _duracion_power_up = _reloj->get_current() + 5000;
}

bool Consumible_Power_Up::comprobar_tiempo_power_up(){
    if(_reloj->get_current() > _duracion_power_up){
        return true;
    }    
    return false;
}