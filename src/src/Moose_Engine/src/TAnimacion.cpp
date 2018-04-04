#include "TAnimacion.h"
#include "TGestorRecursos.h"
#include "TRecursoAnimacion.h"
#include "Shader.h"
#include <iostream>


TAnimacion::TAnimacion(const char* path){
    const char* s(path);
    leerAnimacion(s);
}

TAnimacion::~TAnimacion(){

}
void TAnimacion::beginDraw(Shader* _i_shader){
    draw(_i_shader);
}

void TAnimacion::draw(Shader* _i_shader){
    _i_shader->setModel(_matriz);
    _animacion->draw(_i_shader,15);
    //seleccionar de entre todos los modelados el correspondiente para dibujar
    /*
    _i_shader->setModel(_matriz);
    for(std::vector<TModelado*>::iterator it = _modelos.begin(); it != _modelos.end(); it++){
        (*it)->draw(_i_shader);
    }*/
}

void TAnimacion::endDraw(){   
}

void TAnimacion::leerAnimacion(const char* path){
    TGestorRecursos* gRec = TGestorRecursos::get_instancia();
    _animacion=gRec->getRecursoAnim(path);

}