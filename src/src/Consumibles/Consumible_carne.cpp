#include "Consumible_carne.h"
#include <iostream>

Consumible_carne::Consumible_carne(short _id, float _i_x, float _i_y, float _i_z, short vida) : Consumible(_id,_i_x, _i_y, _i_z, vida){
}

Consumible_carne::~Consumible_carne(){
}

bool Consumible_carne::usar(){
	
	return true;
}
	
void Consumible_carne::render(){

}