#include "Objeto.h"
#include "Interfaz/Matcher.h"

Objeto::Objeto(short id, float _i_x, float _i_y,float _i_z): _x(_i_x),_y(_i_y), _z(_i_z), _id(id), _borrar(false), _visible(true) {
	
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
/*
float Objeto::getX(){
	_x = _matcher->getPosition()._x;
	return _x;
}

float Objeto::getY(){
	_y = _matcher->getPosition()._y;
	return _y;
}

float Objeto::getZ(){
	_z = _matcher->getPosition()._z;
	return _z;
}
*/
void Objeto::set_borrar(){
	_borrar=true;
}


bool Objeto::get_borrar(){
	return _borrar;
}

Vector2 Objeto::get_vector(){
	return Vector2(_x, _z);
}

void Objeto::set_visible(bool _i_visible){
    _visible = _i_visible;
}

bool Objeto::get_visible(){
    return _visible;
}

short Objeto::get_id(){
    return _id;
}
