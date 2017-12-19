#include "Blackboard.h"

#include "Interfaz_Datos.h"

Blackboard::Blackboard(Interfaz_Datos& _i_interfaz, unsigned short _i_n_enemigo) {
	/*_n_npc = _i_n_enemigo;
	_tipo_enemigo = Normal;
	_interfaz = &_i_interfaz;
	_distancia_jugador = 0;
	_decision = Decision_Quieto;
	_accion = Nada;*/
}

Blackboard::~Blackboard() {

}



void Blackboard::actualiza_datos() {
	_distancia_jugador = _interfaz->get_distancia_enemigo_personaje(_n_npc);
	// AQUI NO PUEDEN IR GETS
	// EN LUGAR DE GETS DEBE HABER PUNTEROS
	// AQUI SE HACEN CALCULOS SOBRE LAS VARIABLES QUE SE ACTUALIZAN AUTOMATICAMENTE
	// P. EJ. _se_acerca ES ALGO QUE NO SE VA A ACTUALIZAR, SE DEBE CALCULAR EN CADA ACTUALIZA_DATOS
}



void Blackboard::set_decision(enum Enum_Decisiones _i_decision) {
	_decision = _i_decision;
}

void Blackboard::set_accion(enum Enum_Acciones _i_accion) {
	_accion = _i_accion;
}



//ESTA POR HACER
unsigned short Blackboard::get_vida() {
	return 10;
}



unsigned short Blackboard::get_n_enemigo() {
	return _n_npc;
}

enum Enum_Tipo_Enemigo Blackboard::get_tipo_enemigo() {
	return _tipo_npc[0];
}

unsigned short Blackboard::get_rango_ataque() {
	return _rango_ataque[0];
}



enum Enum_Decisiones Blackboard::get_decision() {
	return _decision;
}

enum Enum_Acciones Blackboard::get_accion() {
	return _accion;
}



int8_t Blackboard::get_level_of_detail() {
	return _level_of_detail[0];
}

bool Blackboard::get_alertado() {
	return _alertado;
}

bool Blackboard::get_hay_orden() {
	return _hay_orden;
}



bool Blackboard::get_tiene_arma() {
	return _tiene_arma;
}

bool Blackboard::get_tiene_arma_corta() {
	return _tiene_arma_corta;
}

unsigned short Blackboard::get_rango_arma_corta() {
	return _rango_arma_corta;
}

bool Blackboard::get_tiene_arma_larga() {
	return _tiene_arma_larga;
}

unsigned short Blackboard::get_rango_arma_larga() {
	return _rango_arma_larga;
}



float Blackboard::get_distancia_jugador() {
	return _distancia_jugador;
}

enum Enum_Acciones Blackboard::get_accion_jugador() {
	return _accion_jugador;
}

bool Blackboard::get_se_acerca() {
	return _se_acerca;
}

bool Blackboard::get_jugador_tiene_arma() {
	return _jugador_tiene_arma;
}



unsigned short Blackboard::get_n_aliados_zona() {
	return _n_aliados_zona;
}



float Blackboard::get_distancia_objeto() {
	return _distancia_objeto;
}

bool Blackboard::get_jugador_entre_objeto() {
	return _jugador_entre_objeto;
}



unsigned short Blackboard::get_n_enemigos_zona() {
	return _n_enemigos_zona;
}

float Blackboard::get_distancia_enemigo_cercano() {
	return _distancia_enemigo_cercano;
}

float Blackboard::get_distancia_enemigo_lejano() {
	return _distancia_enemigo_lejano;
}

bool Blackboard::get_enemigos_tienen_arma() {
	return _enemigos_tienen_arma;
}



unsigned short Blackboard::get_n_pasillos() {
	return _n_pasillos;
}

//FALTA POR HACER
unsigned short Blackboard::get_distancia_pasillos(unsigned short _i_n_pasillo) {
	return 0;
}

unsigned short Blackboard::get_n_enemigos_min_pasillo() {
	return _n_enemigos_min_pasillo;
}

unsigned short Blackboard::get_n_paredes_cerca() {
	return _n_paredes_cerca;
}

unsigned short Blackboard::get_n_paredes_medio() {
	return _n_paredes_medio;
}

unsigned short Blackboard::get_n_paredes_lejos() {
	return _n_paredes_lejos;
}



unsigned short Blackboard::get_zonas_adyacentes() {
	return _zonas_adyacentes;
}

unsigned short Blackboard::get_zonas_enemigas() {
	return _zonas_enemigas;
}

unsigned short Blackboard::get_zonas_jugador() {
	return _zonas_jugador;
}



bool Blackboard::get_interactuable_en_zona_adyacente() {
	return _interactuable_en_zona_adyacente;
}

unsigned short Blackboard::get_id_zona_interactuable() {
	return _id_zona_interactuable;
}

bool Blackboard::get_interruptor_en_zona() {
	return _interruptor_en_zona;
}

bool Blackboard::get_interruptor_activado() {
	return _interruptor_activado;
}

unsigned short Blackboard::get_dist_jug_interruptor() {
	return _dist_jug_interruptor;
}

bool Blackboard::get_powerup_zona_adyacente() {
	return _powerup_zona_adyacente;
}

unsigned short Blackboard::get_id_zona_powerup() {
	return _id_zona_powerup;
}

