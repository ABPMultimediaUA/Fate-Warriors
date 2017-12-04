#ifndef SRC_NODO_DECISION_H_
#define SRC_NODO_DECISION_H_

#include "Enum_Acciones.h"
#include "Blackboard.h"
#include "Interfaz_Toma_Decision.h"

class Nodo_Decision {
public:
	Nodo_Decision();
	Nodo_Decision(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der);
	virtual ~Nodo_Decision();

	virtual enum Enum_Acciones nodo_decision_toma_decision(Blackboard* _blackboard) = 0;

protected:
	Interfaz_Toma_Decision *_interfaz;

	Nodo_Decision *_nodo_izq;
	Nodo_Decision *_nodo_der;
};

#endif /* SRC_NODO_DECISION_H_ */
