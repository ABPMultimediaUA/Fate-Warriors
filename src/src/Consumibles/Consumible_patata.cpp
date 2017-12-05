#include "Consumible_patata.h"
#include <iostream>

Consumible_patata::Consumible_patata(short _id, float _i_x, float _i_y, float _i_z, short vida) : Consumible(_id,_i_x, _i_y, _i_z, vida){
}

Consumible_patata::~Consumible_patata(){
}

bool Consumible_patata::usar(){
	
	return true;
}


void Consumible_patata::render(){

}