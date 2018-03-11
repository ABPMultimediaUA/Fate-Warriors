#include "iNodoLuz.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TLuz.h"
#include "TNodo.h"

iNodoLuz::iNodoLuz(bool activa, float intensidad){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TLuz* _luz = motor->crearLuz(glm::vec3(1,1,1),glm::vec3(1,1,1),glm::vec3(1,1,1));

    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    //transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoLuz = motor->crearNodoLuz(nodoTraslacion, _luz);
    _nodo_motor = nodoLuz; //almacenamos el puntero al nodo del ME
}

iNodoLuz::iNodoLuz(bool activa, float intensidad, float x, float y, float z){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TLuz* _luz = motor->crearLuz(glm::vec3(1,1,1),glm::vec3(1,1,1),glm::vec3(1,1,1));

    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoLuz = motor->crearNodoLuz(nodoTraslacion, _luz);
    _nodo_motor = nodoLuz; //almacenamos el puntero al nodo del ME
}

iNodoLuz::~iNodoLuz(){
    
}