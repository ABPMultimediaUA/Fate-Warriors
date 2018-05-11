#include "Blackboard.h"

#include "../Personajes/NPC.h"
#include "../Personajes/NPC_Manager.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Nivel/Nivel.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "../Zonas/Zonas_Manager.h"
#include "../Zonas/Zona.h"
#include "../Personajes/Inventario.h"
#include "../Interactuables/Interruptor.h"
#include "../Interactuables/Puerta_Pincho.h"
#include "../Interfaz/Motor.h"
#include "../Interfaz/Objeto_Motor.h"
#include "../Armas/Armas_Manager.h"
#include "../Armas/Arma.h"
#include "../Consumibles/Consumible_Manager.h"
#include "../Consumibles/Consumible.h"
#include "../Consumibles/Consumible_Agua.h"
#include "../Consumibles/Consumible_Patata.h"
#include "../Consumibles/Consumible_Carne.h"

#include <iostream>

Blackboard::Blackboard(NPC * npc_padre) {

	_accion = Nada;
	_npc_padre = npc_padre; 
	_decision = Decision_Quieto;
	_porcentaje_vida = 100;

	_enemigo_mas_cerca = nullptr;
	_distancia_enemigo_mas_cerca = 10000000;

	_enemigo_mas_cerca_esta_cerca = false;
	_enemigo_mas_cerca_esta_muy_cerca = false;

	_zona_actual = nullptr;
	_estoy_en_mi_zona = false;

}

Blackboard::~Blackboard() {
}

void Blackboard::actualiza_datos() {

	//actualizar_zonas(); //actualizarlo cuando va por la rama izquierda

	// Actualizar siempre:
	actualizar_pseudo_azar();
	actualizar_characteres();
	actualizar_zonas();
	
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

	if(_enemigo_mas_cerca != nullptr && _enemigo_mas_cerca->get_vida() > 0){

		float _distancia_enemigo_mas_cercano = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), _enemigo_mas_cerca->getX(), _enemigo_mas_cerca->getZ());

		// Esta lejos
		if(_distancia_enemigo_mas_cercano >= 10000000000){
			_enemigo_mas_cerca->decrementar_npcs_persiguiendome();
			_enemigo_mas_cerca = nullptr;
			_enemigo_mas_cerca_esta_cerca = false;
			_enemigo_mas_cerca_esta_muy_cerca = false;
			_distancia_enemigo_mas_cerca =  10000000000;
			
		}
		else{
			_distancia_enemigo_mas_cerca =  _distancia_enemigo_mas_cercano;

			if(_distancia_enemigo_mas_cercano < 10000000000){
				_enemigo_mas_cerca_esta_cerca = true;
			}
			else{
				_enemigo_mas_cerca_esta_cerca = false;
			}
				
			if(_distancia_enemigo_mas_cercano < 6){
				_enemigo_mas_cerca_esta_muy_cerca = true;
			}
			else{
				_enemigo_mas_cerca_esta_muy_cerca = false;
			}
				
		}


		if(_npc_padre->get_zona()->esta_jugador_en_zona() == true && _enemigo_mas_cerca_esta_cerca == true) { // TRUE, es 1 
			
		} 
		else if(_enemigo_mas_cerca != nullptr){ 
			_enemigo_mas_cerca->decrementar_npcs_persiguiendome(); 
			_enemigo_mas_cerca = nullptr; 
			_enemigo_mas_cerca_esta_cerca = false; 
			_enemigo_mas_cerca_esta_muy_cerca = false; 
			_distancia_enemigo_mas_cerca =  10000000000; 
		} 

	}
	
	else{ // En este caso analizara todos los enemigos que pueda perseguir

		float _distancia_enemigo_mas_cercano = 10000000000;

		_distancia_enemigo_mas_cerca =  10000000000;
		_enemigo_mas_cerca = nullptr;

		for (uint16_t cont=0; cont < num_characters; cont++){
			if(characters[cont]->get_vida_actual()>0 && characters[cont]->get_equipo() != _npc_padre->get_equipo())
			{
				float _distancia = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), characters[cont]->getX(), characters[cont]->getZ());
				if(_distancia < _distancia_enemigo_mas_cercano && characters[cont]->get_npcs_persiguiendome() < 2 /*((rand() % 3)+1)*/){
					_distancia_enemigo_mas_cercano = _distancia;
					_enemigo_mas_cerca = characters[cont];
				}
				else if (estoy_mas_cerca_que_otro(characters[cont], _distancia) == true){
					_distancia_enemigo_mas_cercano = _distancia_enemigo_mas_cerca;
				}
				//if( characters[cont]->get_npcs_persiguiendome() > 2){
					//std::cout<< "MAS DE 2 ------------------ \n";
					//std::cout<<characters[cont]->get_npcs_persiguiendome()<<std::endl;
				//}
			}		
		}

		if(_enemigo_mas_cerca != nullptr){

			if(_distancia_enemigo_mas_cercano < 10000000000){
				_distancia_enemigo_mas_cerca =  _distancia_enemigo_mas_cercano;
				_enemigo_mas_cerca->incrementar_npcs_persiguiendome();
				_enemigo_mas_cerca_esta_cerca = true;
			}
			else{
				_enemigo_mas_cerca = nullptr;
				_distancia_enemigo_mas_cerca =  10000000000;
				_enemigo_mas_cerca_esta_cerca = false;
			}
				
			if(_distancia_enemigo_mas_cercano < 6){
				_enemigo_mas_cerca_esta_muy_cerca = true;
			}
			else
				_enemigo_mas_cerca_esta_muy_cerca = false;

		}
		else{
			_distancia_enemigo_mas_cerca =  10000000000;
			_enemigo_mas_cerca_esta_cerca = false;
			_enemigo_mas_cerca_esta_muy_cerca = false;
		}
	}
} 

