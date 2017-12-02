#include "AD_Arco.h"
#include <iostream>

AD_Arco::AD_Arco(short _id, float _i_x, float _i_y, float _i_z, short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango) : Arma_distancia(_id, _i_x, _i_y, _i_z, _i_tipo, _i_uses, _i_frecuencia, _i_rango){
}

AD_Arco::~AD_Arco(){
	
}

bool AD_Arco::usar(){
	if (decrease_uses()){
		return true;
	}

	return false;
}


void AD_Arco::update(){
}


void AD_Arco::render(){

}
