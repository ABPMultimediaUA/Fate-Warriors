#include "Datos_Partida.h"

#include "Interactuable_Manager.h"
#include "Interfaz/Motor.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Personajes/NPC.h"
#include "Armas/Armas_Manager.h"
#include "Consumibles/Consumible_Manager.h"
#include "Trampas/Trampas_manager.h"
#include "Llave.h"
#include "Puerta.h"
#include "Zonas_Manager.h"
#include <iostream>


Datos_Partida::Datos_Partida(Input* _i_input) {
	float mult = 4.9212625;
	_jugador 			 	= 	new Player( 0, 12.5*mult, 0, 9.5*mult, _i_input);
	_npc_manager 		 	= 	new NPC_Manager();
	_consumibles_manager 	= 	new Consumible_Manager();
	_trampas_manager	 	= 	new Trampas_manager();
    _interactuable_manager 	= 	new Interactuable_Manager();
	_armas_manager 			=	new Armas_Manager();
	_zonas_manager 			=	new Zonas_Manager();

	

	NPC ** _npcs = _npc_manager->get_npcs();
	uint16_t _cont, _n_npcs;
	_n_npcs = _npc_manager->get_n_npc();

	_num_characters = _n_npcs + 1;
	_characters = new Character*[_num_characters];

	for(_cont = 0; _cont < _n_npcs; _cont++) {
		_characters[_cont] = _npcs[_cont];
	}
	_characters[_cont] = _jugador;

}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete _trampas_manager;
	delete _consumibles_manager;
	delete _armas_manager;

	delete _npc_manager;
  	delete _interactuable_manager;
	delete _zonas_manager;

	delete [] _characters;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida::get_npc_manager() {
	return _npc_manager;
}

Trampas_manager * Datos_Partida::get_trampas_manager(){
	return _trampas_manager;
}

Consumible_Manager * Datos_Partida::get_Consumible_Manager(){
	return _consumibles_manager;
}

Interactuable_Manager* Datos_Partida::get_interactuable_manager(){
	return _interactuable_manager;
}

Armas_Manager* Datos_Partida::get_armas_manager(){
	return _armas_manager;
}

Zonas_Manager* Datos_Partida::get_zonas_manager(){
	return _zonas_manager;
}

void Datos_Partida::inserta_npc_nivel(){
	_npc_manager->inserta_npc_nivel();
}