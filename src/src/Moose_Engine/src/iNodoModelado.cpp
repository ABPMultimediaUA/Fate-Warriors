#include "iNodoModelado.h"
#include "TModelado.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TNodo.h"

iNodoModelado::iNodoModelado(){
    
}
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


void iNodoModelado::cambiar_modelado(const char * _i_ruta, uint8_t _num_ruta){
    TMooseEngine* motor =  TMooseEngine::get_instancia();
    TModelado* _modelado = motor->crearModelado(_i_ruta);
    TNodo* nodoModelado = motor->crearNodo(_nodo_motor->get_padre(), _modelado);
    borrarNodo();
    _nodo_motor=nodoModelado;
}

Vector3 iNodoModelado::getBB(){
    glm::vec3 bb = static_cast<TModelado*>(_nodo_motor->get_entidad())->get_BB();
    return Vector3(bb.x, bb.y, bb.z);
}

iNodoModelado::~iNodoModelado(){
    
}

void iNodoModelado::remove(){
    delete this;
}