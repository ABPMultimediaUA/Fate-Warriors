#include "P_Pistola.h"
#include <iostream>

P_Pistola::P_Pistola(short _id, float _i_x, float _i_y, float _i_z, short _i_danyo, short _i_id_shooter) 
: Proyectil(_id, _i_x, _i_y, _i_z, _i_danyo, _id_shooter){}

P_Pistola::~P_Pistola(){}


void P_Pistola::Update(){

}

void P_Pistola::Render(){

}