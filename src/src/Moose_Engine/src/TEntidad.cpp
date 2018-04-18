#include "TEntidad.h"
#include "TNodo.h"

glm::mat4 TEntidad::_matriz;
std::stack<glm::mat4> TEntidad::_pila_matrices;

TEntidad::TEntidad() : _nodo(nullptr){

}

TEntidad::~TEntidad(){
}

TNodo* TEntidad::get_mi_nodo(){
    return _nodo;
}

void TEntidad::set_mi_nodo(TNodo* nodo){
    _nodo = nodo;
}

uint16_t TEntidad::getID(){
    return _ID;
}

void TEntidad::setID(uint16_t id){
    _ID = id;
}

glm::mat4 TEntidad::get_matriz(){
    return _matriz;
}