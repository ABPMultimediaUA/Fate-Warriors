#include "Nodo_blackboard.h"
#include <iostream>

Nodo_blackboard::Nodo_blackboard(int _i_zona_actual){
    _zona_actual=static_cast<Enum_zonas>(_i_zona_actual);
    _zonas_ady=0;
}

Nodo_blackboard::~Nodo_blackboard(){
    _objetos.clear();
    delete[] _zonas_ady;
    _zonas_ady=nullptr;
}
Enum_zonas Nodo_blackboard::get_zona_actual(){
    return _zona_actual;
}
int* Nodo_blackboard::get_zonas_ady(){
    return _zonas_ady;
}
std::vector<Objeto*> Nodo_blackboard::get_objetos(){
    return _objetos;
}

unsigned short Nodo_blackboard::get_lod(){
    return _lod;
}

int Nodo_blackboard::get_ultima_zona(){
    if(_zona_actual==Enum_zonas::Zona_enemiga){
        return _ultima_zona;
    }else{
        return 0;
    }
}
Enum_Acciones Nodo_blackboard::get_ultima_accion(){
    if(_zona_actual==Enum_zonas::Zona_enemiga){
        return _ultima_accion;
    }else{
        return Enum_Acciones::Nada;
    }
}
int Nodo_blackboard::get_zonas_enemigas(){
    return _n_zonas_ady_enemigas;
}
void Nodo_blackboard::set_lod(int _i_lod){
    _lod=_i_lod;
}
void Nodo_blackboard::declarar_zonas_ady(int _i_size){//unsigned necesario para declarar el array
    _zonas_ady = new int[_i_size];
    _n_zonas_ady_enemigas=_i_size;
    while(_i_size>0){
        --_i_size;
        _zonas_ady[_i_size]=0;
    }
}
void Nodo_blackboard::anyadir_zona(int _i_zona){
    unsigned short cont=0;
    while(cont<_n_zonas_ady_enemigas){
        if(_zonas_ady[cont]==0){
            _zonas_ady[cont]=_i_zona;
        }
        ++cont;
    }
}