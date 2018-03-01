#ifndef SRC_ND_9H_
#define SRC_ND_9H_

#include "Nodo_Decision.h"

class ND_9 : public Nodo_Decision {
public:
	ND_9(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_9();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_9H_ */