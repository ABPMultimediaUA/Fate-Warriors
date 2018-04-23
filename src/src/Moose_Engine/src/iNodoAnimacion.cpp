#include "iNodoAnimacion.h"
#include "TAnimacion.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TNodo.h"

iNodoAnimacion::iNodoAnimacion(bool bucle, const char* ruta){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TAnimacion* _animacion = motor->crearAnimacion(ruta);
    _animacion->set_bucle(bucle);

    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoAnimacion = motor->crearNodo(nodoTraslacion, _animacion);

    _nodo_motor = nodoAnimacion; //almacenamos el puntero al nodo del ME
}

iNodoAnimacion::iNodoAnimacion(bool bucle, const char* ruta, float x, float y, float z){
    
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TAnimacion* _animacion = motor->crearAnimacion(ruta);
    _animacion->set_bucle(bucle);

    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoAnimacion = motor->crearNodo(nodoTraslacion, _animacion);

    _nodo_motor = nodoAnimacion; //almacenamos el puntero al nodo del ME
}

void iNodoAnimacion::cambiar_modelado(const char * _i_ruta){
    TMooseEngine* motor =  TMooseEngine::get_instancia();
    TAnimacion* _Animacion = motor->crearAnimacion(_i_ruta);
    TNodo* nodoAnimacion = motor->crearNodo(_nodo_motor->get_padre(), _Animacion);
    borrarNodo();
    _nodo_motor=nodoAnimacion;
}

iNodoAnimacion::~iNodoAnimacion(){
    
}