#ifndef SRC_NODO_DECISION_DISTANCIA_H_
#define SRC_NODO_DECISION_DISTANCIA_H_

#include "Nodo_Decision.h"

class Nodo_Decision_Distancia : public Nodo_Decision {
public:
	Nodo_Decision_Distancia(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~Nodo_Decision_Distancia();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_NODO_DECISION_DISTANCIA_H_ */
