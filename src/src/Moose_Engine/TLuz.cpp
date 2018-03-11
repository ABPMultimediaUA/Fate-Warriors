#include "TLuz.h"
#include <iostream>

TLuz::TLuz(glm::vec3 _i_ambiente, glm::vec3 _i_especular, glm::vec3 _i_difusa): 
_ambiente(_i_ambiente), _especular(_i_especular), _difusa(_i_difusa){
    
}
TLuz::~TLuz(){}
void TLuz::beginDraw(Shader* _i_shader){
}
void TLuz::endDraw(){
}

void TLuz::setActiva(bool activa){
    _activa = activa;
}