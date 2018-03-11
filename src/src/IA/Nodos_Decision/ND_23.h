#ifndef SRC_ND_23H_
#define SRC_ND_23H_

#include "Nodo_Decision.h"

class ND_23 : public Nodo_Decision {
public:
	ND_23(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_23();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_23H_ */