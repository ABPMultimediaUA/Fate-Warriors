#include "Llave.h"
#include "Interfaz/Motor.h"
#include "Utilidades/Modelados.h"
#include <string>

Llave::Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta) : Objeto(_i_id, _i_x, _i_y, _i_z), _id_puerta(_i_id_puerta) {

    std::string str = "models/Personaje.obj"; //TEMPORAL : La llave usa el mismo modelado que el personaje
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    _id_motor = _motor->crearObjeto(cstr,_i_x,_i_y,_i_z);
}

Llave::~Llave() {
}

short Llave::get_id_puerta(){
    return _id_puerta;
}
