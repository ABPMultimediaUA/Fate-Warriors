#include "AD_Ametralladora.h"
#include <iostream>

																								///short _i_tipo, short _i_uses, short _i_frecuencia, short _i_rango
AD_Ametralladora::AD_Ametralladora(short _id, float _i_x, float _i_y, float _i_z) : Arma_distancia(_id, _i_x, _i_y, _i_z, 1, 50, 200, 1){
}

AD_Ametralladora::~AD_Ametralladora(){
	
}

bool AD_Ametralladora::usar(float _i_x, float _i_y, float _i_z){
	if(preparado_siguiente_ataque()){
		//obtener_mundo->anyadirbalametralladora(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
		//Anadir trigger sonido
		return true;
	}
	return false;
}


void AD_Ametralladora::render(){

}
