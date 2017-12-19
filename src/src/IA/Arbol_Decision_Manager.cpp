#include "Arbol_Decision_Manager.h"

#include "Blackboard.h"
#include "Nodos_Decision.h"

const unsigned short MAX_NODOS = 1;
const unsigned short MAX_ARBOLES = 1;

Arbol_Decision_Manager::Arbol_Decision_Manager() {
	_n_nodos = 1;
	_n_arboles = 0;

	//Creacion de las aciones
	_acciones = new Nodo_Decision_Final*[n_acciones];
	for(unsigned short _cont = 0; _cont < n_acciones; _cont++) {
		_acciones[_cont] = new Nodo_Decision_Final((Enum_Acciones)_cont);
	}


	//Creacion de los nodos
	_nodos_decision = new Nodo_Decision*[MAX_NODOS];

	//Lectura de fichero y eso [COMING SOON]
	_nodos_decision[0] = new Nodo_Decision_Distancia(*_acciones[Andar], *_acciones[Atacar], 2);


	//Asignacion de los arboles
	_arboles_decision = new Nodo_Decision*[MAX_ARBOLES];

	_arboles_decision[0] = _nodos_decision[0];

}

Arbol_Decision_Manager::~Arbol_Decision_Manager() {
	//Desasignar arboles
	for(unsigned short _cont = 0; _cont < _n_arboles; _cont++) {
		_arboles_decision[_cont] = nullptr;
	}
	delete [] _arboles_decision;

	//Borrar nodos
	for(unsigned short _cont = 0; _cont < _n_nodos; _cont++) {
		delete _nodos_decision[_cont];
	}
	delete [] _nodos_decision;

	//Borrar acciones
	for(unsigned short _cont = 0; _cont < n_acciones; _cont++) {
		delete _acciones[_cont];
	}
	delete [] _acciones;
}

enum Enum_Acciones Arbol_Decision_Manager::_tomar_decision(Blackboard* _blackboard) {
	return _arboles_decision[_blackboard->get_tipo_enemigo()]->toma_decision(_blackboard);
}
