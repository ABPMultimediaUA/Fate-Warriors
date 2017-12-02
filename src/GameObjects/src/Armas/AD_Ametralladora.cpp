#include "AD_Ametralladora.h"
#include <iostream>

AD_Ametralladora::AD_Ametralladora(short _id, float _i_x, float _i_y, float _i_z, short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango) : Arma_distancia(_id, _i_x, _i_y, _i_z, _i_tipo, _i_uses, _i_frecuencia, _i_rango){
}

AD_Ametralladora::~AD_Ametralladora(){
	
}

bool AD_Ametralladora::usar(){
	if (decrease_uses()){
		return true;
	}

	return false;
}


void AD_Ametralladora::update(){
}


void AD_Ametralladora::render(){

}
