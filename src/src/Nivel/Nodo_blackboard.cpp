#include "Nodo_blackboard.h"

Nodo_blackboard::Nodo_blackboard(int _i_zona_actual){
    _zona_actual=static_cast<Enum_zonas>(_i_zona_actual);
}

Nodo_blackboard::~Nodo_blackboard(){
    _objetos.clear();
}
Enum_zonas Nodo_blackboard::get_zona_actual(){
    return _zona_actual;
}
std::vector<int> Nodo_blackboard::get_zonas_ady(){
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
    return _zonas_ady.size();
}
void Nodo_blackboard::set_lod(int _i_lod){
    _lod=_i_lod;
}
void Nodo_blackboard::anyadir_zona(int _i_zona){
    _zonas_ady.push_back(_i_zona);
}