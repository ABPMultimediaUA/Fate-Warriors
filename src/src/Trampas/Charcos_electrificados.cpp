#include "Charcos_electrificados.h"
#include "../Tiempo/Time.h"

Charcos_electrificados::Charcos_electrificados(short _id, float _i_x, float _i_y,float _i_z) : Trampas(_id, _i_x, _i_y,  _i_z, 50){
    siguiente_tiempo_hace_danyo = _reloj->get_current();
    std::string str = "models/Trampas/Charco/Charco.obj";
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    
    _id=_id_motor = _motor->crearObjeto(E_BoundingBox,cstr,_i_x, _i_y, _i_z);
}

Charcos_electrificados::~Charcos_electrificados(){
	_reloj=nullptr;
}


void Charcos_electrificados::render(){}


bool Charcos_electrificados::puede_quitar_vida(){ 
    if(_reloj->get_current() > siguiente_tiempo_hace_danyo){
        siguiente_tiempo_hace_danyo = _reloj->get_current() + 1000;
        return true;
    }
    
    return false;
}
