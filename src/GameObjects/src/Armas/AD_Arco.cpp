#include "AD_Arco.h"
#include <iostream>
#include "../Scriptor/Game_Scriptor.h"


AD_Arco::AD_Arco(short _id, float _i_x, float _i_y, float _i_z) 
: Arma_distancia(_id, _i_x, _i_y, _i_z, 
				script->Dame_valor_de("Arco_tipo"), 
				script->Dame_valor_de("Arco_usos"), 
				script->Dame_valor_de("Arco_frecuencia"), 
				script->Dame_valor_de("Arco_rango")){}

AD_Arco::~AD_Arco(){
	
}

bool AD_Arco::usar(float _i_x, float _i_y, float _i_z){
	if(preparado_siguiente_ataque()){
		//obtener_mundo->anyadirbaflecha(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
		//Anadir trigger sonido
		return true;
	}
	return false;
}


void AD_Arco::update(){
}


void AD_Arco::render(){

}
