#ifndef SRC_NODO_DECISION_DISTANCIA_H_
#define SRC_NODO_DECISION_DISTANCIA_H_

#include "Enum_Acciones.h"
#include "Nodo_Decision.h"

class Nodo_Decision_Distancia : public Nodo_Decision{
public:
	Nodo_Decision_Distancia(Interfaz_Toma_Decision& _i_interfaz, Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der);
	virtual ~Nodo_Decision_Distancia();

	enum Enum_Acciones nodo_decision_toma_decision(unsigned short _i_n_enemigo);
};

#endif /* SRC_NODO_DECISION_DISTANCIA_H_ */
