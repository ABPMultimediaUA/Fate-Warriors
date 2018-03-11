#include "iNodoModelado.h"
#include "TModelado.h"
#include "TMooseEngine.h"
#include "TTransform.h"

iNodoModelado::iNodoModelado(const char* ruta){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TModelado* _modelado = motor->crearModelado(ruta);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoModelado = motor->crearNodo(nodoTraslacion, _modelado);

    _nodo_motor = nodoModelado; //almacenamos el puntero al nodo del ME
}

iNodoModelado::iNodoModelado(const char* ruta, float x, float y, float z){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TModelado* _modelado = motor->crearModelado(ruta);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoModelado = motor->crearNodo(nodoTraslacion, _modelado);

    _nodo_motor = nodoModelado; //almacenamos el puntero al nodo del ME
}

iNodoModelado::~iNodoModelado(){
    
}