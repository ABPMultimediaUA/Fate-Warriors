#ifndef SRC_ND_SITUADO_EN_ZONA_ALIADA_H_
#define SRC_ND_SITUADO_EN_ZONA_ALIADA_H_

#include "Nodo_Decision.h"

class ND_Situado_En_Zona_Aliada : public Nodo_Decision {
public:
	ND_Situado_En_Zona_Aliada(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_Situado_En_Zona_Aliada();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_SITUADO_EN_ZONA_ALIADA_H_ */
