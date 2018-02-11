#ifndef SRC_BLACKBOARD_H_
#define SRC_BLACKBOARD_H_

#include <cstdlib>
#include <iostream>

#include "Enums_Decisiones.h"
#include "Enum_Acciones.h"

#include "../Nivel/Enum_zonas.h"

#include "../Personajes/Enum_Tipo_Ataque.h"
#include "../Personajes/Enum_Tipo_Enemigo.h"
#include "../Nivel/Nodo_blackboard.h"

class Character;

class Blackboard {
public:
	Blackboard(NPC * npc_padre);
	~Blackboard();

	//FUNCIONES DE REFRESCO Y OBTENCION DE DATOS
	void actualiza_datos();									//Actualiza los datos del blackboard para cada iteracion

	//FUNCIONES DE TOMA DE DECISION
	void set_decision(enum Enum_Decisiones _i_decision);	//Set la decision actual

	//setters
	inline void set_nodo_blackboard(Nodo_blackboard* _i_blackboard){
		_zona = _i_blackboard;
	}

	//getters
	float get_distancia_objetivo();
	int8_t get_level_of_detail();
	float get_porcentaje_vida();
	Enum_Decisiones get_decision();
	inline NPC * get_npc_padre(){
		return _npc_padre;
	}

private:

	// Datos de identidad del NPC
	NPC * _npc_padre;
	
	// Datos de accion y decision propio de cada enemigo
	enum Enum_Decisiones _decision;			// Decision actual 			(Controlado por Pablo)

	Objeto* _objetivo;				// Objetivo actual

	// Datos de estado
	float _porcentaje_vida;					// Porcentaje vida actual (Se calcula en cada iteracion) DONE

	//Con informacion de la zona
	Nodo_blackboard* _zona;					// Blackbaord de la zona
};

#endif /* SRC_BLACKBOARD_H_ */
