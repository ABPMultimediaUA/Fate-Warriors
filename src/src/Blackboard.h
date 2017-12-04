#ifndef SRC_BLACKBOARD_H_
#define SRC_BLACKBOARD_H_

#include "Interfaz_Toma_Decision.h"
#include "Enum_Decisiones.h"
#include "Enum_Acciones.h"

class Blackboard {
public:
	Blackboard(Interfaz_Toma_Decision& _i_interfaz, unsigned short _i_n_enemigo);
	virtual ~Blackboard();

	void actualiza_datos();

	enum Enum_Decisiones get_decision();
	enum Enum_Acciones get_accion();
	float get_distancia_jugador();

	void set_decision(enum Enum_Decisiones _i_decision);
	void set_accion(enum Enum_Acciones _i_accion);

private:
	Interfaz_Toma_Decision *_interfaz;

	unsigned short _n_enemigo;
	float _disancia_jugador;
	enum Enum_Decisiones _decision;
	enum Enum_Acciones _accion;
};

#endif /* SRC_BLACKBOARD_H_ */
