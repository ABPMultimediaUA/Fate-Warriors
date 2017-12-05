#ifndef SRC_EXPERTO_COMBATE_H_
#define SRC_EXPERTO_COMBATE_H_

#include "Experto.h"

class Experto_Combate : public Experto {
public:
	Experto_Combate(Nodo_Decision *_i_arbol_decision);
	virtual ~Experto_Combate();

	bool leer_blackboard(Blackboard* _blackboard);
	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

};

#endif /* SRC_EXPERTO_COMBATE_H_ */
