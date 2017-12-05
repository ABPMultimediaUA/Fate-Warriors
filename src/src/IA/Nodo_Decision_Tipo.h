#ifndef SRC_NODO_DECISION_TIPO_H_
#define SRC_NODO_DECISION_TIPO_H_

#include "Nodo_Decision.h"

class Nodo_Decision_Tipo : public Nodo_Decision {
public:
	Nodo_Decision_Tipo(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der);
	virtual ~Nodo_Decision_Tipo();

	enum Enum_Acciones nodo_decision_toma_decision(Blackboard* _blackboard);
};

#endif /* SRC_NODO_DECISION_TIPO_H_ */
