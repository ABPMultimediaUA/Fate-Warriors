#include "Decision_Manager.h"

#include "Action_Manager.h"
#include "Arbol_Decision_Manager.h"
#include "Blackboard.h"
#include "Enum_Acciones.h"
#include "Interfaz_Toma_Decision.h"

#include "../Personajes/NPC.h"

#include<iostream>

Decision_Manager::Decision_Manager(Action_Manager* _i_action_manager) {
	_decision_tree_manager = new Arbol_Decision_Manager();

	_interfaz_decision = _i_action_manager->get_interfaz();

	_enemigos = _interfaz_decision->interfaz_decision_get_enemigos();

	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();

	_blackboards = new Blackboard*[_n_enemigos];

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_blackboards[_cont] = new Blackboard(*_interfaz_decision, _cont);
		_enemigos[_cont]->set_blackboard(_blackboards[_cont]);
	}

	_action_manager = _i_action_manager;
}

Decision_Manager::~Decision_Manager() {
	delete _decision_tree_manager;

	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();
	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		delete _blackboards[_cont];
	}
	delete [] _blackboards;

	_interfaz_decision = nullptr;
	_enemigos = nullptr;
	_action_manager = nullptr;
}


// Recorre todos los enemigos y les agrega una accion
void Decision_Manager::toma_decisiones(){
	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {

		//Se actualizan los datos del blackboard
		_blackboards[_cont]->actualiza_datos();

		//Se toma la accion
		_blackboards[_cont]->set_accion(_decision_tree_manager->_tomar_decision(_blackboards[_cont]));

		//Se realiza la accion
		_action_manager->realiza_accion(_enemigos[_cont]);
	}
}