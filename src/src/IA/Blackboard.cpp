#include "Blackboard.h"

#include "Interfaz_Datos.h"

Blackboard::Blackboard(Interfaz_Datos& _i_interfaz, unsigned short _i_n_enemigo) {
	_n_npc = _i_n_enemigo;
	_tipo_npc[0] = Normal;
	_interfaz = &_i_interfaz;
	_distancia_jugador = 0;
	_decision = Decision_Quieto;
	_accion = Nada;
}

Blackboard::~Blackboard() {

}



void Blackboard::actualiza_datos() {
	_distancia_jugador = _interfaz->get_distancia_enemigo_personaje(_n_npc);
	// AQUI NO PUEDEN IR GETS
	// EN LUGAR DE GETS DEBE HABER PUNTEROS
	// AQUI SE HACEN CALCULOS SOBRE LAS VARIABLES QUE SE ACTUALIZAN AUTOMATICAMENTE (que van en punteros)
	// P. EJ. _se_acerca ES ALGO QUE NO SE VA A ACTUALIZAR, SE DEBE CALCULAR EN CADA ACTUALIZA_DATOS
}



void Blackboard::set_decision(enum Enum_Decisiones _i_decision) {
	_decision = _i_decision;
}

void Blackboard::set_accion(enum Enum_Acciones _i_accion) {
	_accion = _i_accion;
}



// Datos de identidad del NPC
unsigned short Blackboard::get_n_enemigo() {
	return _n_npc;
}

enum Enum_Tipo_Enemigo Blackboard::get_tipo_enemigo() {
	return _tipo_npc[0];
}

enum Enum_Tipo_Enemigo Blackboard::get_tipo_npc() {
	return _tipo_npc[0];
}



// Datos de estado
int16_t Blackboard::get_vida_actual() {
	return (*_vida_actual);
}


int16_t Blackboard::get_vida_max() {

}


float Blackboard::get_porcentaje_vida() {

}


uint8_t Blackboard::get_rango_ataque_normal() {

}


uint8_t Blackboard::get_rango_ataque_fuerte() {

}



// Datos de accion y decision propio de cada enemigo
enum Enum_Decisiones Blackboard::get_decision() {
	return _decision;
}

enum Enum_Acciones Blackboard::get_accion() {
	return _accion;
}

enum Enum_Tipo_Ataque Blackboard::get_ataque() {

}



// Datos de estado
int8_t Blackboard::get_level_of_detail() {
	return _level_of_detail;
}


bool Blackboard::get_alertado() {

}



// Datos de inventario
bool Blackboard::get_tiene_arma() {
	return (_tiene_arma_corta || _tiene_arma_larga);
}

bool Blackboard::get_tiene_arma_corta() {

}


uint8_t Blackboard::get_rango_arma_corta() {

}


bool Blackboard::get_tiene_arma_larga() {

}


uint8_t Blackboard::get_rango_arma_larga() {

}



// Blackboard del NPC contrario (PARA LOS ALIADOS PUEDEN SER DE CUALQUIER TIPO DE ENEMIGO Y PARA LOS ENEMIGOS DE TIPO ALIADO)
enum Enum_Decisiones Blackboard::get_decision_contrario() {

}


enum Enum_Acciones Blackboard::get_accion_contrario() {

}


enum Enum_Tipo_Ataque Blackboard::get_ataque_contrario() {

}


float Blackboard::get_x_contrario() {
	
}


float Blackboard::get_z_contrario() {
	
}


float Blackboard::get_distancia_contrario() {

}


int16_t Blackboard::get_vida_actual_npc_contrario() {
	
}


int16_t Blackboard::get_vida_max_npc_contrario() {
	
}


float Blackboard::get_porcentaje_vida_contrario() {

}


bool Blackboard::get_tiene_arma_contrario() {
	return (_tiene_arma_corta_contrario || _tiene_arma_larga_contrario);
}


bool Blackboard::get_tiene_arma_corta_contrario() {

}


bool Blackboard::get_tiene_arma_larga_contrario() {

}


bool Blackboard::get_se_acerca_contrario() {

}



//Con el jugador
enum Enum_Decisiones Blackboard::get_decision_jugador() {

}


