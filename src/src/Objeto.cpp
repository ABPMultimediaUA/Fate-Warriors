#include "Objeto.h"
//#include "Interfaz/Objeto_Motor.h"


Objeto::Objeto(short id, float _i_x, float _i_y,float _i_z): _id(id), _borrar(false), _visible(true) {
}

Objeto::~Objeto() {
	delete _objeto_motor;
}

void Objeto::setPositionXZ(float _i_x, float _i_z){
    _objeto_motor->setPositionXZ(_i_x,_i_z);
}

void Objeto::setX(float _i_x){

}

void Objeto::setY(float _i_y){

}

void Objeto::setZ(float _i_z){

}

void Objeto::haz_desaparecer(){
//	_motor->haz_desaparecer(_id_motor);
}

float Objeto::getX(){
	return(_objeto_motor->getX());
}

float Objeto::getY(){
	return(_objeto_motor->getY());
}

float Objeto::getZ(){
	return(_objeto_motor->getZ());
}

void Objeto::set_borrar(){
	_borrar=true;
}


bool Objeto::get_borrar(){
	return _borrar;
}

Vector2 Objeto::get_vector(){
	return Vector2(_objeto_motor->getX(), _objeto_motor->getZ()); 
}

void Objeto::set_visible(bool _i_visible){
    _visible = _i_visible;

	if(_i_visible == false){
		setPositionXZ(10000, 10000);
	}
}

bool Objeto::get_visible(){
    return _visible;
}

short Objeto::get_id(){
    return _id;
}
