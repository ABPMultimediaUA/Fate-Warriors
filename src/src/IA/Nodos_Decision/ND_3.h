#ifndef SRC_ND_3H_
#define SRC_ND_3H_

#include "Nodo_Decision.h"

class ND_3 : public Nodo_Decision {
public:
	ND_3(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_3();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_3H_ */