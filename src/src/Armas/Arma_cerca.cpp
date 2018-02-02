#include "Arma_cerca.h"
#include <iostream>

Arma_cerca::Arma_cerca(uint16_t _id, float _i_x, float _i_y, float _i_z,short _i_tipo, short _i_uses , short _i_frecuencia, short _i_rango) 
							: Arma(_id, _i_x, _i_y, _i_z, _i_uses, _i_tipo, _i_frecuencia, _i_rango){
}

Arma_cerca::~Arma_cerca(){

}

Character* Arma_cerca::usar(uint16_t _i_direccion){
	decrease_uses();
	return 0;
}

void Arma_cerca::render(){

}