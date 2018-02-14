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
TMooseEngine::~TMooseEngine(){
    delete _escena;
    delete _gestorRecursos;
    _contadorIDEntidad=0;
}

TNodo* TMooseEngine::crearNodo(TNodo *padre, TEntidad *ent){     
    TNodo* nodo = new TNodo(_contadorIDEntidad,padre);
    nodo->set_entidad(ent);
    padre->agrega_hijo(nodo);
    ++_contadorIDEntidad;
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
    //_gestorRecursos->getRecursoMalla(fichero);
    return malla;
}

TNodo* TMooseEngine::nodoRaiz(){
    return _escena;
}