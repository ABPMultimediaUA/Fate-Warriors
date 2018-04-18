#include "Consumible_Agua.h"

#include "../Personajes/Player.h"
#include "../Interfaz/Motor.h"

Consumible_Agua::Consumible_Agua(short _id, float _i_x, float _i_y, float _i_z) : Consumible(_id,_i_x, _i_y, _i_z, 1){
    const char* cstr = "Agua";
    
    _objeto_motor =new Objeto_Motor(this, E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);

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