enum Enum_Acciones Blackboard::get_accion_jugador() {

}


enum Enum_Tipo_Ataque Blackboard::get_ataque_jugador() {

}


float Blackboard::get_x_jugador() {
	
}


float Blackboard::get_z_jugador() {
	
}


float Blackboard::get_distancia_jugador() {
	return _distancia_jugador;
}


int16_t Blackboard::get_vida_actual_jugador() {
	
}


int16_t Blackboard::get_vida_max_jugador() {
	
}


float Blackboard::get_porcentaje_vida_jugador() {

}


bool Blackboard::get_tiene_arma_jugador() {
	return (_tiene_arma_corta_jugador || _tiene_arma_larga_jugador);
}


bool Blackboard::get_tiene_arma_corta_jugador() {

}


bool Blackboard::get_tiene_arma_larga_jugador() {

}


bool Blackboard::get_se_acerca() {

}


bool Blackboard::get_jugador_en_zona() {

}


uint8_t Blackboard::get_distancia_jugador_puerta_cerca() {

}


bool Blackboard::get_tiene_llave() {

}



//Con objetos
float Blackboard::get_distancia_objeto_cercano() {

}


bool Blackboard::get_jugador_entre_objeto() {

}	



//Con otros enemigos
float Blackboard::get_distancia_enemigo_cercano() {

}


float Blackboard::get_distancia_enemigo_lejano() {

}


bool Blackboard::get_enemigos_tienen_arma() {

}


int16_t Blackboard::get_vida_actual_enemigo_cerca() {

}


int16_t Blackboard::get_vida_maxima_enemigo_cerca() {

}


float Blackboard::get_porcentaje_vida_enemigo_cerca() {

}


uint8_t Blackboard::get_n_enemigos_cerca() {

}


uint8_t Blackboard::get_n_enemigos_medio() {

}


uint8_t Blackboard::get_n_enemigos_lejos() {

}


bool Blackboard::get_enemigo_alertado_medio() {

}


bool Blackboard::get_enemigo_alertado_lejos() {

}



//Con otros aliados
float Blackboard::get_distancia_aliado_cercano() {

}


float Blackboard::get_distancia_aliado_lejano() {

}


bool Blackboard::get_aliados_tienen_arma() {

}


int16_t Blackboard::get_vida_actual_aliado_cerca() {

}


int16_t Blackboard::get_vida_maxima_aliado_cerca() {

}


float Blackboard::get_porcentaje_vida_aliado_cerca() {

}


uint8_t Blackboard::get_n_aliados_cerca() {

}


uint8_t Blackboard::get_n_aliados_medio() {

}


uint8_t Blackboard::get_n_aliados_lejos() {

}



//Con informacion de la zona
int8_t Blackboard::get_n_enemigos_zona() {

}


int8_t Blackboard::get_n_aliados_zona() {

}


float Blackboard::get_n_aliados_por_n_enemigos() {

}



uint8_t Blackboard::get_n_pasillos() {

}


uint8_t Blackboard::get_distancia_pasillos() {

}


uint8_t Blackboard::get_n_enemigos_min_pasillo() {

}


uint8_t Blackboard::get_n_paredes_cerca() {

}


uint8_t Blackboard::get_n_paredes_medio() {

}


uint8_t Blackboard::get_n_paredes_lejos() {

}


bool Blackboard::get_jugador_entre_pasillo_y_yo() {

}



//Con otras zonas
uint8_t Blackboard::get_zonas_adyacentes() {

}


uint8_t Blackboard::get_zonas_enemigas() {

}


uint8_t Blackboard::get_zonas_jugador() {

}


enum Enum_zonas Blackboard::get_tipo_zona_cercana() {

}


bool Blackboard::get_puedo_ir_zona_cercana() {

}



//Con objetos interactuables
bool Blackboard::get_interruptor_en_zona() {

}


bool Blackboard::get_interruptor_activado() {

}


bool Blackboard::get_soy_enemigo_mas_cerca_interruptor() {

}


uint8_t Blackboard::get_dist_jug_interruptor() {

}


bool Blackboard::get_powerup_zona_adyacente() {

}


uint8_t Blackboard::get_id_zona_powerup() {

}