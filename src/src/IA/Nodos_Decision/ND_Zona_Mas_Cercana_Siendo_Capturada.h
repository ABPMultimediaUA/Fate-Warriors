#ifndef SRC_ND_ZONA_MAS_CERCANA_SIENDO_CAPTURADA_H_
#define SRC_ND_ZONA_MAS_CERCANA_SIENDO_CAPTURADA_H_

#include "Nodo_Decision.h"

class ND_Zona_Mas_Cercana_Siendo_Capturada : public Nodo_Decision {
public:
	ND_Zona_Mas_Cercana_Siendo_Capturada(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor);
	virtual ~ND_Zona_Mas_Cercana_Siendo_Capturada();

	enum Enum_Acciones toma_decision(Blackboard* _blackboard);

private:
	float _valor;
};

#endif /* SRC_ND_ZONA_MAS_CERCANA_SIENDO_CAPTURADA_H_ */
