/*
#include "Objeto_Estandar.h"
#include "Interfaz/Matcher.h"

Objeto_Estandar::Objeto_Estandar(short _id, float _i_x, float _i_y, float _i_z, char* ruta) : Objeto(_id, _i_x, _i_y, _i_z) {
     
}

Objeto_Estandar::Objeto_Estandar(short _id, float _i_x, float _i_y, float _i_z, char* ruta, char* modelo) : Objeto(_id, _i_x, _i_y, _i_z){
    _matcher = new Matcher(ruta, modelo, _i_x, _i_y,  _i_z, 10,false);
}

void Objeto_Estandar::update(){}

void Objeto_Estandar::render(){}

Objeto_Estandar::~Objeto_Estandar(){

}       
*/