bool Blackboard::estoy_mas_cerca_que_otro(Character * player, float distancia){
	bool res = false;
	NPC ** characters = Game::game_instancia()->game_get_datos()->get_npc_manager()->get_npcs();
	unsigned long num_characters = Game::game_instancia()->game_get_datos()->get_npc_manager()->get_n_npc();

	for (uint16_t cont=0; cont < num_characters && res == false; cont++){
		if(characters[cont]->get_vida_actual()>0 && characters[cont]->get_blackboard()->_enemigo_mas_cerca != nullptr)
		{
			float _distancia2 = lib_math_distancia_2_puntos(player->getX(), player->getZ(), characters[cont]->getX(), characters[cont]->getZ());
			
			if(distancia < _distancia2){
				_enemigo_mas_cerca = player;
				_distancia_enemigo_mas_cerca = distancia;
				res = true;
				characters[cont]->get_blackboard()->_enemigo_mas_cerca->decrementar_npcs_persiguiendome();
				characters[cont]->get_blackboard()->_enemigo_mas_cerca = nullptr;
				characters[cont]->get_blackboard()->_enemigo_mas_cerca_esta_cerca = false;;
				characters[cont]->get_blackboard()->_enemigo_mas_cerca_esta_muy_cerca = false;
				characters[cont]->get_blackboard()->_distancia_enemigo_mas_cerca =  10000000000;
			}
		}		
	}
	return res;
}


void Blackboard::actualizar_zonas(){
	Objeto_Motor * objeto_npc = _npc_padre->get_objeto_motor();

	//Salgo de la zona
	if(Motor::Motor_GetInstance()->comprobar_colision(objeto_npc->getRigidBody(), _npc_padre->get_zona()->getRigidBody()) == true){
		_estoy_en_mi_zona = true;
	}
	else{
		_estoy_en_mi_zona = false;
	}

	// Distancia con su posicion de respawn

	float _distancia = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), _npc_padre->get_pos_x_azar_en_zona(), _npc_padre->get_pos_y_azar_en_zona());
	
	if(_distancia < 4){
		_muy_cerca_de_mi_posicion_respawn = true;
	}
	else{
		_muy_cerca_de_mi_posicion_respawn = false;
	}
}


