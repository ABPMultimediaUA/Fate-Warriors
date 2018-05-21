#include "Datos_Partida.h"

#include "Interactuables/Interactuable_Manager.h"
#include "Interfaz/Motor.h"
#include "Personajes/Player.h"
#include "Personajes/NPC_Manager.h"
#include "Personajes/NPC.h"
#include "Consumibles/Consumible_Manager.h"
#include "Zonas/Zonas_Manager.h"
#include "Zonas/Respawn.h"
#include "Utilidades/Vector.h"

Datos_Partida::Datos_Partida(Input* _i_input) { 
	float mult = 4.9212625; 
  	_zonas_manager       	=  new Zonas_Manager();
	Vector2 pos 			=  _zonas_manager->get_posicion_zona_inicial();
  	_jugador 				= new Player( 0, pos._x, 1, pos._y, _i_input); 
    _consumibles_manager 	= new Consumible_Manager(); 
	//  _respawn_Points      =  new Respawn_Points(); 
	_interactuable_manager  =   new Interactuable_Manager(_zonas_manager->get_zonas()); 
  	_npc_manager        	=   new NPC_Manager(); 
 
   
 
	NPC ** _npcs = _npc_manager->get_npcs(); 
	uint16_t _cont, _n_npcs; 
	_n_npcs = _npc_manager->get_n_npc(); 

	for(_cont = 0; _cont < _n_npcs; _cont++) { 
		_npcs[_cont]->aparecer_muerto();
	} 
	_num_characters = _n_npcs + 1;
	_characters = new Character*[_num_characters];

	for(_cont = 0; _cont < _n_npcs; _cont++) {
		_characters[_cont] = _npcs[_cont];
	}
	_characters[_cont] = _jugador;

}

Datos_Partida::~Datos_Partida() {
	delete _jugador;
	delete _consumibles_manager;

	delete _npc_manager;
  	delete _interactuable_manager;
//	delete _respawn_Points;
	delete _zonas_manager;

	delete [] _characters;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC_Manager* Datos_Partida::get_npc_manager() {
	return _npc_manager;
}

Consumible_Manager * Datos_Partida::get_Consumible_Manager(){
	return _consumibles_manager;
}

Interactuable_Manager* Datos_Partida::get_interactuable_manager(){
	return _interactuable_manager;
}

Zonas_Manager* Datos_Partida::get_zonas_manager(){
	return _zonas_manager;
}

void Datos_Partida::inserta_npc_nivel(){
	_npc_manager->inserta_npc_nivel();
}

Character** Datos_Partida::get_characters(){
	return _characters;
}

void Datos_Partida::posicionar_characters_inicialmente(){
 
	uint16_t _cont;

	Respawn * respawn = Respawn::posiciones_instancia();
	for(_cont = 0; _cont < _num_characters; _cont++) { 
	/*	if(_characters[_cont]!=_jugador){
			Vector2 vector = respawn->generar_posicion_del_bando(_characters[_cont]->get_equipo()); BORRAME
			_characters[_cont]->setPositionXZ(vector._x, vector._y);
		}
		*/
	} 
}