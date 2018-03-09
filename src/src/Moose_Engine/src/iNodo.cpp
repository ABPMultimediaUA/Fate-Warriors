#include "iNodo.h"
#include "TNodo.h"
#include "TEntidad.h"
#include "TTransform.h"

iNodo::iNodo(){

}

iNodo::~iNodo(){

}

void iNodo::mover(float x, float y, float z){
    
    static_cast<TTransform*>(_nodo_motor->get_padre()->get_entidad())->trasladar(x, y, z);
}

void iNodo::rotar(float x, float y, float z, float w){
    static_cast<TTransform*>(_nodo_motor->get_padre()->get_padre()->get_padre()->get_entidad())->rotar(x, y, z, w);    
}

void iNodo::escalar(float x, float y, float z){
    static_cast<TTransform*>(_nodo_motor->get_padre()->get_padre()->get_entidad())->escalar(x, y, z);
}