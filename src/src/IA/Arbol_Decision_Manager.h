#ifndef SRC_ARBOL_DECISION_MANAGER_H_
#define SRC_ARBOL_DECISION_MANAGER_H_

class Nodo_Decision;
class Nodo_Decision_Final;

class Arbol_Decision_Manager {
public:
	Arbol_Decision_Manager();
	virtual ~Arbol_Decision_Manager();

	Nodo_Decision* crea_arbol_decision();

private:
	unsigned short _n_nodos;
	unsigned short _n_arboles;

	//Nodos de decision
	Nodo_Decision** _nodos_decision;

	//Asignaciones de nodos que forman arboles
	Nodo_Decision** _arboles_decision;

	//Acciones
	Nodo_Decision_Final** _acciones;
};

#endif /* SRC_ARBOL_DECISION_MANAGER_H_ */
