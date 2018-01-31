#include "P_Ametralladora.h"
#include <iostream>

P_Ametralladora::P_Ametralladora(uint16_t _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter) 
: Proyectil(_id, _i_x, _i_y, _i_z, _i_danyo, _id_shooter){}

P_Ametralladora::~P_Ametralladora(){}


void P_Ametralladora::Update(){

}

void P_Ametralladora::Render(){

}