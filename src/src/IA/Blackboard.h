#ifndef SRC_BLACKBOARD_H_
#define SRC_BLACKBOARD_H_

#include "Enum_Decisiones.h"
#include "Enum_Acciones.h"

#include "../Personajes/Enum_Tipo_Enemigo.h"

class Interfaz_Datos;

class Blackboard {
public:
	Blackboard(Interfaz_Datos& _i_interfaz, unsigned short _i_n_enemigo);
	virtual ~Blackboard();

	void actualiza_datos();

	unsigned short get_n_enemigo();

	enum Enum_Tipo_Enemigo get_tipo_enemigo();
	enum Enum_Decisiones get_decision();
	enum Enum_Acciones get_accion();
	float get_distancia_jugador();

	void set_decision(enum Enum_Decisiones _i_decision);
	void set_accion(enum Enum_Acciones _i_accion);

private:
	Interfaz_Datos *_interfaz;

	// Datos de identidad del enemigo NO SE MODIFICAN
	unsigned short _n_enemigo;				// Numero del enemigo
	enum Enum_Tipo_Enemigo _tipo_enemigo;	// Tipo de enemigo que es

	// Datos de estado
	bool _alertado;							// Esta alertado o no
	bool _hay_orden;						// Hay orden o no

	// Datos de distancia
	float _disancia_jugador;				// Distancia a la que se encuentra del jugador
	float _distancia_objeto;				//Distancia al objeto mas cercano

	// Datos de accion y decision
	enum Enum_Decisiones _decision;			// Decision actual
	enum Enum_Acciones _accion;				// Accion actual
};

#endif /* SRC_BLACKBOARD_H_ */
