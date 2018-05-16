#include "Llave.h"

#include "../Interfaz/Motor.h"
#include "../Moose_Engine/src/iObjeto_Mapa.h"


Llave::Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta) : Objeto(_i_id, _i_x, _i_y, _i_z), _id_puerta(_i_id_puerta) {

   const char* cstr = "Llave";
       
    _objeto_motor = new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
  //  _objeto_visual_mapa = new iObjeto_Mapa(_i_x, _i_z, 50,50, Enum_Llave);
}

Llave::~Llave() {
    if (_objeto_visual_mapa !=nullptr){
        eliminar_del_minimapa();
    }
}

short Llave::get_id_puerta(){
    return _id_puerta;
}

std::tuple<float, float> Llave::get_posicion() {
    return std::make_tuple(_objeto_motor->getX(), _objeto_motor->getZ());
}

void Llave::eliminar_del_minimapa(){
    delete _objeto_visual_mapa;
    _objeto_visual_mapa = nullptr;
}