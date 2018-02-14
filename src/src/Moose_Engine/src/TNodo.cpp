#include "TNodo.h"

#include <iterator>
#include <algorithm>

#include <iostream>

TNodo::TNodo(uint16_t entidadID, TNodo* nodo_padre) : _visible(true){
    _padre = nodo_padre;
    _entidadID = entidadID;
    _entidad = nullptr;
}

TNodo::~TNodo(){
    for(auto it = _hijos.begin(); it!=_hijos.end(); it++){ //itera por el vector eliminando
        delete *it;
    }
    delete _entidad;
}

void TNodo::agrega_hijo(TNodo* hijo){
    _hijos.push_back(hijo);
}

void TNodo::agrega_hijo(TEntidad* entidad){

}

void TNodo::set_nodo_padre(TNodo* nodo_padre){
    _padre = nodo_padre;
}

void TNodo::borrar_nodo(){
    _padre->borrar_hijo(this);
    set_nodo_padre(nullptr);
    delete this;
}

bool TNodo::borrar_hijo(TNodo* hijo){
    auto result = std::find(_hijos.begin(), _hijos.end(), hijo);

    if(result != _hijos.end()){
        _hijos.erase(result);
        return true;
    }
    
    return false;
}

TEntidad* TNodo::get_entidad(){
    return _entidad;
}

void TNodo::set_entidad(TEntidad* entidad){
    _entidad = entidad;
    _entidad->setID(_entidadID);
}

uint16_t TNodo::get_entidad_id(){
    return _entidadID;
}

void TNodo::draw(){
            if(_entidad != nullptr){
                _entidad->beginDraw();
                for(std::vector<TNodo*>::iterator it = _hijos.begin(); it != _hijos.end(); it++){
                    (*it)->draw();
                }
                _entidad->endDraw();
            }else{
                std::cout<<"entra";
                for(std::vector<TNodo*>::iterator it = _hijos.begin(); it != _hijos.end(); it++){
                    (*it)->draw();
                }
            }
}