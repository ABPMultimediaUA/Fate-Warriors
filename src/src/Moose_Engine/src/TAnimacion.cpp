#include "TAnimacion.h"
#include "TGestorRecursos.h"
#include "TRecursoAnimacion.h"
#include "Shader.h"
#include "../../Tiempo/Time.h"
//#include "Time.h"
#include <iostream>


TAnimacion::TAnimacion(const char* path){
    leerAnimacion(path);
    _contador_anim=0;
    _reloj=Time::Instance();
    _tiempo_aux=_reloj->get_tiempo_inicio_pausa();
    _bucle=false;
}

TAnimacion::~TAnimacion(){

}
void TAnimacion::beginDraw(Shader* _i_shader){
    draw(_i_shader);
}

void TAnimacion::draw(Shader* _i_shader){
    _i_shader->setModel(_matriz);
    _animacion->draw(_i_shader,_contador_anim);
    update_anim();
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
std::string TAnimacion::get_nombre(){
    return _animacion->GetNombre();
}
void TAnimacion::update_anim(){
    if(!_reloj->get_esta_pausado()){
        if(_reloj->get_current()-_tiempo_aux>=55){
            _tiempo_aux=_reloj->get_current();
            if(_contador_anim!=_animacion->get_anim_cont()){
                ++_contador_anim;
            }else if(_bucle){
                _contador_anim=0;
            }
        }
    }
}