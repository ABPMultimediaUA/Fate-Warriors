#include "TAnimacion.h"
#include "TGestorRecursos.h"
#include "Shader.h"
#include <iostream>


TAnimacion::TAnimacion(const char* path){
    std::string s(path);
    leerAnimacion(s);
}

TAnimacion::~TAnimacion(){
    _modelos.clear();
}
void TAnimacion::beginDraw(Shader* _i_shader){
    draw(_i_shader);
}

void TAnimacion::draw(Shader* _i_shader){
    _i_shader->setModel(_matriz);
    //seleccionar de entre todos los modelados el correspondiente para dibujar
    /*
    _i_shader->setModel(_matriz);
    for(std::vector<TModelado*>::iterator it = _modelos.begin(); it != _modelos.end(); it++){
        (*it)->draw(_i_shader);
    }*/
}

void TAnimacion::endDraw(){   
}

void TAnimacion::leerAnimacion(std::string &path){
    TGestorRecursos* gRec = TGestorRecursos::get_instancia();
    gRec->cargarAnim(path, _modelos);

}