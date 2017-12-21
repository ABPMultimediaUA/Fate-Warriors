#include "Puerta.h"
#include "Interfaz/Matcher.h"
#include "Utilidades/Modelados.h"

Puerta::Puerta(short _i_id, float _i_x, float _i_y, float _i_z, bool _i_abierta) : Objeto(_i_id, _i_x, _i_y, _i_z), _abierta(_i_abierta) {
    _matcher = new Matcher(PERSONAJE_R, PERSONAJE_M, _i_x, _i_y, _i_z, 1, false);
}

void Puerta::set_abierta(bool _i_abierta){
	_abierta = _i_abierta;
}

bool Puerta::get_abierta(){
    return _abierta;
}

Puerta::~Puerta() {
}
