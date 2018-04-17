#include "Pinchos.h"

#include "../Tiempo/Time.h"

Pinchos::Pinchos(short _id, float _i_x, float _i_y,float _i_z) : Trampas(_id, _i_x, _i_y,  _i_z, 50){
    siguiente_tiempo_hace_danyo =_reloj->get_current();
 
    const char* cstr  = "Pinchos";
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
}

Pinchos::~Pinchos(){}

bool Pinchos::puede_quitar_vida(){ 
    if(_reloj->get_current() > siguiente_tiempo_hace_danyo){
        siguiente_tiempo_hace_danyo = _reloj->get_current() + 600;
        return true;
    }
    
    return false;
}
