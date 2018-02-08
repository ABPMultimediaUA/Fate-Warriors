#include "AD_Arco.h"
#include <iostream>
#include "../Scriptor/Game_Scriptor.h"


AD_Arco::AD_Arco(uint16_t _id, float _i_x, float _i_y, float _i_z) 
: Arma_distancia(_id, _i_x, _i_y, _i_z, 
				Nombre_Arma_Arco, 
				script->Dame_valor_de("Arco_usos"), 
				script->Dame_valor_de("Arco_frecuencia"), 
				script->Dame_valor_de("Arco_rango")){}

AD_Arco::~AD_Arco(){
	
}

Character* AD_Arco::usar(uint16_t _i_direccion){
	if(preparado_siguiente_ataque()){
		//obtener_mundo->anyadirbaflecha(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
		decrementar_usos();

		//Anadir trigger sonido
		return _objeto_motor->disparar(_i_direccion, _rango);
	}
	return 0;
}


void AD_Arco::render(){

}
