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
    if(_i_shader->check_program(sombras_proyectadas)){//ajuste de la sombra por posicionamiento del pivote en el centro
        _matriz[3][1]=_matriz[3][1]-_modelado->get_BB().y/2+0.1;
    }
    _i_shader->setModel(_matriz);
    _modelado->draw(_i_shader);
}

void TModelado::endDraw(){   
}

void TModelado::leerModelado(const char* path){
    TGestorRecursos* gRec = TGestorRecursos::get_instancia();
    _modelado = gRec->getRecursoModelo(path);
 
}
glm::vec3 TModelado::get_BB(){
    return _modelado->get_BB();
}