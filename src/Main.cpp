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

void funcion_red(){
	bool isServer;
	std::string input;

	isServer = true;

	std::cout << "(C)lient or (S)erver: ";
	std::cin >> input;

	if (input[0] == 'C' || input[0] == 'c')
		isServer = false;

	if(isServer){
		Game::getInstance()->main_loop_servidor();
	}
	else{
		Game::getInstance()->main_loop_cliente();
	}
}
int main(){
	Game* game = Game::getInstance();
	game->game_run();
	funcion_red();
}
