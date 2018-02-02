#include "Arma_distancia.h"
#include <iostream>
//#include <list>

Arma_distancia::Arma_distancia(uint16_t _id, float _i_x, float _i_y, float _i_z, short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango) : Arma(_id, _i_x, _i_y, _i_z, _i_tipo, _i_uses, _i_frecuencia, _i_rango){
}

Arma_distancia::~Arma_distancia(){
	
}

Character* Arma_distancia::usar(uint16_t _i_direccion){
	if (decrease_uses()){
		return 0;
	}

	return 0;
}

void Arma_distancia::render(){

}
