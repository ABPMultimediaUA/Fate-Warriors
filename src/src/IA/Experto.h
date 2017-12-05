#ifndef SRC_EXPERTO_H_
#define SRC_EXPERTO_H_

#include "Enum_Acciones.h"

class Blackboard;
class Nodo_Decision;

class Experto {
public:
	Experto(Nodo_Decision *_i_arbol_decision);
	virtual ~Experto();

	virtual bool leer_blackboard(Blackboard* _blackboard) = 0;
	virtual enum Enum_Acciones toma_decision(Blackboard* _blackboard) = 0;

protected:
	Nodo_Decision *_arbol_decision;

};

#endif /* SRC_EXPERTO_H_ */
