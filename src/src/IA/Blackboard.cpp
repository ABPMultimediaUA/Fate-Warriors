#include "Blackboard.h"

#include "../Personajes/NPC.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Nivel/Nivel.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Zonas_Manager.h"
#include "../Zona.h"
#include "../Inventario.h"
#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"
#include "../Armas/Armas_Manager.h"
#include "../Armas/Arma.h"
#include "../Consumibles/Consumible_Manager.h"
#include "../Consumibles/Consumible.h"

Blackboard::Blackboard(NPC * npc_padre) {

	_accion = Nada;
	_npc_padre = npc_padre; 
	_decision = Decision_Quieto;
	_porcentaje_vida = 100;


	_enemigo_mas_cerca = nullptr;
	_distancia_enemigo_mas_cerca = 10000000;

	_zona_actual = nullptr;
	_zona_mas_cerca = nullptr;
	_zona_enemiga_mas_cerca = nullptr;
	_zona_aliada_mas_cerca = nullptr;

}

Blackboard::~Blackboard() {
}

void Blackboard::actualiza_datos() {

	//_porcentaje_vida=100*(_npc_padre->get_vida_actual()/_npc_padre->get_vida_maxima());

	actualizar_zonas(); //actualizarlo cuando va por la rama izquierda

	// Actualizar siempre:
	actualizar_pseudo_azar();
	actualizar_datos_npc_padre();
	actualizar_characteres();
	actualizar_objetos();
	
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

	float _distancia_enemigo_mas_cercano = 10000000000;

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

	_distancia_enemigo_mas_cerca = _distancia_enemigo_mas_cercano;

	if(_distancia_enemigo_mas_cercano < 1000000){
		_enemigo_mas_cerca_esta_cerca = true;
	}
	else
		_enemigo_mas_cerca_esta_cerca = false;

	if(_distancia_enemigo_mas_cercano < 6){
		_enemigo_mas_cerca_esta_muy_cerca = true;
	}
	else
		_enemigo_mas_cerca_esta_muy_cerca = false;

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
	float distancia_zona_mas_cerca = 10000000000000;
	float distancia_zona_enemiga_mas_cerca = 10000000000000;
	float distancia_zona_aliada_mas_cerca = 10000000000000;
	
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

			float distancia_a_zona = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), zonas[cont]->getX(), zonas[cont]->getY());

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

	_zona_mas_cerca = zona_mas_cerca_aux;
	_zona_enemiga_mas_cerca = zona_enemiga_mas_cerca_aux;
	_zona_aliada_mas_cerca = zona_aliada_mas_cerca_aux;

}

void Blackboard::actualizar_objetos(){

	Objeto * objeto_mas_cerca_aux = nullptr;
	float distancia_objeto_mas_cerca = 10000000000;

	// Armas
	std::vector<Arma*>* lista_armas = Game::game_instancia()->game_get_datos()->get_armas_manager()->get_armas();
	int num_armas = (*lista_armas).size();

	for (short i = 0; i < num_armas; i++) {
    	float distancia_a_objeto = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), (*lista_armas)[i]->getX(), (*lista_armas)[i]->getZ());

		if(distancia_a_objeto < distancia_objeto_mas_cerca){
			distancia_objeto_mas_cerca = distancia_a_objeto;
			objeto_mas_cerca_aux = (*lista_armas)[i];
		}
  	}

	// Power-ups y consumibles
	std::vector<Consumible*>* lista_consumibles = Game::game_instancia()->game_get_datos()->get_Consumible_Manager()->get_consumibles();
	int num_consumibles = (*lista_consumibles).size();

	for (short i = 0; i < num_consumibles; i++) {
    	float distancia_a_objeto = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), (*lista_consumibles)[i]->getX(), (*lista_consumibles)[i]->getZ());

		if(distancia_a_objeto < distancia_objeto_mas_cerca){
			distancia_objeto_mas_cerca = distancia_a_objeto;
			objeto_mas_cerca_aux = (*lista_consumibles)[i];
		}
  	}

	if(distancia_objeto_mas_cerca <= _distancia_enemigo_mas_cerca){
		_objeto_mas_cerca_que_enemigo_mas_cerca = true;
	}
	else{
		_objeto_mas_cerca_que_enemigo_mas_cerca = false;
	}

	if(distancia_objeto_mas_cerca < 15){
		_objeto_mas_cerca_esta_cerca = true;
	}
	else
		_objeto_mas_cerca_esta_cerca = false;

	if(distancia_objeto_mas_cerca < 1){
		_objeto_mas_cerca_esta_muy_cerca = true;
	}
	else
		_objeto_mas_cerca_esta_muy_cerca = false;

	_objeto_mas_cerca = objeto_mas_cerca_aux;

}

void Blackboard::actualizar_datos_npc_padre(){

	Inventario * inventario = _npc_padre->get_inventario();

	if(inventario->get_objeto_distancia() != nullptr){
		_tengo_arma_larga_distancia = true;
	}
	else{
		_tengo_arma_larga_distancia = false;
	}

	if(inventario->get_objeto_cerca() != nullptr){
		_tengo_arma_corta_distancia = true;
	}
	else{
		_tengo_arma_corta_distancia = false;
	}
}

void Blackboard::equipar_arma_larga_distancia(){
	_npc_padre->get_inventario()->seleccionar_arma_distancia_NPC();
}

void Blackboard::equipar_arma_corta_distancia(){
	_npc_padre->get_inventario()->seleccionar_arma_cerca_NPC();
}

void Blackboard::actualizar_pseudo_azar(){
	int x = _npc_padre->getX();
	int z = _npc_padre->getZ();
	
	if(uint16_t(x+z)%2==0){
		_ataque_a_realizar = Ataque_Normal;
		_puedo_esquivar = true;
	}
	else{
		_ataque_a_realizar = Ataque_Fuerte;
		_puedo_esquivar = false;
	}
}


