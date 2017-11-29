#include "Bala.h"
#include <iostream>

Bala::Bala(short _id, float _i_x, float _i_y, float _i_z,  float _i_ancho, float _i_alto) : Interactuable(_id, _i_x, _i_y, _i_z,  _i_ancho, _i_alto){
	std::cout << "Bala" << std::endl;
	_activated = false;
	_collision = false;

}

Bala::~Bala(){

}

void Bala::render(){

}

void Bala::update(){
	//Avanzar hacia la direccion a a la que dispara
}


void Bala::set_direction(float _i_x, float _i_y, float _i_z){
	_directionx= _i_x;
	_directiony= _i_y;
	_directionz= _i_z;
}


/*Devuelve true cuando explota*/
bool Bala::usar(){
	_activated = true;
	return true;
}

void Bala::set_collision(){
	_collision=true;	
}

bool Bala::get_state(){
	return _activated;
}


bool Bala::get_collision(){
	return _collision;
}