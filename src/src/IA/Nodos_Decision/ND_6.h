#ifndef SRC_ND_6H_
#define SRC_ND_6H_

#include "Nodo_Decision.h"

class ND_6 : public Nodo_Decision {
public:
	ND_6(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_6();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_6H_ */