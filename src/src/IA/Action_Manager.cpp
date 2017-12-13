#include "Action_Manager.h"

#include "Blackboard.h"
#include "Enum_Acciones.h"
#include "Interfaz_Toma_Decision.h"
#include "Path_Manager.h"

#include "../Personajes/NPC.h"

#include<iostream>

Action_Manager::Action_Manager() {
	_interfaz_decision = new Interfaz_Toma_Decision();

	_path_manager = new Path_Manager(*_interfaz_decision);
}

Action_Manager::~Action_Manager() {
	delete _path_manager;

	delete _interfaz_decision;
}

void Action_Manager::realiza_accion(NPC* _i_npc){
	
	Blackboard* _blackboard = _i_npc->get_blackboard();

	enum Enum_Acciones _accion = _blackboard->get_accion();
	unsigned short _n_enemigo = _blackboard->get_n_enemigo();


	switch(_accion) {
		case Andar:
			unsigned short _direccion;

			_direccion = _path_manager->get_direccion_movimiento(_n_enemigo);

			_i_npc->move(_direccion);

			break;

		case Atacar:
		//	std::cout << "El enemigo " << _n_enemigo << " ataca" << std::endl;
			//ATACAR
			break;

		case Decidir:
		//	std::cout << "El enemigo " << _n_enemigo << " decide" << std::endl;
			break;
		case Nada:
		//	std::cout << "El enemigo " << _n_enemigo << " hace nada" << std::endl;
			break;
	}
}


void Action_Manager::mover(Character* _i_personaje, unsigned short _i_direccion) {
	//Comprobar que se puede mover
	//_i_personaje->move(_direccion);
}



Interfaz_Toma_Decision* Action_Manager::get_interfaz() {
	return _interfaz_decision;
}