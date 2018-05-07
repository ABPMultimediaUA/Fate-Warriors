#include "iNodoModeladoEscenario.h"
#include "TModeladoEscenario.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TNodo.h"

iNodoModeladoEscenario::iNodoModeladoEscenario(const char* ruta){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TModeladoEscenario* _ModeladoEscenario = motor->crearModeladoEscenario(ruta);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoModeladoEscenario = motor->crearNodo(nodoTraslacion, _ModeladoEscenario);

    _nodo_motor = nodoModeladoEscenario; //almacenamos el puntero al nodo del ME
}

iNodoModeladoEscenario::iNodoModeladoEscenario(const char* ruta, float x, float y, float z){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TModeladoEscenario* _ModeladoEscenario = motor->crearModeladoEscenario(ruta);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoModeladoEscenario = motor->crearNodo(nodoTraslacion, _ModeladoEscenario);

    _nodo_motor = nodoModeladoEscenario; //almacenamos el puntero al nodo del ME
}


void iNodoModeladoEscenario::cambiar_modelado(const char * _i_ruta){
    TMooseEngine* motor =  TMooseEngine::get_instancia();
    TModeladoEscenario* _ModeladoEscenario = motor->crearModeladoEscenario(_i_ruta);
    TNodo* nodoModeladoEscenario = motor->crearNodo(_nodo_motor->get_padre(), _ModeladoEscenario);
    borrarNodo();
    _nodo_motor=nodoModeladoEscenario;
}

Vector3 iNodoModeladoEscenario::getBB(){
    glm::vec3 bb = static_cast<TModeladoEscenario*>(_nodo_motor->get_entidad())->get_BB();
    return Vector3(bb.x, bb.y, bb.z);
}

