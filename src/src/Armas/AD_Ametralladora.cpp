#include "AD_Ametralladora.h"
#include <iostream>

#include <stdio.h>
#include <string.h>

#include "../Interfaz/Motor.h"


AD_Ametralladora::AD_Ametralladora(uint16_t _id, float _i_x, float _i_y, float _i_z) : Arma_distancia(_id, _i_x, _i_y, _i_z, Nombre_Arma_Ametralladora, 10, 10, 20,20){
    const char* cstr  = "models/Armas/Ametralladora/Ametralladora.obj";
    _objeto_motor = new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
}

AD_Ametralladora::~AD_Ametralladora(){
}

Character* AD_Ametralladora::usar(Objeto_Motor* _i_objeto_origen, uint16_t _i_direccion){
	if(preparado_siguiente_ataque()){
		decrementar_usos();
		//obtener_mundo->anyadirbalametralladora(_i_x,_i_y,_i_z);
		actualizar_tiempo_siguiente_ataque();
			
		//Anadir trigger sonido
		return _objeto_motor->disparar(_i_objeto_origen,_i_direccion, _rango);
	}
	return 0;
}