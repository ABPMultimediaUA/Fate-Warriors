#include "Interruptor.h"

#include "Puerta_Pincho.h"
#include <iostream>

Interruptor::Interruptor(short _i_id, float _i_x, float _i_z, float _i_rotacion) : Objeto(_i_id, _i_x, 0, _i_z){
	 
    const char* cstr  = "models/Interactuables/Interruptor/BaseInterruptor.obj";
    _objeto_motor = new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,0,_i_z,0);
    _objeto_motor->rotar_nodo(_i_rotacion);

    const char* cstr_2  = "models/Interactuables/Interruptor/PalancaInterruptor.obj";
	_palito = new Objeto_Motor(this,E_BoundingBox, cstr_2, _i_x,-1.8,_i_z,0);
    _palito->rotar_nodo(_i_rotacion);

    _estado = false;
}

Interruptor::~Interruptor() {
	delete _palito;

    _puertas_asociadas.clear();
}


void Interruptor::accionar_sin_propagar() {
    accionar();
}

void Interruptor::agregar_puerta(Puerta_Pincho* _puerta) {
    _puertas_asociadas.push_back(_puerta);
}

void Interruptor::agregar_interruptor(Interruptor* _interruptor) {
}


void Interruptor::update(){
}