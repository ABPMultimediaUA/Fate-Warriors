#include "Datos_Partida_Offline.h"

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


Datos_Partida_Offline::Datos_Partida_Offline(Input* _i_input) { 
    float mult = 4.9212625; 
  _jugador          =   new Player( 0, 12.5*mult, 0, 9.5*mult, _i_input, false); 
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
	_num_characters = _n_npcs; //+ 1;
	_characters = new Character*[_num_characters];

	for(_cont = 0; _cont < _n_npcs; _cont++) {
		_characters[_cont] = _npcs[_cont];
	}
	//_characters[_cont] = _jugador;
}

Datos_Partida_Offline::~Datos_Partida_Offline() {
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

Player* Datos_Partida_Offline::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida_Offline::get_npc_manager() {
	return _npc_manager;
}

Trampas_manager * Datos_Partida_Offline::get_trampas_manager(){
	return _trampas_manager;
}

Consumible_Manager * Datos_Partida_Offline::get_Consumible_Manager(){
	return _consumibles_manager;
}

Interactuable_Manager* Datos_Partida_Offline::get_interactuable_manager(){
	return _interactuable_manager;
}

Armas_Manager* Datos_Partida_Offline::get_armas_manager(){
	return _armas_manager;
}

Zonas_Manager* Datos_Partida_Offline::get_zonas_manager(){
	return _zonas_manager;
}

void Datos_Partida_Offline::inserta_npc_nivel(){
	_npc_manager->inserta_npc_nivel();
}

Character** Datos_Partida_Offline::get_characters(){
	return _characters;
}

Player* Datos_Partida_Offline::crear_jugador(float x, float y){
	  float mult = 4.9212625; 
	//  Player* _jugador = new Player( 0, 12.5*mult, 0, 9.5*mult, nullptr, true);
	  Player_Online* _jugador = new Player_Online( 0, x, 0, y, nullptr, true);
	
	_jugadores_online.push_back(_jugador);
	_jugadores_online_incluyendo_player.push_back(_jugador);
	return _jugador;
}

std::vector<Player*> Datos_Partida_Offline::dame_jugadores_online(){
 return _jugadores_online;
}

std::vector<Player*> Datos_Partida_Offline::todos_jugadores_de_la_sesion(){
	return _jugadores_online_incluyendo_player;
}