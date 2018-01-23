#include "Llave.h"
#include "Interfaz/Motor.h"
#include "Utilidades/Modelados.h"
#include <string>
//#include "Interfaz/Objeto_Motor.h"

Llave::Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta) : Objeto(_i_id, _i_x, _i_y, _i_z), _id_puerta(_i_id_puerta) {

   const char* cstr = "models/Interactuables/Llave/Llave.obj";

   // _id_motor = _motor->crear_objeto(E_BoundingBox,cstr,_i_x,_i_y,_i_z, 999);
       
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);
    

}

Llave::~Llave() {
}

short Llave::get_id_puerta(){
    return _id_puerta;
}
