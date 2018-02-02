#include "Arma.h"

Arma::Arma(uint16_t _id, float _i_x, float _i_y, float _i_z, short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango) 
: Objeto(_id, _i_x, _i_y, _i_z), 
_uses(_i_uses) , 
_tipo(_i_tipo), 
_frecuencia(_i_frecuencia),
 _rango(_i_rango),
 _reloj(Time::Instance()){
 _tiempo_siguiente_disponible = 0;
}

Arma::~Arma() {
}

bool Arma::decrease_uses(){
	if(_uses>0){
		_uses--;
		return true;
	}
	return false;
}

bool Arma::preparado_siguiente_ataque(){
	if(_reloj->get_current() > _tiempo_siguiente_disponible){
		return true;
	}
	return false;
}

void Arma::actualizar_tiempo_siguiente_ataque(){
	_tiempo_siguiente_disponible = _reloj->get_current() + 1.0/_frecuencia;
}

short Arma::get_uses(){
	return _uses;
}

short Arma::get_tipo(){
	return _tipo;
}

short Arma::get_frecuencia(){
	return _frecuencia;
}

short Arma::get_rango(){
	return _rango;
}