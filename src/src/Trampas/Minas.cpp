#include "Minas.h"
#include "../Tiempo/Time.h"
                                                                                            //70 en danyo
Minas::Minas(short _id, float _i_x, float _i_y,float _i_z) : Trampas(_id, _i_x, _i_y,  _i_z, 450){
    _explota_en = _reloj->get_current();
 
    const char* cstr  = "models/Trampas/Mina/Mina.obj";

    //_id=_id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z,12);
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,69);
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