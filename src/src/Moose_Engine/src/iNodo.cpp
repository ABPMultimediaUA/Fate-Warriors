#include "iNodo.h"
#include "TNodo.h"
#include "TEntidad.h"
#include "TTransform.h"
#include <glm/ext.hpp>

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

Vector3 iNodo::getPosition(){
    glm::mat4 transformacion = static_cast<TTransform*>(_nodo_motor->get_padre()->get_entidad())->get_t_matriz();
    Vector3 position(transformacion[0][0], transformacion[1][1], transformacion[2][2]);
    return position;
}