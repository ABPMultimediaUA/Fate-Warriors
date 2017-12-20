#ifndef SRC_NODO_DECISION_RANGO_ATAQUE_NORMAL_H_
#define SRC_NODO_DECISION_RANGO_ATAQUE_NORMAL_H_

#include "Nodo_Decision.h"

class Nodo_Decision_Rango_Ataque_Normal : public Nodo_Decision {
public:
	Nodo_Decision_Rango_Ataque_Normal(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, unsigned short _i_valor);
	virtual ~Nodo_Decision_Rango_Ataque_Normal();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	unsigned short _valor;
};

#endif /* SRC_NODO_DECISION_RANGO_ATAQUE_NORMAL_H_ */
