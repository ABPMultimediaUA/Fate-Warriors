#ifndef SRC_EXPERTO_MANAGER_H_
#define SRC_EXPERTO_MANAGER_H_

#include "Experto_Combate.h"
#include "Blackboard.h"
#include "Arbol_Decision_Manager.h"

class Experto_Manager {
public:
	Experto_Manager();
	virtual ~Experto_Manager();

	enum Enum_Acciones _tomar_decisiones(Blackboard* _blackboard);

private:
	//Manager de arboles de decision
	Arbol_Decision_Manager* _decision_tree_manager;

	Experto** _expertos;
};

#endif /* SRC_EXPERTO_MANAGER_H_ */
