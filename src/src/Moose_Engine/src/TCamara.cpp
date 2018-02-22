#include "TCamara.h"
#include <iostream>

TCamara::TCamara(){}
TCamara::~TCamara(){}
void TCamara::beginDraw(){
    std::cout<<"ID ------"<<_ID<<"\n";
}
void TCamara::endDraw(){
    std::cout<<"termino dibujar "<<_ID<<"\n";
}

void TCamara::setActiva(bool activa){
    _activa = activa;
}

void TCamara::calculaView(){
    
}