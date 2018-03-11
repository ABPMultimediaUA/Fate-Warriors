#ifndef SRC_ND_DISTANCIA_OBJETIVO_H_
#define SRC_ND_DISTANCIA_OBJETIVO_H_

#include "Nodo_Decision.h"

class ND_Distancia_Objetivo : public Nodo_Decision {
public:
	ND_Distancia_Objetivo(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_Distancia_Objetivo();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_DISTANCIA_OBJETIVO_H_ */
