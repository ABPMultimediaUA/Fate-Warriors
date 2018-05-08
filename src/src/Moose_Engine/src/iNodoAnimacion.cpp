#include "iNodoAnimacion.h"

#include "TAnimacion.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TNodo.h"

#include "../../Tiempo/Time.h"

#include <iostream>

iNodoAnimacion::iNodoAnimacion(bool bucle, const char* ruta, uint8_t _num_ruta){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TAnimacion* _animacion_aux = motor->crearAnimacion(ruta);
    _bucle= bucle;

    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoAnimacion = motor->crearNodo(nodoTraslacion, _animacion_aux);

    _nodo_motor = nodoAnimacion; //almacenamos el puntero al nodo del ME

    _ruta_actual = _num_ruta;

    _animacion = _animacion_aux;

    _contador_anim = 0;

    _bucle = true;
    _fin_animacion = false;

    _max_anim = _animacion->get_max_anim();
    _animacion->set_cont_animaciones(_contador_anim);

    _reloj = Time::Instance();
    _tiempo_aux = _reloj->get_tiempo_inicio_pausa();

    _ruta_idle = ruta;
}

iNodoAnimacion::iNodoAnimacion(bool bucle, const char* ruta, float x, float y, float z, uint8_t _num_ruta){
    
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TAnimacion* _animacion_aux = motor->crearAnimacion(ruta);
    _bucle= bucle;

    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoAnimacion = motor->crearNodo(nodoTraslacion, _animacion_aux);

    _nodo_motor = nodoAnimacion; //almacenamos el puntero al nodo del ME

    _ruta_actual = _num_ruta;

    _animacion = _animacion_aux;

    _contador_anim = 0;

    _bucle = true;
    _fin_animacion = false;

    _max_anim = _animacion->get_max_anim();
    _animacion->set_cont_animaciones(_contador_anim);

    _reloj = Time::Instance();
    _tiempo_aux = _reloj->get_tiempo_inicio_pausa();

    _ruta_idle = ruta;
}


iNodoAnimacion::~iNodoAnimacion(){
    
}

void iNodoAnimacion::cambiar_modelado(const char * _i_ruta, uint8_t _num_ruta){
    
    if(_num_ruta != _ruta_actual && (_ruta_actual < 10 || _fin_animacion == true || (_ruta_actual >= 10 && _num_ruta >= 10))) {
        TMooseEngine* motor =  TMooseEngine::get_instancia();
        TAnimacion* _Animacion = motor->crearAnimacion(_i_ruta);
        TNodo* nodoAnimacion = motor->crearNodo(_nodo_motor->get_padre(), _Animacion);

        borrarNodo();

        _nodo_motor = nodoAnimacion;
        _ruta_actual = _num_ruta;

        if(_num_ruta < 3) {
            _bucle = true;
        }
        else {
            _bucle = false;
        }

        _fin_animacion = false;
        
        _animacion = _Animacion;

        _contador_anim = 0;
        _max_anim = _animacion->get_max_anim();
    }
}


// RUTAS
// 0 - IDLE
// 1 - ANDAR
// 2 - CORRER

// 10 - ATK D 1
// 11 - ATK D 2
// 12 - ATK D 3
// 13 - ATK F 1
// 14 - ATK F 2
// 15 - ATK F 3

void iNodoAnimacion::update_anim(){
    if(!_reloj->get_esta_pausado() && _reloj->get_current()-_tiempo_aux>=55){
        _tiempo_aux=_reloj->get_current();

        if(_contador_anim < _max_anim){
            ++_contador_anim;
        }
        else if(_bucle){
            _contador_anim = 0;
        }
        else if(!_bucle) {
            _fin_animacion = true;
            cambiar_modelado(_ruta_idle, 0);
        }

        _animacion->set_cont_animaciones(_contador_anim);
    }
}


Vector3 iNodoAnimacion::getBB(){
    glm::vec3 bb = static_cast<TAnimacion*>(_nodo_motor->get_entidad())->get_BB();
    return Vector3(bb.x, bb.y, bb.z);
}