/*
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
		if(dynamic_cast<Consumible_Agua*>((*lista_consumibles)[i]) == NULL){

			if(dynamic_cast<Consumible_Patata*>((*lista_consumibles)[i]) != NULL && _porcentaje_vida > 90 ||
				dynamic_cast<Consumible_Carne*>((*lista_consumibles)[i]) != NULL && _porcentaje_vida > 90){
				break;
			}

			float distancia_a_objeto = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), (*lista_consumibles)[i]->getX(), (*lista_consumibles)[i]->getZ());

			if(distancia_a_objeto < distancia_objeto_mas_cerca){
				distancia_objeto_mas_cerca = distancia_a_objeto;
				objeto_mas_cerca_aux = (*lista_consumibles)[i];
			}
		}
  	}

	if(_enemigo_mas_cerca != nullptr && distancia_objeto_mas_cerca <= _distancia_enemigo_mas_cerca){
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

	if(distancia_objeto_mas_cerca < 2){
		_objeto_mas_cerca_esta_muy_cerca = true;
	}
	else
		_objeto_mas_cerca_esta_muy_cerca = false;

	_objeto_mas_cerca = objeto_mas_cerca_aux;

}



void Blackboard::actualizar_interruptores(){

	/*if(_zona_actual != nullptr && _enemigo_mas_cerca == nullptr){


		if(_interruptor_cerca_util != nullptr){ // Se actualiza el interruptor objetivo actual

			if(!_interruptor_cerca_util->get_puerta()->ha_pasado_tiempo_suficiente()){

				_interruptor_cerca_util->decrementar_npcs_persiguiendome();
				_interruptor_cerca_util = nullptr;
				_interruptor_esta_cerca = false;
			}
			else{

				float distancia_a_interruptor = lib_math_distancia_2_puntos(_interruptor_cerca_util->getX(), _interruptor_cerca_util->getZ(), _npc_padre->getX(), _npc_padre->getZ());
			
				if(distancia_a_interruptor < 5){
					_interruptor_esta_cerca = true;
				}
				else{
					_interruptor_esta_cerca = false;
				}

			}
			

		}
		else{ // Se analizan de nuevo los interruptores

			Interruptor * interruptor_aux = nullptr;

			float distancia_a_interruptor_mas_cerca = 1000000000;

			std::vector<Interruptor*> interruptores = _zona_actual->get_interruptores_asociados();

			short tamanio = interruptores.size();

			for(short i = 0; i < tamanio; i++){
				Zona* zona1 = interruptores[i]->get_puerta()->get_zona_1();
				Zona* zona2 = interruptores[i]->get_puerta()->get_zona_2();

				float distancia_a_interruptor = lib_math_distancia_2_puntos(interruptores[i]->getX(), interruptores[i]->getZ(), _npc_padre->getX(), _npc_padre->getZ());

				if(distancia_a_interruptor < distancia_a_interruptor_mas_cerca 
				&& interruptores[i]->get_puerta()->ha_pasado_tiempo_suficiente() 
				&& interruptores[i]->get_npcs_persiguiendome() < 1){

					if(zona1 != _zona_actual && zona1->get_equipo() != _npc_padre->get_equipo()){

						int num_enemigos_zona = 0;

						if(_npc_padre->get_equipo() == Enum_Equipo_A){
							num_enemigos_zona = zona1->_num_characters_equipo_B;
						}
						else{
							num_enemigos_zona = zona1->_num_characters_equipo_A;
						}

						if(num_enemigos_zona > 2){
							interruptor_aux = interruptores[i];
							distancia_a_interruptor_mas_cerca = distancia_a_interruptor;
						}
						
					}
					else if(zona2 != _zona_actual && zona2->get_equipo() != _npc_padre->get_equipo()){

						int num_enemigos_zona = 0;

						if(_npc_padre->get_equipo() == Enum_Equipo_A){
							num_enemigos_zona = zona2->_num_characters_equipo_B;
						}
						else{
							num_enemigos_zona = zona2->_num_characters_equipo_A;
						}

						if(num_enemigos_zona > 2){
							interruptor_aux = interruptores[i];
							distancia_a_interruptor_mas_cerca = distancia_a_interruptor;
						}
					}
				}
			}

			_interruptor_cerca_util = interruptor_aux;

			if(interruptor_aux != nullptr){

				interruptor_aux->incrementar_npcs_persiguiendome();

				float distancia_a_interruptor = lib_math_distancia_2_puntos(_interruptor_cerca_util->getX(), _interruptor_cerca_util->getZ(), _npc_padre->getX(), _npc_padre->getZ());
			
				if(distancia_a_interruptor < 5){
					_interruptor_esta_cerca = true;
				}
				else{
					_interruptor_esta_cerca = false;
				}
					

			}


		}
	}
	else{

		if(_interruptor_cerca_util != nullptr){
			_interruptor_cerca_util->decrementar_npcs_persiguiendome();
		}
		_interruptor_cerca_util = nullptr;
		_interruptor_esta_cerca = false;
	}
	
}

void Blackboard::actualizar_datos_npc_padre(){

	_porcentaje_vida=100*(_npc_padre->get_vida_actual()/_npc_padre->get_vida_maxima());

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
*/
void Blackboard::equipar_arma_larga_distancia(){
	_npc_padre->get_inventario()->seleccionar_arma_distancia_NPC();
}

void Blackboard::equipar_arma_corta_distancia(){
	_npc_padre->get_inventario()->seleccionar_arma_cerca_NPC();
}

void Blackboard::actualizar_pseudo_azar(){
	int x = _npc_padre->getX();
	int z = _npc_padre->getZ();
	
	if(rand() % 2 == 0){
		_ataque_a_realizar = Ataque_Normal;
		_puedo_esquivar = true;
		//std::cout <<"Entra 1 \n";
	}
	else{
		_ataque_a_realizar = Ataque_Fuerte;
		_puedo_esquivar = false;
		//std::cout <<"Entra 2 \n";
	}
}