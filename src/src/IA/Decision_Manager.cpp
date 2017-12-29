#include "Decision_Manager.h"

#include "../Action_Manager.h"
#include "Arbol_Decision_Manager.h"
#include "Blackboard.h"
#include "Enum_Acciones.h"
#include "Interfaz_Datos.h"

#include "../Personajes/NPC.h"

#include<iostream>

const uint8_t _niveles_lod = 5; // Niveles 1, 2, 3, 4 ( y 0 para evitar sumar y restar)

Decision_Manager::Decision_Manager(Action_Manager* _i_action_manager) {
	_decision_tree_manager = new Arbol_Decision_Manager();

	_interfaz_decision = _i_action_manager->get_interfaz();

	_enemigos = _interfaz_decision->get_enemigos();

	//unsigned short _n_enemigos = _interfaz_decision->get_n_enemigos();
	unsigned short _n_enemigos = 0;
	_blackboards = new Blackboard*[_n_enemigos];

	for(uint8_t _cont = 0; _cont<_n_enemigos; _cont++) {
		_blackboards[_cont] = new Blackboard(*_interfaz_decision, _cont);
		_enemigos[_cont]->set_blackboard(_blackboards[_cont]);
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

	unsigned short _n_enemigos = _interfaz_decision->get_n_enemigos();
	for(uint8_t _cont=0; _cont<_n_enemigos; _cont++) {
		delete _blackboards[_cont];
	}
	delete [] _blackboards;


	delete _iteraciones_lod;
	delete _iteraciones_actuales_lod;
}


// Recorre todos los enemigos y les agrega una accion
void Decision_Manager::toma_decisiones(){
	//unsigned short _n_enemigos = _interfaz_decision->get_n_enemigos();
	unsigned short _n_enemigos = 0;	
	// Control de las iteraciones del level of detail
	for(uint8_t _cont = 1; _cont<_niveles_lod; _cont++) {
		_iteraciones_actuales_lod[_cont]++;
		if(_iteraciones_actuales_lod[_cont] > _iteraciones_lod[_cont]) {
			_iteraciones_actuales_lod[_cont] = 1;
		}
		//std::cout << "Iteraciones actuales del level of detail " << (int)_cont << " = " << (int)_iteraciones_actuales_lod[_cont] << "\n";
	}
	//std::cout << "\n";

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {

		// Se actualizan los datos del blackboard
		_blackboards[_cont]->actualiza_datos();

		// Recoge el Level of Detail actual
		int8_t _lod_npc = _blackboards[_cont]->get_level_of_detail();
		//std::cout << "LoD del NPC " << _cont << " es " << (int)_lod_npc << "\n";

		if(_iteraciones_actuales_lod[_lod_npc] == _iteraciones_lod[_lod_npc]) {
			//Se toma la accion
			_blackboards[_cont]->set_accion(_decision_tree_manager->_tomar_decision(_blackboards[_cont]));
		}
		else {
			//Ninguna accion
			_blackboards[_cont]->set_accion(Nada);
		}

		//Se realiza la accion
		_action_manager->realiza_accion(_enemigos[_cont]);
	}
}