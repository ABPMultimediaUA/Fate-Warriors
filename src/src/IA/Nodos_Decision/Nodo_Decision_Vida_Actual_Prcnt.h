#ifndef SRC_NODO_DECISION_VIDA_ACTUAL_PRCNT_H_
#define SRC_NODO_DECISION_VIDA_ACTUAL_PRCNT_H_

#include "Nodo_Decision.h"

class Nodo_Decision_Vida_Actual_Prcnt : public Nodo_Decision {
public:
	Nodo_Decision_Vida_Actual_Prcnt(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~Nodo_Decision_Vida_Actual_Prcnt();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_NODO_DECISION_VIDA_ACTUAL_PRCNT_H_ */
