#include "Interruptor_Tiempo.h"

#include "../Puerta_Pincho.h"

#include "../../Tiempo/Time.h"

Interruptor_Tiempo::Interruptor_Tiempo(short _i_id, float _i_x, float _i_z, float _i_rotacion, uint16_t _t_duracion, short _i_rotacion_x, short _i_rotacion_y, short _i_distancia) : Interruptor(_i_id, _i_x, _i_z, _i_rotacion, _i_rotacion_x, _i_rotacion_y, _i_distancia){
	_t_final_activacion = 0;
	_duracion = _t_duracion;
}

Interruptor_Tiempo::~Interruptor_Tiempo() {
}

void Interruptor_Tiempo::accionar() {
    if(_estado == false) {
        _estado = true;

		cambiar_estado_puertas();
        _t_final_activacion = _reloj->get_current() + _duracion;
    }
}

void Interruptor_Tiempo::update() {
	if(_estado && _reloj->get_current() >= _t_final_activacion) {
		_estado = false;
       
       cambiar_estado_puertas();
	}
}

void Interruptor_Tiempo::cambiar_estado_puertas() {
    uint8_t size = _puertas_asociadas.size();

    for(uint8_t i=0; i<size; i++) {
    	_puertas_asociadas[i]->cambiar_estado();
    }
}