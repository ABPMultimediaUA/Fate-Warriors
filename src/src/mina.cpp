#include "mina.h"
#include <iostream>

Mina::Mina(float _i_x, float _i_y, float _i_ancho, float _i_alto, int _i_id) : Interactuable(_i_x, _i_y, _i_ancho, _i_alto,  _i_id){
	_activated = true;
	_id = 0;
	_time_out=0;
	std::cout << "mina" << std::endl;
}

Mina::~Mina(){

}

bool Mina::explote(){
	if(_time_out>0){
		_time_out--;
		return false;
	}
	return true;		//Couter value is 0
}

bool Mina::usar(){
	_activated = true;
	return true;
}

