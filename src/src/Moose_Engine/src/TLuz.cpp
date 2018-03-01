#include "TLuz.h"
#include <iostream>

TLuz::TLuz(){}
TLuz::~TLuz(){}
void TLuz::beginDraw(Shader* _i_shader){

    std::cout<<"ID ------"<<_ID<<"\n";
}
void TLuz::endDraw(){
    std::cout<<"termino dibujar "<<_ID<<"\n";
}

void TLuz::setActiva(bool activa){
    _activa = activa;
}