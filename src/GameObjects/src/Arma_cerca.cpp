#include "Arma_cerca.h"
#include <iostream>

Arma_cerca::Arma_cerca(short _id, float _i_x, float _i_y, float _i_z, float _i_ancho, float _i_alto, short _i_uses) : Arma(_id, _i_x, _i_y, _i_z,_i_ancho, _i_alto, _i_uses){
}

Arma_cerca::~Arma_cerca(){

}

bool Arma_cerca::usar(){
	//Comprobar colision
	decrease_uses();
	return true;
}

void Arma_cerca::update(){

}


void Arma_cerca::render(){

}