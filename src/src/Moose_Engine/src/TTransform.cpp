#include "TTransform.h"
#include <iostream>

TTransform::TTransform(){
    _t_matriz = glm::mat4(1.0f);
}
TTransform::~TTransform(){}

void TTransform::beginDraw(Shader* _i_shader){
    _pila_matrices.push(_matriz);
    _matriz = _matriz * _t_matriz;   //MULTIPLICACION DE MATRIZ
    //std::cout<<"ID ------"<<_ID<<"matrix:   "<<glm::to_string(_t_matriz)<<"\n";
    //std::cout<<"lll:  "<<glm::to_string(matriz)<<"\n";
    
    /*    matriz= glm::outerProduct(&_t_matriz,&matriz);
    glm::vec4 a(0.1, 0.2, 0.3, 0.4), b(0.5, 0.6, 0.7, 0.8);
    glm::mat4 algo=(a,a,a,a);
    glm::mat4 o = glm::outerProduct(a, b);*/

}
void TTransform::endDraw(){

    _matriz=_pila_matrices.top();
    _pila_matrices.pop();
}

void TTransform::identidad(){
    _t_matriz = glm::mat4(1.0f);
}

void TTransform::cargar(glm::mat4 matriz){
    _t_matriz = matriz;
}

void TTransform::trasponer(){
    _t_matriz = glm::transpose(_t_matriz);
}

void TTransform::trasladar(float _i_x, float _i_y, float _i_z){
    _t_matriz = glm::translate(glm::vec3(_i_x,_i_y,_i_z));
}

void TTransform::rotar(float _i_x, float _i_y, float _i_z, float _i_w){
    _t_matriz = glm::rotate(_t_matriz, glm::radians(_i_w), glm::vec3(_i_x,_i_y,_i_z));
}

void TTransform::escalar(float _i_x, float _i_y, float _i_z){
    _t_matriz = glm::scale(glm::vec3(_i_x,_i_y,_i_z));
    int algo;
}

