#include "Arma.h"

Arma::Arma(short _id, float _i_x, float _i_y, float _i_z, short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango) : Objeto(_id, _i_x, _i_y, _i_z), _uses(_i_uses) , _tipo(_i_tipo), _frecuencia(_i_frecuencia), _rango(_i_rango){
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

short Arma::get_uses(){
	return _uses;
}

short Arma::get_tipo(){
	return _tipo;
}