#ifndef SRC_ND_16H_
#define SRC_ND_16H_

#include "Nodo_Decision.h"

class ND_16 : public Nodo_Decision {
public:
	ND_16(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_16();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_16H_ */