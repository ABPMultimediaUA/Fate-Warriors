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
    if(_i_shader->check_program(sombras_proyectadas)){
        _matriz[3][1]=_matriz[3][1]+_animacion->get_BB().y/8;
    }
    _i_shader->setModel(_matriz);
    _animacion->draw(_i_shader,_contador_anim);
    update_anim();
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
            if(_contador_anim!=(_animacion->get_anim_cont()-1)){
                ++_contador_anim;
            }else if(_bucle){
                _contador_anim=0;
            }
        }
    }
}
glm::vec3 TAnimacion::get_BB(){
    return _animacion->get_BB();
}