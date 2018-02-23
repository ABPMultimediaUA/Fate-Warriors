#include "TMalla.h"
#include "TRecursoMalla.h"
#include <iostream>
TMalla::TMalla(){
    _t_matriz = glm::mat4(1.0f);
}
TMalla::~TMalla(){

}
void TMalla::beginDraw(){
    std::cout<<"ID ------"<<_ID<<"\n";
}

void TMalla::draw(){
    for(std::vector<TRecursoMalla*>::iterator it = mallas.begin(); it != mallas.end(); it++){
        (*it)->draw();
    }
}

void TMalla::endDraw(){
    std::cout<<"termino dibujar "<<_ID<<"\n";    
}