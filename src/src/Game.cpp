#include "Game.h"

#include "Action_Manager.h"
#include "Datos_Partida.h"
#include "Input.h"

#include "Entrada/Input.h"
#include "IA/Decision_Manager.h"
#include "Personajes/Player.h"
#include "Interfaz/Motor.h"
#include "Nivel/Nivel.h"
#include "Consumibles/Consumible_action.h"
#include "Trampas/Trampas_action.h"


#include <iostream>
#include <stack>

Game* Game::instancia = 0;

Game* Game::game_instancia(){
	if(instancia == 0)
		instancia= new Game();

	return instancia;
}
Game::Game() : _datos(nullptr), 
			   _action_manager(nullptr), 
			   _decision_manager(nullptr), 
			   _motor(nullptr),
			   _consumibles_action(nullptr),
			   _trampas_action(nullptr)
			   {
	_input_jugador = new Input();
}

Game::~Game(){

	delete _input_jugador;

	if(_datos != nullptr) {
		delete _datos;
		_datos = nullptr;
	}
	if(_decision_manager != nullptr) {
		delete _decision_manager;
		_decision_manager = nullptr;
	}
	if(_action_manager != nullptr) {
		delete _action_manager;
		_action_manager = nullptr;
	}
	if(_motor != nullptr) {
		delete _motor;
		_motor = nullptr;
	}
	if(_consumibles_action != nullptr) {
		delete _consumibles_action;
		_consumibles_action = nullptr;
	}

	if(_trampas_action != nullptr) {
		delete _consumibles_action;
		_consumibles_action = nullptr;
	}
}


void Game::crea_partida() {	

	_motor = Motor::Motor_GetInstance();
	_nivel=Nivel::nivel_instancia();
	_datos 				= new Datos_Partida(_input_jugador);
	_action_manager 	= new Action_Manager();
	_decision_manager 	= new Decision_Manager(_action_manager);
	_datos->inserta_npc_nivel();

	
	_consumibles_action = new Consumible_action();	
	_trampas_action 	= new Trampas_action();	
	



}

void Game::fin_partida() {

	//delete _datos;   ->da core dumped amigos
	delete _decision_manager;
	delete _action_manager;
	
	delete _motor;
	delete _consumibles_action;
	delete _trampas_action;
	delete _nivel;


	_datos 				= nullptr;
	_decision_manager 	= nullptr;
	_action_manager 	= nullptr;
	_consumibles_action = nullptr;
	_trampas_action 	= nullptr;
	_motor = nullptr;
}

void Game::run(){

}


void Game::update(double _i_tiempo_desde_ultimo_update){
	//std::cout << "UPDATE" << std::endl;
	Player *_player = _datos->get_player();
	_player->update();
	_nivel->Update();
	//_consumibles_action->comprobar_consumibles();
	_trampas_action->update();
	_player = nullptr;

	_motor->update(_i_tiempo_desde_ultimo_update);
		
//std::cout<<"ALTURA:    "<<_interfaz_grafica->getHeight()<<std::endl;
	_decision_manager->toma_decisiones();
}

void Game::render(float _i_interpolacion){
	//std::cout << "YEEEEEEEEEE" << std::endl;
	_motor->render();
}
  
Datos_Partida* Game::game_get_datos() {
	return _datos;
}

Action_Manager* Game::game_get_action_manager() {
	return _action_manager;
}

void Game::recibir_inputs() {
	_input_jugador->recibir_inputs();
}