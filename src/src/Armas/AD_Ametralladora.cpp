#include "AD_Ametralladora.h"
#include <iostream>

#include <stdio.h>
#include <string.h>

#include "../Interfaz/Motor.h"


AD_Ametralladora::AD_Ametralladora(short _id, float _i_x, float _i_y, float _i_z) : Arma_distancia(_id, _i_x, _i_y, _i_z, 0, 60, 10, 20){
    std::string str = "models/Armas/Ametralladora/Ametralladora.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    //_id=_id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z,12);
	    
    _objeto = new Objeto_Motor(E_BoundingCapsule, cstr, _i_x,_i_y,_i_z,69);
    _id_motor = _objeto->getId();
    
    delete cstr;
}

AD_Ametralladora::~AD_Ametralladora(){
	
}

void AD_Ametralladora::update(){
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
