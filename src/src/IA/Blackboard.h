#ifndef SRC_BLACKBOARD_H_
#define SRC_BLACKBOARD_H_

#include <cstdlib>

#include "Enums_Decisiones.h"
#include "Enum_Acciones.h"

#include "../Personajes/Enum_Tipo_Ataque.h"
#include "../Personajes/Enum_Tipo_Enemigo.h"
#include "../Nivel/Nodo_blackboard.h"

#include "../Zonas/Zona.h"

class Character;

class Blackboard {
public:
	Blackboard(NPC * npc_padre);
	~Blackboard();

	//FUNCIONES DE REFRESCO Y OBTENCION DE DATOS
	void actualiza_datos();									//Actualiza los datos del blackboard para cada iteracion
	void actualizar_characteres();
	void actualizar_pseudo_azar();
	void actualizar_zonas();

	void equipar_arma_larga_distancia();
	void equipar_arma_corta_distancia();

	//FUNCIONES DE TOMA DE DECISION
	void set_decision(enum Enum_Decisiones _i_decision);	//Set la decision actual

	//setters
	inline void set_nodo_blackboard(Nodo_blackboard* _i_blackboard){
		_zona = _i_blackboard;
	}
	inline void set_accion(Enum_Acciones i_accion){
		_accion = i_accion;
	}

	//getters
	float get_distancia_objetivo();
	int8_t get_level_of_detail();
	float get_porcentaje_vida();
	Enum_Decisiones get_decision();
	inline NPC * get_npc_padre(){
		return _npc_padre;
	}
	inline Enum_Acciones get_accion(){
		return _accion;
	}

//private:

	Enum_Acciones _accion; // Es la accion que se tiene en mente, distinta de la accion actual de Character!!

	// Datos de identidad del NPC
	NPC * _npc_padre;
	Enum_Tipo_Ataque _ataque_a_realizar; // Se lee en el Action Manager
	bool _puedo_esquivar;
	
	// Datos de accion y decision propio de cada enemigo
	enum Enum_Decisiones _decision;			// Decision actual 			(Controlado por Pablo)

	// Objetivo actual
	float objetivo_x;
	float objetivo_y;

	// Datos de estado
	float _porcentaje_vida;					// Porcentaje vida actual (Se calcula en cada iteracion) DONE

	// CHARACTER ENEMIGO

	Character* _enemigo_mas_cerca; // Y CON MENOS DE 2 NPCS SIGUIENDOLO
	float _distancia_enemigo_mas_cerca;
	bool _enemigo_mas_cerca_esta_cerca;
	bool _enemigo_mas_cerca_esta_muy_cerca;

	Zona * _zona_actual;
	bool _estoy_en_mi_zona;

	bool _muy_cerca_de_mi_posicion_respawn;

	//Con informacion de la zona
	Nodo_blackboard* _zona;					// Blackbaord de la zona
};

#endif /* SRC_BLACKBOARD_H_ */
