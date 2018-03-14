#include "TModelado.h"
#include "TRecursoModelado.h"
#include "TGestorRecursos.h"
#include "Shader.h"
#include <iostream>


TModelado::TModelado(const char* path){
    leerModelado(path);
}

TModelado::~TModelado(){

}

void TModelado::beginDraw(Shader* _i_shader){
    draw(_i_shader);
}

void TModelado::draw(Shader* _i_shader){
    _i_shader->setModel(_matriz);
    _modelado->draw(_i_shader);
}

void TModelado::endDraw(){   
}

void TModelado::leerModelado(const char* path){
    TGestorRecursos* gRec = TGestorRecursos::get_instancia();
    _modelado = gRec->getRecursoModelo(path);
 
}