#include "Objeto.h"

Objeto::Objeto(short id, float _i_x, float _i_y,float _i_z): _x(_i_x),_y(_i_y), _z(_i_z), _id(id), _borrar(false) {
	
}

Objeto::~Objeto() {
}

void Objeto::setPosition(float _i_x, float _i_y, float _i_z){
    _x=_i_x;
    _y=_i_y;
    _z=_i_z;
}


void Objeto::setX(float _i_x){
	_x = _i_x;
}

void Objeto::setY(float _i_y){
	_y = _i_y; 
}

void Objeto::setZ(float _i_z){
	_z = _i_z; 
}

float Objeto::getX(){
	return _x;
}

float Objeto::getY(){
	return _y;
}

float Objeto::getZ(){
	return _z;
}


bool Objeto::get_borrar(){
	return _borrar;
}


Vector2 Objeto::get_vector(){
	return Vector2(_x, _z);
}