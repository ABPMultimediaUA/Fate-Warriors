#include "Blackboard.h"

#include "../Personajes/NPC.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Nivel/Nivel.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Zonas_Manager.h"
#include "../Zona.h"
#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"

Blackboard::Blackboard(NPC * npc_padre) {

	_accion = Nada;
	_npc_padre = npc_padre; 
	_decision = Decision_Quieto;
	_porcentaje_vida = 100;

}

Blackboard::~Blackboard() {
}

void Blackboard::actualiza_datos() {

	_porcentaje_vida=100*(_npc_padre->get_vida_actual()/_npc_padre->get_vida_maxima());

	actualizar_zonas();
	actualizar_characteres();
	
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
	return lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), objetivo_x, objetivo_y);
}

void Blackboard::actualizar_characteres(){
	Character ** characters = Game::game_instancia()->game_get_datos()->get_characters();
	unsigned long num_characters = Game::game_instancia()->game_get_datos()->get_num_characters();

	float _distancia_enemigo_mas_cercano = 1000;

	for (uint16_t cont=0; cont < num_characters; cont++){
		if(characters[cont]->get_equipo() != _npc_padre->get_equipo())
		{
			float _distancia = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), characters[cont]->getX(), characters[cont]->getZ());
			if(_distancia < _distancia_enemigo_mas_cercano){
				_distancia_enemigo_mas_cercano = _distancia;
				_enemigo_mas_cerca = characters[cont];
			}
		}		
    }

	if(_distancia_enemigo_mas_cercano < 30){
		_enemigo_mas_cerca_menos_de_30_metros = true;
	}
	else
		_enemigo_mas_cerca_menos_de_30_metros = false;

	if(_distancia_enemigo_mas_cercano < 6){
		_enemigo_mas_cerca_menos_de_6_metros = true;
	}
	else
		_enemigo_mas_cerca_menos_de_6_metros = false;

}

void Blackboard::actualizar_zonas(){
	Zonas_Manager * zonas_manager = Game::game_instancia()->game_get_datos()->get_zonas_manager();
	Zona** zonas = zonas_manager->get_zonas();
	unsigned long num_zonas = zonas_manager->get_n_zonas();

	Objeto_Motor * objeto_npc = _npc_padre->get_objeto_motor();
	bool encontrado = false;

	Zona * zona_mas_cerca_aux = nullptr;
	Zona * zona_enemiga_mas_cerca_aux = nullptr;
	Zona * zona_aliada_mas_cerca_aux = nullptr;
	float distancia_zona_mas_cerca = 0;
	float distancia_zona_enemiga_mas_cerca = 0;
	float distancia_zona_aliada_mas_cerca = 0;
	
	for (uint16_t cont=0; cont < num_zonas; cont++){
		if(Motor::Motor_GetInstance()->comprobar_colision(objeto_npc->getRigidBody(), zonas[cont]->getRigidBody()) == true){
			encontrado = true;
			_zona_actual = zonas[cont];
		}   
    }

	if(encontrado == false){
		_zona_actual = nullptr;
	}

	for (uint16_t cont=0; cont < num_zonas; cont++){
    	
		if(zonas[cont] != _zona_actual){

			float distancia_a_zona = lib_math_distancia_2_puntos(objeto_npc->getX(), objeto_npc->getZ(), zonas[cont]->getX(), zonas[cont]->getY());

			//Zona mas cerca
			if(distancia_a_zona < distancia_zona_mas_cerca){
				distancia_zona_mas_cerca = distancia_a_zona;
				zona_mas_cerca_aux = zonas[cont];
			}

			//Zona enemiga mas cerca
			if(zonas[cont]->get_equipo() != _npc_padre->get_equipo() && distancia_a_zona < distancia_zona_enemiga_mas_cerca){
				distancia_zona_enemiga_mas_cerca = distancia_a_zona;
				zona_enemiga_mas_cerca_aux = zonas[cont];
			}
			//Zona aliada mas cerca
			else if(zonas[cont]->get_equipo() == _npc_padre->get_equipo() && distancia_a_zona < distancia_zona_aliada_mas_cerca){
				distancia_zona_aliada_mas_cerca = distancia_a_zona;
				zona_aliada_mas_cerca_aux = zonas[cont];
			}
		}
    }

}