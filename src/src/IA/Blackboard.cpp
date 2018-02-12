#include "Blackboard.h"

#include "Interfaz_Datos.h"

#include "../Personajes/NPC.h"

#include "../Interfaz_Libs/Lib_Math.h"

#include "../Nivel/Nivel.h"

Blackboard::Blackboard(NPC * npc_padre) {

	_npc_padre = npc_padre; 
	_decision = Decision_Quieto;
	_objetivo = nullptr;
	_porcentaje_vida = 100;
}

Blackboard::~Blackboard() {
}

void Blackboard::actualiza_datos() {

	_porcentaje_vida=100*(_npc_padre->get_vida_actual()/_npc_padre->get_vida_maxima());
	
	// AQUI NO PUEDEN IR GETS
	// EN LUGAR DE GETS DEBE HABER PUNTEROS
	// AQUI SE HACEN CALCULOS SOBRE LAS VARIABLES QUE SE ACTUALIZAN AUTOMATICAMENTE (que van en punteros)
	// P. EJ. _se_acerca ES ALGO QUE NO SE VA A ACTUALIZAR, SE DEBE CALCULAR EN CADA ACTUALIZA_DATOS
}

void Blackboard::set_decision(enum Enum_Decisiones _i_decision) {
	_decision = _i_decision;
}

float Blackboard::get_porcentaje_vida() {
	return _porcentaje_vida;
}

// Datos de accion y decision propio de cada enemigo
enum Enum_Decisiones Blackboard::get_decision() {
	return _decision;
}

// Datos de estado
int8_t Blackboard::get_level_of_detail() {
	//std::cout<<"lvl of detail: "<<(int)_zona->get_lod()<<std::endl;
	return _zona->get_lod();
}

float Blackboard::get_distancia_objetivo(){
	return 1;
}