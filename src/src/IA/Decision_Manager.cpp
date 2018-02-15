#include "Decision_Manager.h"

#include "../Action_Manager.h"
#include "Arbol_Decision_Manager.h"
#include "Blackboard.h"
#include "Enum_Acciones.h"
#include "../Game.h"
#include "../Datos_Partida.h"

#include "../Personajes/NPC.h"
#include "../Personajes/NPC_Manager.h"

#include<iostream>

const uint8_t _niveles_lod = 5; // Niveles 1, 2, 3, 4 ( y 0 para evitar sumar y restar)

Decision_Manager::Decision_Manager(Action_Manager* _i_action_manager) {
	_decision_tree_manager = new Arbol_Decision_Manager();

	_npcs =  Game::game_instancia()->game_get_datos()->get_npc_manager()->get_npcs();

	uint16_t _n_npcs = Game::game_instancia()->game_get_datos()->get_npc_manager()->get_n_npc();
	_blackboards = new Blackboard*[_n_npcs];

	for(uint16_t _cont = 0; _cont<_n_npcs; _cont++) {
		_blackboards[_cont] = _npcs[_cont]->get_blackboard();
	}

	_action_manager = _i_action_manager;

	// Control del LoD
	_iteraciones_lod = new uint8_t[_niveles_lod];
	_iteraciones_lod[0] = 0;
	_iteraciones_lod[1] = 1;
	_iteraciones_lod[2] = 3;
	_iteraciones_lod[3] = 6;
	_iteraciones_lod[4] = 12;

	_iteraciones_actuales_lod = new uint8_t[_niveles_lod];
	_iteraciones_actuales_lod[0] = 0;
	_iteraciones_actuales_lod[1] = 1;
	_iteraciones_actuales_lod[2] = 3;
	_iteraciones_actuales_lod[3] = 5;
	_iteraciones_actuales_lod[4] = 10;
}

Decision_Manager::~Decision_Manager() {
	delete _decision_tree_manager;

	delete [] _blackboards;

	delete _iteraciones_lod;
	delete _iteraciones_actuales_lod;
}

// Recorre todos los enemigos y les agrega una accion
void Decision_Manager::toma_decisiones(){

	uint16_t _n_npcs = Game::game_instancia()->game_get_datos()->get_npc_manager()->get_n_npc();
	
	// Control de las iteraciones del level of detail
	for(uint8_t _cont = 1; _cont<_niveles_lod; _cont++) {
		_iteraciones_actuales_lod[_cont]++;
		if(_iteraciones_actuales_lod[_cont] > _iteraciones_lod[_cont]) {
			_iteraciones_actuales_lod[_cont] = 1;
		}
		//std::cout << "Iteraciones actuales del level of detail " << (int)_cont << " = " << (int)_iteraciones_actuales_lod[_cont] << "\n";
	}
	//std::cout << "\n";

	for(uint16_t _cont=0; _cont<_n_npcs; _cont++) {

		// Se actualizan los datos del blackboard
		_blackboards[_cont]->actualiza_datos();
		_npcs[_cont]->gestion_acciones();

		//std::cout << "accion" <<_npcs[_cont]->get_accion() << "\n";
		// Recoge el Level of Detail actual
		int8_t _lod_npc = _blackboards[_cont]->get_level_of_detail();
		//std::cout << "LoD del NPC " << _cont << " es " << (int)_lod_npc << "\n";

		// Estas acciones no es la misma variable que accion de Character
		//if(_iteraciones_actuales_lod[_lod_npc] == _iteraciones_lod[_lod_npc]) {
			//Se toma la accion
			_blackboards[_cont]->set_accion(_decision_tree_manager->_tomar_decision(_blackboards[_cont]));
		//}
		//else {
			//Ninguna accion
		//	_blackboards[_cont]->set_accion(Nada);
		//}

		//Se realiza la accion
		_action_manager->realiza_accion(_npcs[_cont]);
	}
}