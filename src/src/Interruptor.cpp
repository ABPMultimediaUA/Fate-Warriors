#include "Interruptor.h"
#include "Puerta_Pincho.h"
#include "Tiempo/Time.h"

Interruptor::Interruptor(short _i_id, float _i_x, float _i_y, float _i_z, float _i_rotacion, Puerta_Pincho* _i_objeto_asociado,
		bool _i_es_generador, bool _i_activado, double _i_temporizador) : Objeto(_i_id, _i_x, _i_y, _i_z),
		_objeto_asociado(_i_objeto_asociado), _es_generador(_i_es_generador){
	 
    const char* cstr  = "models/Interactuables/Interruptor/BaseInterruptor.obj";
    _objeto_motor =new Objeto_Motor(this,E_BoundingBox, cstr, _i_x,_i_y,_i_z,0);

    _objeto_motor->rotar_nodo(_i_rotacion);
	_npcs_persiguiendome = 0;

}

void Interruptor::set_activado(bool _i_activado){
	_objeto_asociado->activar();
}

void Interruptor::set_desactivado_para_siempre(){
	_objeto_asociado->desactivar();
	_objeto_asociado->set_desactivable_con_con_el_tiempo(false);
}


void Interruptor::set_desactivado(){
	_objeto_asociado->desactivar();
}

Interruptor::~Interruptor() {
}

void Interruptor::update(){
	/*
	if(_temporizador<_reloj->get_current()){
	}
	*/
	if(_objeto_asociado->comprobar_si_finalizo_el_tiempo()){
		_objeto_asociado->activar();
	}

}


void Interruptor::render(){
	
}