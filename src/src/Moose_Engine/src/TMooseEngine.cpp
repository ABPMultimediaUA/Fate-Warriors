#include "TMooseEngine.h"
#include "TNodo.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TGestorRecursos.h"

struct Mapeado{//declaracion de los parametros
    bool activa;
    TNodo* Nodo;
};
TMooseEngine::TMooseEngine(){
    uint16_t _contadorIDEntidad = 0;
    n_camaras=2;
    n_c_actual=0;
    n_l_actual=0;
    n_luces=0;
    _gestorRecursos = new TGestorRecursos();
    TNodo* nodo = new TNodo(_contadorIDEntidad,nullptr);
    _escena = nodo;
    mapping_camaras = new Mapeado[n_camaras];
    mapping_luces   = new Mapeado[n_luces];
}
TMooseEngine::~TMooseEngine(){
    delete _escena;
    delete _gestorRecursos;
    delete mapping_luces;
    delete mapping_camaras;
    _contadorIDEntidad=0;
}

TNodo* TMooseEngine::crearNodo(TNodo *padre, TEntidad *ent){     
    TNodo* nodo = new TNodo(_contadorIDEntidad,padre);
    nodo->set_entidad(ent);
    padre->agrega_hijo(nodo);
    ++_contadorIDEntidad;
    return nodo;
}
TNodo* TMooseEngine::crearNodoCamara(TNodo *padre, TEntidad *ent){
    mapping_camaras[n_c_actual]={true,crearNodo(padre,ent)};
    ++n_c_actual;
}
TNodo* TMooseEngine::crearNodoLuz(TNodo *padre, TEntidad *ent){
    mapping_luces[n_l_actual]={true,crearNodo(padre,ent)};
    ++n_l_actual;
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

void TMooseEngine::draw(){
    _escena->draw();
}