#include "Consumible_Patata.h"
#include "../Personajes/Character.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../Interfaz/Motor.h"

Consumible_Patata::Consumible_Patata(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 50){
    std::string str = "models/Consumibles/Patata/Patatas.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    _id=_id_motor = _motor->crearObjeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z);
    
    delete cstr;
}

Consumible_Patata::~Consumible_Patata(){
}

bool Consumible_Patata::usar(Character* _personaje){
    
    if(comprobar_colision(_personaje)){
        if(_personaje->puede_subir_vida_(_valor)){
			_personaje->modificar_vida_en(_valor);
            return true;
        }
    }
	return false;	
}


void Consumible_Patata::render(){

}