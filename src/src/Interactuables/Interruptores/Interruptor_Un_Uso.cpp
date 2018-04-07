#include "Interruptor_Un_Uso.h"

#include "../Puerta_Pincho.h"

Interruptor_Un_Uso::Interruptor_Un_Uso(short _i_id, float _i_x, float _i_z, float _i_rotacion) : Interruptor(_i_id, _i_x, _i_z, _i_rotacion){
}

Interruptor_Un_Uso::~Interruptor_Un_Uso() {
}

void Interruptor_Un_Uso::accionar() {
    if(_estado == false) {
        _estado = true;

        uint8_t size = _puertas_asociadas.size();
        for(uint8_t i=0; i<size; i++) {
        	_puertas_asociadas[i]->desactivar();
        }
    }
}