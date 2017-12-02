#include "Proyectil.h"
#include <iostream>

Proyectil::Proyectil(short _id, float _i_x, float _i_y, float _i_z) : Interactuable(_id, _i_x, _i_y, _i_z), _impacted(false){}

Proyectil::~Proyectil(){}


void Proyectil::set_direction(float _i_x, float _i_y, float _i_z){
	_directionx= _i_x;
	_directiony= _i_y;
	_directionz= _i_z;
}

void Proyectil::set_has_impacted(){
	_impacted=true;	
}

bool Proyectil::get_has_impacted(){
	return _impacted;
}