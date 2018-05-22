#include "Consumible.h"

#include "../Personajes/Character.h"
#include "../Tiempo/Time.h"


Consumible::Consumible(short _id, float _i_x, float _i_y, float _i_z, short _i_valor) : Objeto(_id, _i_x, _i_y, _i_z), _valor(_i_valor), tiempo_espera(0), _reloj(Time::Instance()){
}

Consumible::~Consumible() {
}

bool Consumible::comprobar_colision(Character *_character){
	Vector2 vec_player	= _character->get_vector();
    Vector2 vec_cons	= this->get_vector();

    if(ha_pasado_tiempo_suficiente() && comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_cons, 2)){
		return true;
	}
	return false;
}

short Consumible::get_valor(){
	return _valor;
}

void Consumible::set_tiempo_espera(){
	tiempo_espera = _reloj->get_current()+3000;	
}

bool Consumible::ha_pasado_tiempo_suficiente(){
	if(_reloj->get_current() > tiempo_espera){
		return true;
	}
	return false;
}