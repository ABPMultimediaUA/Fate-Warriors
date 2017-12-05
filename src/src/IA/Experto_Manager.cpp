#include "Experto_Manager.h"

#include "Arbol_Decision_Manager.h"
#include "Blackboard.h"
#include "Experto_Combate.h"

#include <iostream>

const unsigned short N_EXPERTOS = 1;

Experto_Manager::Experto_Manager() {
	Nodo_Decision* _nodo = nullptr;

	_decision_tree_manager = new Arbol_Decision_Manager();

	_expertos = new Experto*[N_EXPERTOS];

	_nodo = _decision_tree_manager->crea_arbol_decision();
	_expertos[0] = new Experto_Combate(_nodo);
	//Resto de expertos

	_nodo = nullptr;
}

Experto_Manager::~Experto_Manager() {
	for(unsigned short _cont=0; _cont<N_EXPERTOS;_cont++) {
		delete _expertos[_cont];
	}

	delete [] _expertos;
}


enum Enum_Acciones Experto_Manager::_tomar_decisiones(Blackboard* _blackboard) {
	//Actualizar blackboard
	_blackboard->actualiza_datos();

	//Leer_blackboard de expertos y elegir la accion del primero (mas prioridad)
	for(unsigned short _cont=0; _cont<N_EXPERTOS; _cont++) {
		if(_expertos[_cont]->leer_blackboard(_blackboard) == true) {
			return _expertos[_cont]->toma_decision(_blackboard);
		}
	}

	return Nada;
}
