#include "TTransform.h"

TTransform::TTransform(){}
TTransform::~TTransform(){}

void TTransform::beginDraw(){
    pila_matrices.push(matriz);
    matriz=_t_matriz*matriz;
}
void TTransform::endDraw(){
    matriz=pila_matrices.top();
    pila_matrices.pop();
}