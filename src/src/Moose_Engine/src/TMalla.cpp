#include "TMalla.h"
#include <iostream>
TMalla::TMalla(){
    _t_matriz = glm::mat4();
}
TMalla::~TMalla(){

}
void TMalla::beginDraw(){
    std::cout<<"ID ------"<<_ID<<"\n";
}
void TMalla::endDraw(){
    std::cout<<"termino dibujar "<<_ID<<"\n";    
}