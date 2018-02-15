#ifndef SRC_ND_HAY_ENEMIGOS_EN_MI_ZONA_H_
#define SRC_ND_HAY_ENEMIGOS_EN_MI_ZONA_H_

#include "Nodo_Decision.h"

class ND_Hay_Enemigos_En_Mi_Zona : public Nodo_Decision {
public:
	ND_Hay_Enemigos_En_Mi_Zona(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_Hay_Enemigos_En_Mi_Zona();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_HAY_ENEMIGOS_EN_MI_ZONA_H_ */