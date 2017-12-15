#include "Puerta.h"

Puerta::Puerta(short _i_id, float _i_x, float _i_y, float _i_z, bool _i_abierta) : Objeto(_i_id, _i_x, _i_y, _i_z), _abierta(_i_abierta) {
}

void Puerta::set_abierta(bool _i_abierta){
	_abierta = _i_abierta;
}

Puerta::~Puerta() {
}
