#include "Arma.h"

Arma::Arma(uint16_t _id, float _i_x, float _i_y, float _i_z, Enum_Nombre_Arma _i_tipo, uint8_t _i_uses, uint8_t _i_frecuencia, uint8_t _i_rango, uint8_t _i_danyo) 

: Objeto(_id, _i_x, _i_y, _i_z), 
_uses(_i_uses) , 
_nombre(_i_tipo), 
_frecuencia(_i_frecuencia),
 _rango(_i_rango),
 _reloj(Time::Instance()){
 _tiempo_siguiente_disponible = 0;
}

Arma::~Arma() {
}

bool Arma::preparado_siguiente_ataque(){
	if(_reloj->get_current() > _tiempo_siguiente_disponible){
		return true;
	}
	return false;
}


void Arma::decrementar_usos(){
	_uses--;

}

void Arma::actualizar_tiempo_siguiente_ataque(){
	_tiempo_siguiente_disponible = _reloj->get_current() + 1.0/_frecuencia;
}

short Arma::get_uses(){
	return _uses;
}


Enum_Nombre_Arma Arma::get_nombre(){
	return _nombre;

}

short Arma::get_frecuencia(){
	return _frecuencia;
}

short Arma::get_rango(){
	return _rango;
}