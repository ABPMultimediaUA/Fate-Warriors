#ifndef SRC_ND_SET_OBJETIVO_PERSONAJE_ENEMIGO_CERCA_H_
#define SRC_ND_SET_OBJETIVO_PERSONAJE_ENEMIGO_CERCA_H_

#include "Nodo_Decision.h"

class ND_Set_Objetivo_Personaje_Enemigo_Cerca : public Nodo_Decision {
public:
	ND_Set_Objetivo_Personaje_Enemigo_Cerca(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_Set_Objetivo_Personaje_Enemigo_Cerca();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_SET_OBJETIVO_PERSONAJE_ENEMIGO_CERCA_H_ */
