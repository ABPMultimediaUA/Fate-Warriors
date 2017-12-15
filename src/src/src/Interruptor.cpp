#include "Interruptor.h"

Interruptor::Interruptor(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_objeto_asociado,
		bool _i_es_generador, bool _i_activado, short _i_temporizador) : Objeto(_i_id, _i_x, _i_y, _i_z),
		_id_objeto_asociado(_i_id_objeto_asociado), _es_generador(_i_es_generador), _activado(_i_activado),
		_temporizador(_i_temporizador){
}

void Interruptor::set_activado(bool _i_activado){
	_activado = _i_activado;
}

Interruptor::~Interruptor() {
}
