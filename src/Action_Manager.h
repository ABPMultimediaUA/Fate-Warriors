#ifndef SRC_ACTION_MANAGER_H_
#define SRC_ACTION_MANAGER_H_

#include "Interfaz_Toma_Decision.h"
#include "Experto_Manager.h"
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

	//Manager de expertos
	Experto_Manager* _expert_manager;

	// Nodos y arboles de decision
	/*Nodo_Decision_Final *_accion_andar;
	Nodo_Decision_Final *_accion_atacar;
	Nodo_Decision_Distancia *_arbol_decision;*/

	//NPCs
	NPC** _enemigos;

	//Blackboards
	Blackboard** _blackboards;

	//Path Manager
	Path_Manager *_path_manager;

};

#endif /* SRC_ACTION_MANAGER_H_ */
