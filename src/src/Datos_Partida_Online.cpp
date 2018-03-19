#include "Datos_Partida_Online.h"

#include "Interactuable_Manager.h"
#include "Interfaz/Motor.h"
#include "Personajes/Player.h"
#include "Personajes/Player_Online.h"
#include "Personajes/NPC_Manager.h"
#include "Personajes/NPC.h"
#include "Armas/Armas_Manager.h"
#include "Consumibles/Consumible_Manager.h"
#include "Trampas/Trampas_manager.h"
#include "Llave.h"
#include "Puerta.h"
#include "Zonas_Manager.h"
#include <iostream>
#include "Network/Cliente.h"
#include "Network/Servidor.h"

//#include "Consumibles/Respawn_Points.h"


Datos_Partida_Online::Datos_Partida_Online(Input* _i_input){ 
  float mult = 4.9212625; 

	std::string input;

		isServer = true;

		std::cout << "(C)lient or (S)erver: ";
		std::cin >> input;

		if (input[0] == 'C' || input[0] == 'c')
			isServer = false;

		if(isServer){
			char portstring[30];
			unsigned short port;
			Servidor* servidor = Servidor::getInstance();

			std::cout << "Type port to listen " << std::endl;
			std::cin >> portstring;
			port = (unsigned short) strtoul(portstring, NULL, 0);

			servidor->start_server(port, 3);
			_jugador = nullptr;
		}
		else{
			Cliente* cliente = Cliente::getInstance();
			cliente->send_game_start();

			char portstring [30];
			unsigned short port;
			char iptoconnect [30];

			isServer = false;

			std::cout << "Type port to connect " << std::endl;
			std::cin >> portstring;
			port = (unsigned short) strtoul(portstring, NULL, 0);

			std::cout << "Type ip to connect to" << std::endl;
			std::cin >> iptoconnect;
			_jugador = new Player( 0, 12.5*mult, 0, 9.5*mult, _i_input, false); 
		  	_jugadores_online_incluyendo_player.push_back(_jugador);

			cliente->asociar_player(_jugador);
			std::cout << _jugador  <<"soy el de esta pantalla \n";
			cliente->start_client(iptoconnect, port);
		}




  _consumibles_manager   =   new Consumible_Manager(); 
  _trampas_manager     =   new Trampas_manager(); 
  _armas_manager       =  new Armas_Manager(); 
//  _respawn_Points      =  new Respawn_Points(); 
  _zonas_manager       =  new Zonas_Manager(); 
  _interactuable_manager   =   new Interactuable_Manager(_zonas_manager->get_zonas()); 
  _npc_manager        =   new NPC_Manager(); 
 
   
 
  NPC ** _npcs = _npc_manager->get_npcs(); 
  uint16_t _cont, _n_npcs; 
  _n_npcs = _npc_manager->get_n_npc(); 
 
   
  for(_cont = 0; _cont < _n_npcs; _cont++) { 
    _npcs[_cont]->comprobar_si_asignar_arma_y_asignarla(_armas_manager); 
  } 
	_num_characters = _n_npcs + 1;
	_characters = new Character*[_num_characters];

	for(_cont = 0; _cont < _n_npcs; _cont++) {
		_characters[_cont] = _npcs[_cont];
	}
	_characters[_cont] = _jugador;

}

Datos_Partida_Online::~Datos_Partida_Online() {
	delete _jugador;
	delete _trampas_manager;
	delete _consumibles_manager;
	delete _armas_manager;

	delete _npc_manager;
  	delete _interactuable_manager;
//	delete _respawn_Points;
	delete _zonas_manager;

	delete [] _characters;
	Cliente* cliente = Cliente::getInstance();
	cliente->Cerrar_peer();
}

Player* Datos_Partida_Online::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida_Online::get_npc_manager() {
	return _npc_manager;
}

Trampas_manager * Datos_Partida_Online::get_trampas_manager(){
	return _trampas_manager;
}

Consumible_Manager * Datos_Partida_Online::get_Consumible_Manager(){
	return _consumibles_manager;
}

Interactuable_Manager* Datos_Partida_Online::get_interactuable_manager(){
	return _interactuable_manager;
}

Armas_Manager* Datos_Partida_Online::get_armas_manager(){
	return _armas_manager;
}

Zonas_Manager* Datos_Partida_Online::get_zonas_manager(){
	return _zonas_manager;
}

void Datos_Partida_Online::inserta_npc_nivel(){
	_npc_manager->inserta_npc_nivel();
}

Character** Datos_Partida_Online::get_characters(){
	return _characters;
}

Player* Datos_Partida_Online::crear_jugador(float x, float y){
	  float mult = 4.9212625; 
	//  Player* _jugador = new Player( 0, 12.5*mult, 0, 9.5*mult, nullptr, true);
	  Player_Online* _jugador = new Player_Online( 0, x, 0, y, nullptr, true);
	
	_jugadores_online.push_back(_jugador);
	_jugadores_online_incluyendo_player.push_back(_jugador);
	return _jugador;
}

std::vector<Player*> Datos_Partida_Online::dame_jugadores_online(){
 return _jugadores_online;
}

std::vector<Player*> Datos_Partida_Online::todos_jugadores_de_la_sesion(){
	return _jugadores_online_incluyendo_player;
}