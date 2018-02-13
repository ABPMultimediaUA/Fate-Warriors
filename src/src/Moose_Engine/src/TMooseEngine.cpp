#include "TMooseEngine.h"
#include "TNodo.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TGestorRecursos.h"

TMooseEngine::TMooseEngine(){
    uint16_t _contadorIDEntidad = 0;
    _gestorRecursos = new TGestorRecursos();
    TNodo* nodo = new TNodo(_contadorIDEntidad,nullptr);
    _escena = nodo;
}
TMooseEngine::~TMooseEngine(){}

TNodo* TMooseEngine::crearNodo(TNodo *padre, TEntidad *ent){     
    TNodo* nodo = new TNodo(_contadorIDEntidad,padre);
    padre->agrega_hijo(nodo);
    return nodo;
}

TTransform* TMooseEngine::crearTransform(){
    TTransform* transform = new TTransform();
    return transform;
}

TCamara* TMooseEngine::crearCamara(){
    TCamara* camara = new TCamara();
    return camara;
}

TLuz* TMooseEngine::crearLuz(){
    TLuz* luz = new TLuz();
    return luz;
}

TMalla* TMooseEngine::crearMalla(char* fichero){
    TMalla* malla = new TMalla();
    _gestorRecursos->getRecursoMalla(fichero);
    return malla;
}

TNodo* TMooseEngine::nodoRaiz(){
    return _escena;
}