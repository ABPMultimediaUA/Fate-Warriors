#include "Consumible_Patata.h"

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"

Consumible_Patata::Consumible_Patata(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 500){
  const char* cstr = "Patatas";
  _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
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