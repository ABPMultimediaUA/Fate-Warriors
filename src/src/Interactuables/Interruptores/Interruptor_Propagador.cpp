#include "Interruptor_Propagador.h"

#include "../Puerta_Pincho.h"

#include "../../Game.h"
#include "../../Tiempo/Time.h"

Interruptor_Propagador::Interruptor_Propagador(short _i_id, float _i_x, float _i_z, float _i_rotacion, short _i_rotacion_x, short _i_rotacion_y, short _i_distancia) : Interruptor(_i_id, _i_x, _i_z, _i_rotacion, _i_rotacion_x, _i_rotacion_y, _i_distancia){
}

Interruptor_Propagador::~Interruptor_Propagador() {
}

void Interruptor_Propagador::iniciar_interruptor() {
	Game::game_instancia()->cambio_a_update_mirar(Time::Instance()->get_current() + 3000, this, 90, 30, 30);
}

void Interruptor_Propagador::accionar() {
    accionar_sin_propagar();
    propagar_interruptores();
}

void Interruptor_Propagador::accionar_sin_propagar() {
    _estado = !_estado;
    cambiar_estado_puertas();
}

void Interruptor_Propagador::cambiar_estado_puertas() {
    uint8_t size = _puertas_asociadas.size();

    for(uint8_t i=0; i<size; i++) {
    	_puertas_asociadas[i]->cambiar_estado();
    }
}

void Interruptor_Propagador::propagar_interruptores() {
    uint8_t size = _interruptores_asociados.size();

    for(uint8_t i=0; i<size; i++) {
   		_interruptores_asociados[i]->accionar_sin_propagar();
    }
}

void Interruptor_Propagador::agregar_interruptor(Interruptor* _interruptor) {
    _interruptores_asociados.push_back(_interruptor);
}