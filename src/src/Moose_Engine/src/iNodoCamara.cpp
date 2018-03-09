#include "iNodoCamara.h"
#include "TMooseEngine.h"
#include "TTransform.h"
#include "TCamara.h"

iNodoCamara::iNodoCamara(bool activa, float x, float y, float z){
    //referencia al ME
    TMooseEngine* motor =  TMooseEngine::get_instancia();

    TCamara* _camara = motor->crearCamara(activa);
    TTransform* transTraslacion = motor->crearTransform();
    TTransform* transRotacion   = motor->crearTransform();
    TTransform* transEscalado   = motor->crearTransform();

    transTraslacion->trasladar(x, y, z);
    
    TNodo* nodoRotacion   = motor->crearNodo(motor->nodoRaiz(), transRotacion);
    TNodo* nodoEscalado   = motor->crearNodo(nodoRotacion, transEscalado);
    TNodo* nodoTraslacion = motor->crearNodo(nodoEscalado, transTraslacion);

    TNodo* nodoCamara = motor->crearNodoCamara(nodoTraslacion, _camara);

    _nodo_motor = nodoCamara; //almacenamos el puntero al nodo del ME
}