#ifndef SRC_NODO_DECISION_H_
#define SRC_NODO_DECISION_H_

#include "Enum_Acciones.h"

class Blackboard;

class Nodo_Decision {
public:
	Nodo_Decision();
	Nodo_Decision(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der);
	virtual ~Nodo_Decision();

	virtual enum Enum_Acciones toma_decision(Blackboard* _blackboard) = 0;

protected:
	Nodo_Decision *_nodo_izq;
	Nodo_Decision *_nodo_der;
};

#endif /* SRC_NODO_DECISION_H_ */
