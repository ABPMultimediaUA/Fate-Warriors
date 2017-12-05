#include "Action_Manager.h"

#include "Blackboard.h"
#include "Enum_Acciones.h"
#include "Experto_Manager.h"
#include "Interfaz_Toma_Decision.h"
#include "Path_Manager.h"

#include "../Personajes/NPC.h"

#include<iostream>

Action_Manager::Action_Manager() {

	_expert_manager = new Experto_Manager();

	_interfaz_decision = new Interfaz_Toma_Decision();

	_enemigos = _interfaz_decision->interfaz_decision_get_enemigos();

	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();
	_blackboards = new Blackboard*[_n_enemigos];

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_blackboards[_cont] = new Blackboard(*_interfaz_decision, _cont);
	}


	_path_manager = new Path_Manager(*_interfaz_decision);
}

Action_Manager::~Action_Manager() {
	delete _path_manager;


	delete _interfaz_decision;

	delete _expert_manager;


	_enemigos = nullptr;
}



void Action_Manager::toma_decisiones(){
	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();

	enum Enum_Acciones _accion = Nada;

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_accion = _expert_manager->_tomar_decisiones(_blackboards[_cont]);
		_blackboards[_cont]->set_accion(_accion);
	}
}

void Action_Manager::realiza_acciones(){
	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();
	enum Enum_Acciones _accion;

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {

		_accion = _blackboards[_cont]->get_accion();


		switch(_accion) {
		case Andar:
			unsigned short _direccion;

			_direccion = _path_manager->get_direccion_movimiento(_cont);

			_enemigos[_cont]->move(_direccion);

			break;

		case Atacar:
			std::cout << "El enemigo " << _cont << " ataca" << std::endl;
			//ATACAR
			break;

		case Decidir:
			std::cout << "El enemigo " << _cont << " decide" << std::endl;
			break;
		case Nada:
			std::cout << "El enemigo " << _cont << " hace nada" << std::endl;
			break;
		}
	}
}
