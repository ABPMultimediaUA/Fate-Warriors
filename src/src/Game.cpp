#include "Game.h"

#include "Action_Manager.h"
#include "Datos_Partida.h"

#include "Entrada/Input.h"
#include "IA/Decision_Manager.h"
#include "Personajes/Player.h"
#include "Interfaz/Interfaz.h"
#include "Nivel/Nivel.h"

#include <iostream>
#include <stack>

Game* Game::instancia = 0;

Game* Game::game_instancia(){
	if(instancia == 0)
		instancia= new Game();

	return instancia;
}
Game::Game() : _datos(nullptr), _action_manager(nullptr), _decision_manager(nullptr), _interfaz_grafica(nullptr){

}

Game::~Game(){
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
	if(_interfaz_grafica != nullptr) {
		delete _interfaz_grafica;
		_interfaz_grafica = nullptr;
	}
}


void Game::crea_partida() {	
	_interfaz_grafica = Interfaz::Interfaz_getInstance(); //Moose Ninja || 1280 width || 720 height
	_datos = new Datos_Partida();
	_action_manager = new Action_Manager();
	_decision_manager = new Decision_Manager(_action_manager);

	//Nivel* _nivel1=new Nivel("Nivel.txt");
}

void Game::fin_partida() {
	delete _datos;
	delete _decision_manager;
	delete _action_manager;
	delete _interfaz_grafica;

	_datos = nullptr;
	_decision_manager = nullptr;
	_action_manager = nullptr;
	_interfaz_grafica = nullptr;
}

void Game::run(){

}


void Game::update(double _i_tiempo_desde_ultimo_update){
	Player *_player = _datos->get_player();
	_player->update();
	_player = nullptr;
	_decision_manager->toma_decisiones();
}

void Game::render(float _i_interpolacion){
	_interfaz_grafica->Interfaz_Update(); //Camara->update();
	_interfaz_grafica->Interfaz_Render();
}
  
Datos_Partida* Game::game_get_datos() {
	return _datos;
}