#include "Minas.h"
#include "../Tiempo/Time.h"

Minas::Minas(short _id, float _i_x, float _i_y,float _i_z) : Trampas(_id, _i_x, _i_y,  _i_z, -50){
    _explota_en = _reloj->get_current();
    desactivar();
}

Minas::~Minas(){
}


void Minas::activar(){
    _activa = true;
    _explota_en=_reloj->get_current() + 3000;
}

bool Minas::explota(){
    if(_activa && _reloj->get_current()>_explota_en){
        return true;
    }
    return false;
}

void Minas::render(){

}