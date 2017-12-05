#include "Blackboard.h"

#include "Interfaz_Toma_Decision.h"

Blackboard::Blackboard(Interfaz_Toma_Decision& _i_interfaz, unsigned short _i_n_enemigo) {
	_n_enemigo = _i_n_enemigo;
	_interfaz = &_i_interfaz;
	_disancia_jugador = 0;
	_decision = Decision_Quieto;
	_accion = Nada;
}

Blackboard::~Blackboard() {

}

void Blackboard::actualiza_datos() {
	_disancia_jugador = _interfaz->interfaz_decision_distancia_enemigo_personaje(_n_enemigo);
}

enum Enum_Decisiones Blackboard::get_decision() {
	return _decision;
}

enum Enum_Acciones Blackboard::get_accion() {
	return _accion;
}

float Blackboard::get_distancia_jugador() {
	return _disancia_jugador;
}

void Blackboard::set_decision(enum Enum_Decisiones _i_decision) {
	_decision = _i_decision;
}

void Blackboard::set_accion(enum Enum_Acciones _i_accion) {
	_accion = _i_accion;
}
