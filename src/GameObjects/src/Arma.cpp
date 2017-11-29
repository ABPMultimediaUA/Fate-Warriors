#include "Arma.h"

Arma::Arma(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_uses) : Objeto(_id, _i_x, _i_y, _i_z, _i_ancho, _i_alto){
	_uses = _i_uses;
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