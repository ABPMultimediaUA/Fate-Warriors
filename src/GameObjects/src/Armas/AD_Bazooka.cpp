#include "AD_Bazooka.h"
#include <iostream>
#include "../Scriptor/Game_Scriptor.h"

AD_Bazooka::AD_Bazooka(short _id, float _i_x, float _i_y, float _i_z) : 
Arma_distancia(_id, _i_x, _i_y, _i_z, 
				script->Dame_valor_de("Bazooka_tipo"), 
				script->Dame_valor_de("Bazooka_usos"), 
				script->Dame_valor_de("Bazooka_frecuencia"), 
				script->Dame_valor_de("Bazooka_rango")){}

AD_Bazooka::~AD_Bazooka(){
	
}

bool AD_Bazooka::usar(float _i_x, float _i_y, float _i_z){
	if(preparado_siguiente_ataque()){
		//obtener_mundo->anyadirbalabazooka(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
		//Anadir trigger sonido
		return true;
	}
	return false;
}


void AD_Bazooka::update(){
}


void AD_Bazooka::render(){

}
