#include "Consumible_Carne.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"

Consumible_Carne::Consumible_Carne(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 125){
    std::string str = "models/Consumibles/Carne/Carne.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    _id=_id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z,12);
    
    delete cstr;
}

Consumible_Carne::~Consumible_Carne(){
}

bool Consumible_Carne::usar(Character* _personaje){
    
    if(comprobar_colision(_personaje)){
        if(_personaje->puede_subir_vida_(_valor)){
			_personaje->modificar_vida_en(_valor);
            return true;
        }
    }
	return false;	
}
	
void Consumible_Carne::render(){

}