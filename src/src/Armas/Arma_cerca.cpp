#include "Arma_cerca.h"
#include <iostream>

Arma_cerca::Arma_cerca(short _id, float _i_x, float _i_y, float _i_z,short _i_tipo, short _i_uses , short _i_frecuencia, short _i_rango) 
							: Arma(_id, _i_x, _i_y, _i_z, _i_uses, _i_tipo, _i_frecuencia, _i_rango){
}

Arma_cerca::~Arma_cerca(){

}

bool Arma_cerca::usar(float x, float y, float z){
	decrease_uses();
	return true;
}

void Arma_cerca::render(){

}