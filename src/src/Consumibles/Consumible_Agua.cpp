#include "Consumible_Agua.h"

#include "../Personajes/Player.h"
#include "../Interfaz/Motor.h"

#include "../Motor_sonido/Interfaz_sonido.h"


Consumible_Agua::Consumible_Agua(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 1){
    const char* cstr = "Agua";
    _objeto_motor =new Objeto_Motor(this, E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    _sonido= Interfaz_sonido::GetInstancia();

}

Consumible_Agua::~Consumible_Agua(){
}

bool Consumible_Agua::usar(Character* _personaje){

    if(comprobar_colision(_personaje)){
        Player *_player = static_cast<Player*>(_personaje);
        if(_player->puede_subir_especial()){
            _player->aumentar_especial();
            _sonido->Play_consumibles(1);
            return true;
        }
    }
    	return false;	
}


void Consumible_Agua::cambiar_modelado(){
    if(!_esta_lejos){
        const char* cstr  = "Agua_low";
        _objeto_motor->cambiar_modelado(cstr, 0);
        _esta_lejos=true;
    }else{
        const char* cstr  = "Agua";
        _objeto_motor->cambiar_modelado(cstr, 0);
        _esta_lejos=false;
    }
}