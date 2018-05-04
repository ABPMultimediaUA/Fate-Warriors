#include "Consumible_Patata.h"

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"

#include "../Motor_sonido/Interfaz_sonido.h"

Consumible_Patata::Consumible_Patata(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 500){
  const char* cstr = "Patatas";
  _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
  _sonido= Interfaz_sonido::GetInstancia();
}

Consumible_Patata::~Consumible_Patata(){
}

bool Consumible_Patata::usar(Character* _personaje){
    
    if(comprobar_colision(_personaje)){
        if(_personaje->puede_subir_vida_(_valor)){
			_personaje->modificar_vida_en(_valor);
            _sonido->Play_consumibles(2);
            return true;
        }
    }
	return false;	
}


void Consumible_Patata::cambiar_modelado(){
    if(!_esta_lejos){
        const char* cstr  = "Patatas_low";
        _objeto_motor->cambiar_modelado(cstr, 0);
        _esta_lejos=true;
    }else{
        const char* cstr  = "Patatas";
        _objeto_motor->cambiar_modelado(cstr, 0);
        _esta_lejos=false;
    }
}