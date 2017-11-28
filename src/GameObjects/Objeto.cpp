#include "Objeto.h"

Objeto::Objeto(float _i_x, float _i_y,float _i_z, float _i_ancho, float _i_alto): _objeto_x(_i_x),
_objeto_y(_i_y), _objeto_z(_i_z), _objeto_ancho(_i_ancho), _objeto_alto(_i_alto) {
	
}

Objeto::~Objeto() {
}

void Objeto::setPosition(float _i_x, float _i_y, float _i_z){
	_objeto_x=_i_x;
	_objeto_y=_i_y;
}

float Objeto::getX(){
	return _objeto_x;
}

float Objeto::getY(){
	return _objeto_y;
}

float Objeto::get_widht(){
	return _objeto_ancho;
}

float Objeto::get_height(){
	return _objeto_alto;
}

/*
Modelado Objeto::get_Modelado(){
	return _modelo;
}
*/