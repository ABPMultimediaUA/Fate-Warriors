#include "Opcion_Configuracion.h"

#include "../Game.h"

Opcion_Configuracion::Opcion_Configuracion(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Configuracion::~Opcion_Configuracion(){

}


Opcion* Opcion_Configuracion::update_opcion(double _i_tiempo, Opcion* _this) {
	return _this;
}