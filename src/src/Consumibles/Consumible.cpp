#include "Consumible.h"

#include "../Personajes/Character.h"

Consumible::Consumible(short _id, float _i_x, float _i_y, float _i_z, short _i_valor) : Objeto(_id, _i_x, _i_y, _i_z), _valor(_i_valor){
}

Consumible::~Consumible() {
}

bool Consumible::comprobar_colision(Character *_character){
	Vector2 vec_player	= _character->get_vector();
    Vector2 vec_cons	= this->get_vector();

    if(comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_cons, 2)){
		return true;
	}
	return false;
}

short Consumible::get_valor(){
	return _valor;
}