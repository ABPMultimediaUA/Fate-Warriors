#include "Puerta.h"
#include "Interfaz/Motor.h"
#include "Utilidades/Modelados.h"
#include <string>
Puerta::Puerta(short _i_id, float _i_x, float _i_y, float _i_z, bool _i_abierta) : Objeto(_i_id, _i_x, _i_y, _i_z), _abierta(_i_abierta) {

    std::string str = "models/Personaje.obj"; //TEMPORAL : La llave usa el mismo modelado que el personaje
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    _id_motor = _motor->crearObjeto(E_BoundingBox,cstr,_i_x,_i_y,_i_z);
}

void Puerta::set_abierta(bool _i_abierta){
	_abierta = _i_abierta;
    _motor->saltar(_id_motor);
}

bool Puerta::get_abierta(){
    return _abierta;
}

Puerta::~Puerta() {

}
