#include "Consumible_Agua.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../Personajes/Player.h"
#include "../Interfaz/Motor.h"

Consumible_Agua::Consumible_Agua(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 1){
    std::string str = "models/Consumibles/Agua/Agua.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    _id=_id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z,12);
    
    delete cstr;
}

Consumible_Agua::~Consumible_Agua(){
}

bool Consumible_Agua::usar(Character* _personaje){

    if(comprobar_colision(_personaje)){
        Player *_player = static_cast<Player*>(_personaje);
        if(_player->puede_subir_especial()){
            _player->aumentar_especial();
            return true;
        }
    }
    	return false;	
}
	
void Consumible_Agua::render(){

}