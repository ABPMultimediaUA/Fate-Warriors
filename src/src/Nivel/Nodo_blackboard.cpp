#include "Nodo_blackboard.h"
#include <iostream>
#include "../Personajes/NPC.h"

Nodo_blackboard::Nodo_blackboard(int _i_zona_actual, u_int8_t _i_n_npc):_lod(4){
    _zona_actual=static_cast<Enum_zonas>(_i_zona_actual);
    _zonas_ady=nullptr;
    _maximo_npc=_i_n_npc;
    _NPC =new NPC*[_i_n_npc];
    for(u_int8_t cont=0;cont<_i_n_npc;++cont){
        _NPC[cont]=nullptr;
    }
}

Nodo_blackboard::~Nodo_blackboard(){
    _objetos.clear();
    delete[] _zonas_ady;
    delete[] _NPC;
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
void Nodo_blackboard::inserta_NPC(NPC* _i_npc){
    for(u_int8_t cont=0;cont<_maximo_npc;++cont){
        if(_NPC[cont]==nullptr){
            _NPC[cont]=_i_npc;
            break;
        }
    }
}
void Nodo_blackboard::elimina_NPC(NPC* _i_npc){
    for(u_int8_t cont=0;cont<_maximo_npc;++cont){
        if(_NPC[cont]==_i_npc){
            _NPC[cont]=nullptr;
            break;
        }
    }
}
NPC* Nodo_blackboard::get_NPC(u_int8_t num){
    if(num<_maximo_npc && num>=0){
        return _NPC[num];
    }else{
        return nullptr;
    }
}