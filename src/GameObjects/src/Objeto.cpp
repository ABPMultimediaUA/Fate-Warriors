#include "Objeto.h"

Objeto::Objeto(short id, float _i_x, float _i_y,float _i_z): _objeto_x(_i_x),_objeto_y(_i_y), _objeto_z(_i_z), _id(id), _borrar(false) {}

Objeto::~Objeto() {}

void Objeto::setPosition(float _i_x, float _i_y, float _i_z){
	_objeto_x=_i_x;
	_objeto_y=_i_y;
	_objeto_z=_i_z;
}

void Objeto::setX(float _i_x){
	_objeto_x = _i_x;
}

void Objeto::setY(float _i_y){
	_objeto_y = _i_y; 
}

void Objeto::setZ(float _i_z){
	_objeto_z = _i_z; 
}

float Objeto::getX(){
	return _objeto_x;
}

float Objeto::getY(){
	return _objeto_y;
}

float Objeto::getZ(){
	return _objeto_z;
}

bool Objeto::get_borrar(){
	return _borrar;
}