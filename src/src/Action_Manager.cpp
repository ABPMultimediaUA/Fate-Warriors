#include "Action_Manager.h"
#include "Enum_Acciones.h"

#include<iostream>

Action_Manager::Action_Manager() {
	_interfaz_decision = new Interfaz_Toma_Decision();

	_nodo_vacio = nullptr;
	_accion_andar = new Nodo_Decision_Final(Andar, *_interfaz_decision, *_nodo_vacio, *_nodo_vacio);
	_accion_atacar = new Nodo_Decision_Final(Atacar, *_interfaz_decision, *_nodo_vacio, *_nodo_vacio);
	_arbol_decision = new Nodo_Decision_Distancia(*_interfaz_decision, *_accion_andar, *_accion_atacar);

	_enemigos = _interfaz_decision->interfaz_decision_get_enemigos();

	_path_manager = new Path_Manager(*_interfaz_decision);
}

Action_Manager::~Action_Manager() {
	delete _path_manager;

	delete _arbol_decision;
	delete _accion_atacar;
	delete _accion_andar;
	delete _interfaz_decision;

	_enemigos = nullptr;
}



void Action_Manager::toma_decisiones(){
	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();
	enum Enum_Acciones _accion;

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_accion = _arbol_decision->nodo_decision_toma_decision(_cont);
		_enemigos[_cont]->set_action(_accion);
	}

}

void Action_Manager::realiza_acciones(){
	unsigned short _n_enemigos = _interfaz_decision->interfaz_decision_get_n_enemigos();
	enum Enum_Acciones _accion;

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_accion = _enemigos[_cont]->get_action();

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
