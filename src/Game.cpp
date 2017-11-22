#include "Game.h"

Game* Game::instancia=0;

Game* Game::game_instancia(){
	if(instancia == 0) {
		instancia = new Game();
	}
	return instancia;
}


Game::Game(){
	_datos = nullptr;
	_action_manager = nullptr;
}

Game::~Game(){
}

void Game::game_crea_partida() {
	_datos = new Datos_Partida();
	_action_manager = new Action_Manager();
}

void Game::game_fin_partida() {
	delete _datos;
	delete _action_manager;
}

void Game::game_update(){

}

void Game::game_run(){
	for(int cont=0; cont<10; cont++) {
		_action_manager->toma_decisiones();
		_action_manager->realiza_acciones();
	}
}


Datos_Partida* Game::game_get_datos() {
	return _datos;
}
