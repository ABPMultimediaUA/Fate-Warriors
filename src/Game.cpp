#include "Game.h"
#include "Nivel.h"
#include "Cliente.h"
#include "Servidor.h"
#include <iostream>

Game* Game::instancia = 0;

Game* Game::getInstance(){
	if(instancia == 0)
		instancia= new Game();

	return instancia;
}

Game::Game(){
	enemigo1 = NULL;
	yoplayer = new Hero*[2];
	yoplayer[0] = NULL;
	yoplayer[1] = NULL;
}

void Game::anyadir_jugador(){
	yoplayer[1] = new Hero();
}

void Game::actualizar_jugador_coop(float x, float y){
	yoplayer[1]->setPosition(x,y);
}

void Game::actualizar_posicion_enemigo(float x, float y, short id){
	enemigo1->setPosition(x,y);
}

void Game::main_loop_servidor(){
	char portstring[30];
	unsigned short port;
	Servidor* servidor = Servidor::getInstance();

	std::cout << "Type port to listen " << std::endl;
	std::cin >> portstring;
	port = (unsigned short) strtoul(portstring, NULL, 0);

	enemigo1 = new Enemy(1);
	yoplayer[0] = new Hero();
	yoplayer[1] = new Hero();


	servidor->start_server(port, 3);

	sf::RenderWindow window(sf::VideoMode(900, 600), "Networking Test");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()){
		servidor->check_and_send_mesages();
		enemigo1->update(); // IA

		window.clear();
		window.display();
	}
	delete(servidor);
}

void Game::main_loop_cliente(){
	Cliente* cliente = Cliente::getInstance();
	char portstring [30];
	unsigned short port;
	char iptoconnect [30];

	std::cout << "Type port to connect " << std::endl;
	std::cin >> portstring;
	port = (unsigned short) strtoul(portstring, NULL, 0);

	std::cout << "Type ip to connect to" << std::endl;
	std::cin >> iptoconnect;

	enemigo1 = new Enemy(1);
	cliente->start_client(iptoconnect, port);
	yoplayer[0] = new Hero();

	sf::RenderWindow window(sf::VideoMode(900, 600), "Networking Test");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen()){
		//Bucle prepartida
		while(!cliente->get_start()){
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
				cliente->send_game_start();
		}

		//Bucle partida
		sf::Event e;
		while(window.pollEvent(e)){
			if(e.type == sf::Event::Closed){
				cliente->Cerrar_peer();
				window.close();
			}
		}

		if(window.hasFocus()){
			std::vector<Input_key> inputs = yoplayer[0]->update();

			if(inputs.size()>0){
				cliente->send_player_move (inputs, inputs.size());
			}
		}
		cliente->check_and_send_mesages();

		window.clear();

		window.draw(*(enemigo1->get_player()));
		window.draw(*(yoplayer[0]->get_player()));

		if(yoplayer[1]!= NULL)
			window.draw(*(yoplayer[1]->get_player()));

		window.display();
	}
	delete(cliente);
	delete(enemigo1);
}

void Game::game_update(){

}
void Game::actualizar_by_id(short id, Input_key actionkey){
	yoplayer[id]->update_extern(actionkey);
}

void Game::game_run(){
		Nivel* _nivel1=new Nivel("Nivel.txt");


}
