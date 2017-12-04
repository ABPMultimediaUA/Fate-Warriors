
/*
 *
 * Codigo base del proyecto
 *
 * Clase Main crea un objeto de clase game (clase vacia con solo la estructura)
 * en el método run hemos puesto un hola mundo.
 *
 *Cread una rama del código y añadidle vuestras pruebas
 *y trabajo
 */


#include "Game.h"
#include<iostream>

int main(){
	Game *_game = Game::game_instancia();
	_game->game_crea_partida();
	_game->game_run();
	_game->game_fin_partida();
	delete _game;

	std::cout << "Ha terminado" << std::endl;
}
