#ifndef SRC_ND_17H_
#define SRC_ND_17H_

#include "Nodo_Decision.h"

class ND_17 : public Nodo_Decision {
public:
	ND_17(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_17();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_17H_ */