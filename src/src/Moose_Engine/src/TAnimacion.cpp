#include "TAnimacion.h"

#include "TGestorRecursos.h"
#include "TRecursoAnimacion.h"
#include "Shader.h"

#include "TNodo.h"
#include "iNodoAnimacion.h"

#include <iostream>


TAnimacion::TAnimacion(const char* path){
    leerAnimacion(path);
    _contador_anim = 0;
}

TAnimacion::~TAnimacion(){

}
void TAnimacion::beginDraw(Shader* _i_shader){
    draw(_i_shader);
}

void TAnimacion::draw(Shader* _i_shader){
    if(_i_shader->check_program(sombras_proyectadas)){//desviacion de la sombra para evitar superposicion
        _matriz[3][1]=_matriz[3][1]+0.46;
    }
    _i_shader->setModel(_matriz);
    _animacion->draw(_i_shader,_contador_anim);
}

void TAnimacion::endDraw(){   
}

void TAnimacion::leerAnimacion(const char* path){
    TGestorRecursos* gRec = TGestorRecursos::get_instancia();
    _animacion=gRec->getRecursoAnim(path);

}
std::string TAnimacion::get_nombre(){
    return _animacion->GetNombre();
}


void TAnimacion::set_cont_animaciones(uint8_t _i_cont) {
    _contador_anim = _i_cont;
}

uint8_t TAnimacion::get_max_anim() {
    return _animacion->get_anim_cont() - 1;
}
glm::vec3 TAnimacion::get_BB(){
    return _animacion->get_BB();
}