#include "TLuz.h"
#include <iostream>

TLuz::TLuz(){}
TLuz::~TLuz(){}
void TLuz::beginDraw(){

    std::cout<<"ID ------"<<_ID<<"\n";
}
void TLuz::endDraw(){
    std::cout<<"termino dibujar "<<_ID<<"\n";
}