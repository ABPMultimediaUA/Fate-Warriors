#include "AD_Bazooka.h"
#include <iostream>

AD_Bazooka::AD_Bazooka(short _id, float _i_x, float _i_y, float _i_z, short  _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango) : Arma_distancia(_id, _i_x, _i_y, _i_z, _i_tipo, _i_uses, _i_frecuencia, _i_rango){
}

AD_Bazooka::~AD_Bazooka(){
	
}

bool AD_Bazooka::usar(){
	if (decrease_uses()){
		return true;
	}

	return false;
}


void AD_Bazooka::update(){
}


void AD_Bazooka::render(){

}
