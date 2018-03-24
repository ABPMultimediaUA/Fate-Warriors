#include "AD_Pistola.h"
#include <iostream>
#include "../Scriptor/Game_Scriptor.h"

AD_Pistola::AD_Pistola(uint16_t _id, float _i_x, float _i_y, float _i_z) 
: Arma_distancia(_id, _i_x, _i_y, _i_z, 
				Nombre_Arma_Pistola,
				10, 
				150, 
				90,
				20){

    const char* cstr  = "models/Armas/Pistola/Pistola.obj";
    //_id=_id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z,12);
    _objeto_motor = new Objeto_Motor(false, this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);

}

AD_Pistola::~AD_Pistola(){
	
}

Character* AD_Pistola::usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion){
	if(preparado_siguiente_ataque()){
		//obtener_mundo->anyadirbalapistola(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
		decrementar_usos();

		//Anadir trigger sonido
		return _objeto_motor->disparar(_i_objeto_origen,_i_direccion, _rango);
	}
	return 0;
}

void AD_Pistola::update(){
}


void AD_Pistola::render(){

}
