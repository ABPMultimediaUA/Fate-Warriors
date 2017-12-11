#ifndef SRC_DECISION_MANAGER_H_
#define SRC_DECISION_MANAGER_H_

class Action_Manager;
class Arbol_Decision_Manager;
class Blackboard;
class Interfaz_Toma_Decision;
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
	NPC** _enemigos;

	//Puntero a la interfaz a datos para la toma de decision
	Interfaz_Toma_Decision *_interfaz_decision;
};

#endif /* SRC_ACTION_MANAGER_H_ */
