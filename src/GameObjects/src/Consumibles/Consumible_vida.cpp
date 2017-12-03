#include "Consumible_vida.h"
#include <iostream>

Consumible_vida::Consumible_vida(short _id, float _i_x, float _i_y, float _i_z, short vida) : Consumible(_id,_i_x, _i_y, _i_z, vida){
}

Consumible_vida::~Consumible_vida(){
}

bool Consumible_vida::usar(){
	
	return true;
}

void Consumible_vida::update(){

}
			
void Consumible_vida::render(){

}