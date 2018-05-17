#include "Consumible_Carne.h"

#include "../Personajes/Character.h"
#include "../Interfaz/Motor.h"

#include "../Motor_sonido/Interfaz_sonido.h"


Consumible_Carne::Consumible_Carne(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 1000){
    const char* cstr  = "Carne";
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    _sonido= Interfaz_sonido::GetInstancia();
}

Consumible_Carne::~Consumible_Carne(){
}

bool Consumible_Carne::usar(Character* _personaje){
    
    if(comprobar_colision(_personaje)){
        if(_personaje->puede_subir_vida_(_valor)){
			_personaje->modificar_vida_en(_valor);
            _sonido->Play_consumibles(0);
            return true;
        }
    }
	return false;	
}
