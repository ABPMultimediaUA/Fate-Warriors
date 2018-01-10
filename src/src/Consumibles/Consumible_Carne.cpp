#include "Consumible_Carne.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../Interfaz/Motor.h"

Consumible_Carne::Consumible_Carne(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 125){
    std::string str = "models/Consumibles/Carne/Carne.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    _id=_id_motor = _motor->crearObjeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z);
}

Consumible_Carne::~Consumible_Carne(){
}

bool Consumible_Carne::usar(){
	return true;
}
	
void Consumible_Carne::render(){

}