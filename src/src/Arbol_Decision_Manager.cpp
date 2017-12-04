#include "Arbol_Decision_Manager.h"

const unsigned short MAX_NODOS = 2;
const unsigned short MAX_ARBOLES = 1;

Arbol_Decision_Manager::Arbol_Decision_Manager() {
	_n_nodos = 0;
	_n_arboles = 0;

	//Creacion de las aciones
	_acciones = new Nodo_Decision_Final*[n_acciones];
	for(unsigned short _cont = 0; _cont < n_acciones; _cont++) {
		_acciones[_cont] = new Nodo_Decision_Final((Enum_Acciones)_cont);
	}


	//Creacion de los nodos
	_nodos_decision = new Nodo_Decision*[MAX_NODOS];

	//Lectura de fichero y eso [COMING SOON]
	_nodos_decision[0] = new Nodo_Decision_Distancia(*_acciones[Andar], *_acciones[Atacar]);
	_nodos_decision[1] = new Nodo_Decision_Tipo(*_nodos_decision[0], *_nodos_decision[0]);


	//Asignacion de los arboles
	_arboles_decision = new Nodo_Decision*[MAX_ARBOLES];

	_arboles_decision[0] = _nodos_decision[1];

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

Nodo_Decision* Arbol_Decision_Manager::crea_arbol_decision() {
	return _arboles_decision[0];
}
