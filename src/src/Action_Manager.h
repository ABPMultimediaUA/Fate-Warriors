#ifndef SRC_ACTION_MANAGER_H_
#define SRC_ACTION_MANAGER_H_

#include "Interfaz_Toma_Decision.h"
#include "Nodo_Decision.h"
#include "Nodo_Decision_Distancia.h"
#include "Nodo_Decision_Final.h"
#include "Path_Manager.h"

class Action_Manager {
public:
	Action_Manager();
	virtual ~Action_Manager();

	void toma_decisiones();
	void realiza_acciones();

private:
	//Interfaz a datos para la toma de decision
	Interfaz_Toma_Decision *_interfaz_decision;

	// Nodos y arboles de decision
	Nodo_Decision *_nodo_vacio;
	Nodo_Decision_Final *_accion_andar;
	Nodo_Decision_Final *_accion_atacar;
	Nodo_Decision_Distancia *_arbol_decision;

	//NPCs
	NPC** _enemigos;

	//Path Manager
	Path_Manager *_path_manager;

};

#endif /* SRC_ACTION_MANAGER_H_ */
