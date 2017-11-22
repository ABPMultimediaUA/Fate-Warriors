
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

#include <iostream>
#include "Game.h"

//#include "pruebas.cpp" //perdon, esk lo de este fichero es muy bestia os lo juro. Mejor que no lo veais

void funcion_red(){
	bool isServer;
	std::string input;

	isServer = true;

	std::cout << "(C)lient or (S)erver: ";
	std::cin >> input;

	if (input[0] == 'C' || input[0] == 'c')
		isServer = false;

	if(isServer){
		Game::game_instancia()->main_loop_servidor();
	}
	else{
		Game::game_instancia()->main_loop_cliente();
	}
}
int main(){

	Game *_game = Game::game_instancia();
	_game->game_crea_partida();
	_game->game_run();
	_game->game_fin_partida();
  //funcion_red();
	delete _game;

	std::cout << "Ha terminado" << std::endl;

}
