#include "Game.h"

#include "Action_Manager.h"
#include "Datos_Partida.h"
#include "Input.h"

#include "Entrada/Controles.h"
#include "IA/Decision_Manager.h"
#include "Personajes/Player.h"
#include "Interfaz/Motor.h"
#include "Nivel/Nivel.h"
#include "Consumibles/Consumible_Action.h"
#include "Tiempo/Time.h"
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
	_motor->asigna_input(_input_jugador);
	_nivel=Nivel::nivel_instancia();
	_datos 				= new Datos_Partida(_input_jugador);
	_action_manager 	= new Action_Manager();
	_decision_manager 	= new Decision_Manager(_action_manager);
	_datos->inserta_npc_nivel();

	
	_consumibles_action = new Consumible_Action();	
	_trampas_action 	= new Trampas_action();	

	update_actual = &Game::update_partida;
	render_actual = &Game::render_partida;
}

void Game::fin_partida() {

	delete _datos;
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


// Llama a la funcion update en el momento necesario
void Game::update(double _i_tiempo_desde_ultimo_update){
	(*this.*update_actual)(_i_tiempo_desde_ultimo_update);
}


void Game::update_partida(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Partida" << std::endl;
	Player *_player = _datos->get_player();
	_player->update();
	_nivel->Update();
	_consumibles_action->comprobar_consumibles();
	_trampas_action->update();
	_player = nullptr;

	_motor->update(_i_tiempo_desde_ultimo_update);
		
	_decision_manager->toma_decisiones();

    // Reinicia el procesado y lectura de inputs
    _input_jugador->reiniciar_inputs();
}


void Game::update_pausa(double _i_tiempo_desde_ultimo_update){
	//std::cout << "Update Pausa" << std::endl;
    if(_input_jugador->get_pausa() && Time::Instance()->get_tiempo_inicio_pausa() > 250){
    	cambio_a_update_partida();
    }

    if(update_actual == &Game::update_partida) {
		update_partida(_i_tiempo_desde_ultimo_update);	
    }
}

void Game::render(float _i_interpolacion){
	(*this.*render_actual)(_i_interpolacion);
}

void Game::render_partida(float _i_interpolacion){
	_motor->render(_i_interpolacion);
}

void Game::render_pausa(float _i_interpolacion){
	_motor->render(1);
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


void Game::cambio_a_update_partida() {
	update_actual = &Game::update_partida;
	render_actual = &Game::render_partida;
	Time::Instance()->reanudar_reloj();
}

void Game::cambio_a_update_pausa() {
	update_actual = &Game::update_pausa;
	render_actual = &Game::render_pausa;
	Time::Instance()->pausar_reloj();
}
