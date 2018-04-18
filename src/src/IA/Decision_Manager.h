#ifndef SRC_DECISION_MANAGER_H_
#define SRC_DECISION_MANAGER_H_

#include <cstdint>

class Action_Manager;
class Arbol_Decision_Manager;
class Blackboard;
class NPC;

class Decision_Manager {
public:
	Decision_Manager(Action_Manager*);
	virtual ~Decision_Manager();

	void toma_decisiones();

private:
	//Manager de los arboles
	Arbol_Decision_Manager* _decision_tree_manager;

	//Blackboards para la toma de decision
	Blackboard** _blackboards;

	//Puntero al Action_Manager
	Action_Manager* _action_manager;

	//Puntero a los enemigos
	NPC** _npcs;

	//Control del LOD
	uint32_t _a;
	uint8_t* _iteraciones_lod;
	uint8_t* _iteraciones_actuales_lod;
};

#endif /* SRC_ACTION_MANAGER_H_ */
