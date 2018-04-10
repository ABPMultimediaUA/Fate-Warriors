#include "Blackboard.h"

#include "../Personajes/NPC.h"
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

Blackboard::Blackboard(NPC * npc_padre) {

	_accion = Nada;
	_npc_padre = npc_padre; 
	_decision = Decision_Quieto;
	_porcentaje_vida = 100;

	_enemigo_mas_cerca = nullptr;
	_distancia_enemigo_mas_cerca = 10000000;

	_enemigo_mas_cerca_esta_cerca = false;
	_enemigo_mas_cerca_esta_muy_cerca = false;

}

Blackboard::~Blackboard() {
}

void Blackboard::actualiza_datos() {

	//actualizar_zonas(); //actualizarlo cuando va por la rama izquierda

	// Actualizar siempre:
	actualizar_pseudo_azar();
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

	if(_enemigo_mas_cerca != nullptr && _enemigo_mas_cerca->get_vida() > 0){

		bool otro_enemigo_mas_cerca = false;
		// Controla cuando se acerca mas otro enemigo
		float distancia_enemigo_mas_cercano = 10000000000;
		Character * enemigo_mas_cercano = nullptr;

		//_distancia_enemigo_mas_cerca =  10000000000;
		//_enemigo_mas_cerca = nullptr;

		for (uint16_t cont=0; cont < num_characters; cont++){
			if(characters[cont]->get_vida_actual()>0 && characters[cont]->get_equipo() != _npc_padre->get_equipo())
			{
				float _distancia = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), characters[cont]->getX(), characters[cont]->getZ());
				if(_distancia < distancia_enemigo_mas_cercano && characters[cont]->get_npcs_persiguiendome() < 2){
					distancia_enemigo_mas_cercano = _distancia;
					enemigo_mas_cercano = characters[cont];
				}
			}		
		}

		if(distancia_enemigo_mas_cercano < _distancia_enemigo_mas_cerca){
			otro_enemigo_mas_cerca = true;

			// Eliminamos al actual
			_enemigo_mas_cerca->decrementar_npcs_persiguiendome();
			_enemigo_mas_cerca = nullptr;
			_enemigo_mas_cerca_esta_cerca = false;
			_enemigo_mas_cerca_esta_muy_cerca = false;
			_distancia_enemigo_mas_cerca =  10000000000;

			// APuntamos al nuevo y actualizamos sus valores
			_enemigo_mas_cerca = enemigo_mas_cercano;
			_enemigo_mas_cerca->incrementar_npcs_persiguiendome();
			_distancia_enemigo_mas_cerca = distancia_enemigo_mas_cercano;

			if(distancia_enemigo_mas_cercano < 60){
				_enemigo_mas_cerca_esta_cerca = true;
			}
			else{
				_enemigo_mas_cerca_esta_cerca = false;
			}
				
			if(distancia_enemigo_mas_cercano < 6){
				_enemigo_mas_cerca_esta_muy_cerca = true;
			}
			else{
				_enemigo_mas_cerca_esta_muy_cerca = false;
			}

		}

		if(otro_enemigo_mas_cerca == false){

			float _distancia_enemigo_mas_cercano = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), _enemigo_mas_cerca->getX(), _enemigo_mas_cerca->getZ());

			// Esta lejos
			if(_distancia_enemigo_mas_cercano >= 60){
				_enemigo_mas_cerca->decrementar_npcs_persiguiendome();
				_enemigo_mas_cerca = nullptr;
				_enemigo_mas_cerca_esta_cerca = false;
				_enemigo_mas_cerca_esta_muy_cerca = false;
				_distancia_enemigo_mas_cerca =  10000000000;
				
			}
			else{
				_distancia_enemigo_mas_cerca =  _distancia_enemigo_mas_cercano;

				if(_distancia_enemigo_mas_cercano < 60){
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
				if(_distancia < _distancia_enemigo_mas_cercano && characters[cont]->get_npcs_persiguiendome() < 2){
					_distancia_enemigo_mas_cercano = _distancia;
					_enemigo_mas_cerca = characters[cont];
				}
				if( characters[cont]->get_npcs_persiguiendome() > 2){
					std::cout<< "MAS DE 2 ------------------ \n";
					std::cout<<characters[cont]->get_npcs_persiguiendome()<<std::endl;
				}
			}		
		}

		if(_enemigo_mas_cerca != nullptr){

			if(_distancia_enemigo_mas_cercano < 60){
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

/*
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

	Zona * zona_mas_cerca_aux_util = nullptr;
	Zona * zona_enemiga_mas_cerca_aux_util = nullptr;
	Zona * zona_aliada_mas_cerca_aux_util = nullptr;
	float distancia_zona_mas_cerca_util = 10000000000000;
	float distancia_zona_enemiga_mas_cerca_util = 10000000000000;
	float distancia_zona_aliada_mas_cerca_util = 10000000000000;


	if(_zona_actual != nullptr){

		//Salgo de la zona
		if(Motor::Motor_GetInstance()->comprobar_colision(objeto_npc->getRigidBody(), _zona_actual->getRigidBody()) == false){
			_zona_actual->decrementar_npcs_persiguiendome();
			_zona_actual = nullptr;
		}
	}
	else{ // Actualizo zonas

		Zona * zona_actual_aux = nullptr; // Es la zona en la que esta, la otra es la zona util (_zona_actual)

		for (uint16_t cont=0; cont < num_zonas && encontrado == false; cont++){
			if(Motor::Motor_GetInstance()->comprobar_colision(objeto_npc->getRigidBody(), zonas[cont]->getRigidBody()) == true
			){
				encontrado = true;
				zona_actual_aux = zonas[cont];

				if(zona_actual_aux->get_npcs_persiguiendome() < 3){
					_zona_actual = zonas[cont];
					_zona_actual->incrementar_npcs_persiguiendome();
				}
				else{
					_zona_actual = nullptr;
				}
					
			}   
		}

		for (uint16_t cont=0; cont < num_zonas; cont++){

			if(zonas[cont] != zona_actual_aux){

				int num_aliados_en_zona;

				if(_npc_padre->get_equipo() == Enum_Equipo_A){
					num_aliados_en_zona =zonas[cont]->_num_characters_equipo_A;
				}
				else{
					num_aliados_en_zona =zonas[cont]->_num_characters_equipo_B;
				}

				float distancia_a_zona = lib_math_distancia_2_puntos(_npc_padre->getX(), _npc_padre->getZ(), zonas[cont]->getX(), zonas[cont]->getY());

				//Zona mas cerca
				if(distancia_a_zona < distancia_zona_mas_cerca){
					distancia_zona_mas_cerca = distancia_a_zona;
					zona_mas_cerca_aux = zonas[cont];
				}

				if(distancia_a_zona < distancia_zona_mas_cerca_util
				&& num_aliados_en_zona < 3){
					distancia_zona_mas_cerca_util = distancia_a_zona;
					zona_mas_cerca_aux_util = zonas[cont];
				}

				//FIN Zona mas cerca

				//Zona enemiga mas cerca
				if(zonas[cont]->get_equipo() != _npc_padre->get_equipo() && distancia_a_zona < distancia_zona_enemiga_mas_cerca){
					distancia_zona_enemiga_mas_cerca = distancia_a_zona;
					zona_enemiga_mas_cerca_aux = zonas[cont];
				}

				if(zonas[cont]->get_equipo() != _npc_padre->get_equipo() 
				&& distancia_a_zona < distancia_zona_enemiga_mas_cerca_util
				&& num_aliados_en_zona < 3){
					distancia_zona_enemiga_mas_cerca_util = distancia_a_zona;
					zona_enemiga_mas_cerca_aux_util = zonas[cont];
				}

				//FIN Zona enemiga mas cerca

				//Zona aliada mas cerca
				if(zonas[cont]->get_equipo() == _npc_padre->get_equipo() && distancia_a_zona < distancia_zona_aliada_mas_cerca){
					distancia_zona_aliada_mas_cerca = distancia_a_zona;
					zona_aliada_mas_cerca_aux = zonas[cont];
				}

				if(zonas[cont]->get_equipo() == _npc_padre->get_equipo() 
				&& distancia_a_zona < distancia_zona_aliada_mas_cerca_util
				&& num_aliados_en_zona < 3){
					distancia_zona_aliada_mas_cerca_util = distancia_a_zona;
					zona_aliada_mas_cerca_aux_util = zonas[cont];
				}
				//FIN Zona aliada mas cerca
			}
		}


		if(zona_mas_cerca_aux_util != nullptr)
			_zona_mas_cerca = zona_mas_cerca_aux_util;
		else
			_zona_mas_cerca = zona_mas_cerca_aux;

		if(zona_enemiga_mas_cerca_aux_util != nullptr)
			_zona_enemiga_mas_cerca = zona_enemiga_mas_cerca_aux_util;
		else
			_zona_enemiga_mas_cerca = zona_enemiga_mas_cerca_aux;

		if(zona_aliada_mas_cerca_aux_util != nullptr)
			_zona_aliada_mas_cerca = zona_aliada_mas_cerca_aux_util;
		else
			_zona_aliada_mas_cerca = zona_aliada_mas_cerca_aux;

		// En caso de que solo quede 1 zona por conquistar y estes en ella
		if(_zona_mas_cerca == nullptr)
			_zona_mas_cerca = zona_actual_aux;
		if(_zona_enemiga_mas_cerca == nullptr)
			_zona_enemiga_mas_cerca = zona_actual_aux;
		if(_zona_aliada_mas_cerca == nullptr)
			_zona_aliada_mas_cerca = zona_actual_aux;

	}
	
	
}
*/

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