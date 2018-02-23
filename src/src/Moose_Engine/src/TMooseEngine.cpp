#include "TMooseEngine.h"
#include "TNodo.h"
#include "TTransform.h"
#include "TCamara.h"
#include "TLuz.h"
#include "TMalla.h"
#include "TGestorRecursos.h"

struct Mapeado{//declaracion de los parametros
    bool activa;
    TNodo* nodo;
};
TMooseEngine::TMooseEngine(){
    uint16_t _contadorIDEntidad = 0;
    _n_camaras=2;
    _n_c_actual=0;
    _n_l_actual=0;
    _n_luces=0;
    _gestorRecursos = new TGestorRecursos();
    TNodo* nodo = new TNodo(_contadorIDEntidad,nullptr);
    _escena = nodo;
    _mapping_camaras = new Mapeado[_n_camaras];
    _mapping_luces   = new Mapeado[_n_luces];
}
TMooseEngine::~TMooseEngine(){
    delete _escena;
    delete _gestorRecursos;
    delete _mapping_luces;
    delete _mapping_camaras;
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
    _mapping_camaras[_n_c_actual]={true,crearNodo(padre,ent)};
    ++_n_c_actual;
}
TNodo* TMooseEngine::crearNodoLuz(TNodo *padre, TEntidad *ent){
    _mapping_luces[_n_l_actual]={true,crearNodo(padre,ent)};
    ++_n_l_actual;
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

TMalla* TMooseEngine::crearMalla(char* _i_path){
    TMalla* malla = new TMalla(_i_path);
    //_gestorRecursos->getRecursoMalla(fichero);
    return malla;
}

void TMooseEngine::draw(){
    _escena->draw();
}

void TMooseEngine::drawLuces(){
    u_int16_t cont = 0;
    std::stack<glm::mat4> pila_matriz_luz;
    for(uint16_t i = 0; i < _n_luces; i++){
        if(_mapping_luces[i].activa){
            TNodo* this_node = _mapping_luces[i].nodo;
            while(this_node->get_padre()!=nullptr){
                pila_matriz_luz.push(this_node->get_entidad()->get_matriz());
                this_node = this_node->get_padre();
                cont++;
            }

            for(u_int16_t a = 0; a < cont; a++){
               matriz_luz = matriz_luz * pila_matriz_luz.top();
               pila_matriz_luz.pop();
            }
        }
    }
}

void TMooseEngine::drawCamaras(){
    u_int16_t cont = 0;
    std::stack<glm::mat4> pila_matriz_camara;
    for(uint16_t i = 0; i < _n_luces; i++){
        if(_mapping_camaras[i].activa){
            TNodo* this_node = _mapping_camaras[i].nodo;
            while(this_node->get_padre()!=nullptr){
                pila_matriz_camara.push(this_node->get_entidad()->get_matriz());
                this_node = this_node->get_padre();
                cont++;
            }

            for(u_int16_t a = 0; a < cont; a++){
                matriz_view = matriz_view * pila_matriz_camara.top();
                pila_matriz_camara.pop();
            }
            matriz_view = glm::inverse(matriz_view);
        }
    }
}