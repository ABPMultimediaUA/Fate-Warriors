#include "AD_Bazooka.h"
#include <iostream>
#include "../Scriptor/Game_Scriptor.h"

AD_Bazooka::AD_Bazooka(uint16_t _id, float _i_x, float _i_y, float _i_z) : 
Arma_distancia(_id, _i_x, _i_y, _i_z, 
				Nombre_Arma_Bazooka, 
				script->Dame_valor_de("Bazooka_usos"), 
				script->Dame_valor_de("Bazooka_frecuencia"), 
				script->Dame_valor_de("Bazooka_rango"),
				20){}

AD_Bazooka::~AD_Bazooka(){
	
}

Character* AD_Bazooka::usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion){
	if(preparado_siguiente_ataque()){
		//obtener_mundo->anyadirbalabazooka(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
		decrementar_usos();
		//Anadir trigger sonido
		return _objeto_motor->disparar(_i_objeto_origen,_i_direccion, _rango);
	}
	return 0;
}

void AD_Bazooka::render(){

}
