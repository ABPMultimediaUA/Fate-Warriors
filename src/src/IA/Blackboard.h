#ifndef SRC_BLACKBOARD_H_
#define SRC_BLACKBOARD_H_

#include <cstdlib>
#include <iostream>
#include "Enum_Decisiones/Enum_Decisiones.h"
#include "Enum_Acciones.h"

#include "Enum_Acciones.h"

#include "../Nivel/Enum_zonas.h"

#include "../Personajes/Enum_Tipo_Ataque.h"
#include "../Personajes/Enum_Tipo_Enemigo.h"
#include "../Nivel/Nodo_blackboard.h"
class Interfaz_Datos;
//class Nodo_blackboard;

class Blackboard {
public:
	Blackboard(Interfaz_Datos& _i_interfaz, uint16_t _i_n_enemigo);
	~Blackboard();


	//FUNCIONES DE REFRESCO Y OBTENCION DE DATOS
	void actualiza_datos();									//Actualiza los datos del blackboard para cada iteracion


	//FUNCIONES DE TOMA DE DECISION
	void set_decision(enum Enum_Decisiones _i_decision);	//Set la decision actual
	void set_accion(enum Enum_Acciones _i_accion);			//Set la accion actual


	// Datos de identidad del NPC
	uint16_t get_n_enemigo();
	enum Enum_Tipo_Enemigo get_tipo_enemigo();
	enum Enum_Tipo_Enemigo get_tipo_npc();

	// Datos de estado
	int16_t get_vida_actual();
	int16_t get_vida_max();
	float get_porcentaje_vida();
	unsigned short get_rango_ataque_normal();
	unsigned short get_rango_ataque_fuerte();


	// Datos de accion y decision propio de cada enemigo
	enum Enum_Decisiones get_decision();
	enum Enum_Acciones get_accion();
	enum Enum_Tipo_Ataque get_ataque();


	// Datos de estado
	int8_t get_level_of_detail();
	bool get_alertado();


	// Datos de inventario
	bool get_tiene_arma();
	bool get_tiene_arma_corta();
	unsigned short get_rango_arma_corta();
	bool get_tiene_arma_larga();
	unsigned short get_rango_arma_larga();


	// Blackboard del NPC contrario (PARA LOS ALIADOS PUEDEN SER DE CUALQUIER TIPO DE ENEMIGO Y PARA LOS ENEMIGOS DE TIPO ALIADO)
	enum Enum_Decisiones get_decision_contrario();
	enum Enum_Acciones get_accion_contrario();
	enum Enum_Tipo_Ataque get_ataque_contrario();
	float get_x_contrario();
	float get_z_contrario();
	float get_distancia_contrario();
	int16_t get_vida_actual_npc_contrario();
	int16_t get_vida_max_npc_contrario();
	float get_porcentaje_vida_contrario();
	bool get_tiene_arma_contrario();
	bool get_tiene_arma_corta_contrario();
	bool get_tiene_arma_larga_contrario();
	bool get_se_acerca_contrario();
	

	//Con el jugador
	enum Enum_Decisiones get_decision_jugador();
	enum Enum_Acciones get_accion_jugador();
	enum Enum_Tipo_Ataque get_ataque_jugador();
	float get_x_jugador();
	float get_z_jugador();
	float get_distancia_jugador();
	int16_t get_vida_actual_jugador();
	int16_t get_vida_max_jugador();
	float get_porcentaje_vida_jugador();
	bool get_tiene_arma_jugador();
	bool get_tiene_arma_corta_jugador();
	bool get_tiene_arma_larga_jugador();
	bool get_se_acerca();
	bool get_jugador_en_zona();
	unsigned short get_distancia_jugador_puerta_cerca();
	bool get_tiene_llave();


	//Con objetos
	float get_distancia_objeto_cercano();
	bool get_jugador_entre_objeto();	


	//Con otros enemigos
	float get_distancia_enemigo_cercano();
	float get_distancia_enemigo_lejano();
	bool get_enemigos_tienen_arma();
	int16_t get_vida_actual_enemigo_cerca();
	int16_t get_vida_maxima_enemigo_cerca();
	float get_porcentaje_vida_enemigo_cerca();
	unsigned short get_n_enemigos_cerca();
	unsigned short get_n_enemigos_medio();
	unsigned short get_n_enemigos_lejos();
	bool get_enemigo_alertado_medio();
	bool get_enemigo_alertado_lejos();


	//Con otros aliados
	float get_distancia_aliado_cercano();
	float get_distancia_aliado_lejano();
	bool get_aliados_tienen_arma();
	int16_t get_vida_actual_aliado_cerca();
	int16_t get_vida_maxima_aliado_cerca();
	float get_porcentaje_vida_aliado_cerca();
	unsigned short get_n_aliados_cerca();
	unsigned short get_n_aliados_medio();
	unsigned short get_n_aliados_lejos();


	//Con informacion de la zona
	int8_t get_n_enemigos_zona();
	int8_t get_n_aliados_zona();
	float get_n_aliados_por_n_enemigos();

	unsigned short get_n_pasillos();
	unsigned short get_distancia_pasillos();
	unsigned short get_n_enemigos_min_pasillo();
	unsigned short get_n_paredes_cerca();
	unsigned short get_n_paredes_medio();
	unsigned short get_n_paredes_lejos();
	bool get_jugador_entre_pasillo_y_yo();


	//Con otras zonas
	unsigned short get_zonas_adyacentes();
	unsigned short get_zonas_enemigas();
	unsigned short get_zonas_jugador();
	enum Enum_zonas get_tipo_zona_cercana();
	bool get_puedo_ir_zona_cercana();


	//Con objetos interactuables
	bool get_interruptor_en_zona();
	bool get_interruptor_activado();
	bool get_soy_enemigo_mas_cerca_interruptor();
	unsigned short get_dist_jug_interruptor();
	bool get_powerup_zona_adyacente();
	unsigned short get_id_zona_powerup();

	//setters
	inline void set_nodo_blackboard(Nodo_blackboard* _i_blackboard){
		_zona=_i_blackboard;
	}

private:
	Interfaz_Datos* _interfaz;		//DONE

	// Datos de identidad del NPC
	unsigned short _n_npc;					// Numero del NPC DONE
	enum Enum_Tipo_Enemigo *_tipo_npc;		// Tipo de NPC que es DONE

	// Datos de estado
	int16_t* _vida_actual;					// Vida actual	DONE
	int16_t _vida_max;						// Vida maxima	DONE
	float _porcentaje_vida;					// Porcentaje vida actual (Se calcula en cada iteracion) DONE
	u_int8_t* _rango_ataque_normal;			// Rango de ataque normal DONE
	u_int8_t* _rango_ataque_fuerte;			// Rango de ataque normal DONE
	float *_x;								// Posicion x del NPC
	float *_z;								// Posicion z del NPC


	// Datos de accion y decision propio de cada enemigo
	enum Enum_Decisiones _decision;			// Decision actual 			(Controlado por Pablo)
	enum Enum_Acciones _accion;				// Accion actual   			(Controlado por Pablo)
	enum Enum_Tipo_Ataque _ataque;			// Ataque actual 			(Controlado por Pablo)


	// Datos de estado
	
	bool _alertado;							// Esta alertado o no  (Controlado por Pablo)


	// Datos de inventario
	bool* _tiene_arma_corta;				// Tiene un arma de corta distancia DONE
	unsigned short* _rango_arma_corta;				// Rango del arma corta DONE
	bool* _tiene_arma_larga;				// Tiene un arma de larga distancia DONE
	unsigned short* _rango_arma_larga;				// Rango del arma larga DONE


	// Blackboard del NPC contrario (PARA LOS ALIADOS PUEDEN SER DE CUALQUIER TIPO DE ENEMIGO Y PARA LOS ENEMIGOS DE TIPO ALIADO)
	Blackboard* _npc_contrario;						// Blackboard del enemigo
	enum Enum_Decisiones _decision_contrario;		// Decision actual npc cercano 	(VARIABLE DE REFERENCIA)
	enum Enum_Acciones _accion_contrario;			// Accion actual npc cercano 	(VARIABLE DE REFERENCIA)
	enum Enum_Tipo_Ataque _ataque_contrario;		// Ataque actual npc cercano 	(VARIABLE DE REFERENCIA)
	//float _x_contrario, _z_contrario;				// Posicion del npc mas cercano (VARIABLE DE REFERENCIA)
	float _distancia_contrario;						// Distancia del npc mas cercano
	//int16_t* _vida_actual_npc_contrario;			// Vida actual npc cercano 		(VARIABLE DE REFERENCIA)
	//int16_t* _vida_max_npc_contrario;				// Vida maxima npc cercano 		(VARIABLE DE REFERENCIA)
	float _porcentaje_vida_contrario;				// Porcentaje vida actual npc cercano (Se calcula en cada iteracion)
	//bool _tiene_arma_contrario;					// Tiene arma o no el contrario (VARIABLE DE REFERENCIA)
	bool* _tiene_arma_corta_contrario;				// Tiene un arma de corta distancia
	bool* _tiene_arma_larga_contrario;				// Tiene un arma de larga distancia
	bool _se_acerca_contrario;						// Indica si el npc se aleja o acerca con respecto a el ultimo instante de tiempo
	

	//Con el jugador
	enum Enum_Decisiones _decision_jugador;			// Decision actual jugador cercano 	(VARIABLE DE REFERENCIA)
	enum Enum_Acciones _accion_jugador;				// Accion actual jugador cercano 	(VARIABLE DE REFERENCIA)
	enum Enum_Tipo_Ataque _ataque_jugador;			// Ataque actual jugador cercano 	(VARIABLE DE REFERENCIA)
	//float _x_jugador, _z_jugador;					// Posicion del jugador mas cercano (VARIABLE DE REFERENCIA)
	float _distancia_jugador;						// Distancia del jugador mas cercano , esta en metros DONE
	//int16_t* _vida_actual_jugador;				// Vida actual jugador cercano 		(VARIABLE DE REFERENCIA)
	//int16_t* _vida_max_jugador;					// Vida maxima jugador cercano 		(VARIABLE DE REFERENCIA)
	float _porcentaje_vida_jugador;					// Porcentaje vida actual jugador cercano (Se calcula en cada iteracion)
	bool* _tiene_arma_corta_jugador;				// Tiene un arma de corta distancia
	bool* _tiene_arma_larga_jugador;				// Tiene un arma de larga distancia
	bool _se_acerca;								// Indica si el jugador se aleja o acerca con respecto a el ultimo instante de tiempo
	bool _jugador_en_zona;							// Indica si el jugador esta o no en la zona
	unsigned short _distancia_jugador_puerta_cerca;		// Distancia del jugador a la puerta mas cercana
	bool _tiene_llave;								// Indica si el jugador tiene o no llave


	//Con objetos
	float _distancia_objeto_cercano;		// Distancia al objeto mas cercano
	bool _jugador_entre_objeto;				// Dice si el jugador esta entre el objeto mas cercano y yo (SE DEBE CALCULAR -> ¿CALCULAR EN EL GET O EN ACTUALIZA?)


	//Con otros enemigos
	float _distancia_enemigo_cercano;		// Distancia al enemigo mas cercano
	float _distancia_enemigo_lejano;		// Distancia al enemigo mas lejano de la zona
	bool _enemigos_tienen_arma;				// Indica si algun enemigo en la zona tiene arma
	int16_t* _vida_actual_enemigo_cerca;	// Vida actual del enemigo cercano
	int16_t _vida_maxima_enemigo_cerca;		// Vida maxima del enemigo cercano
	float _porcentaje_vida_enemigo_cerca;	// Porcentaje vida actual del enemigo cercano (¿Se calcula en cada iteracion?)
	unsigned short _n_enemigos_cerca;				// Nº de enemigos a menos de 3 metros
	unsigned short _n_enemigos_medio;				// Nº de enemigos a menos de 5 metros
	unsigned short _n_enemigos_lejos;				// Nº de enemigos a menos de 7 metros
	bool _enemigo_alertado_medio;			// Indica si hay un aliado alertado a menos de 5 metros (Estas distancias son propensas a variar en un futuro)
	bool _enemigo_alertado_lejos;			// Indica si hay un aliado alertado a menos de 10 metros (Estas distancias son propensas a variar en un futuro)


	//Con otros aliados
	float _distancia_aliado_cercano;		// Distancia al aliado mas cercano
	float _distancia_aliado_lejano;			// Distancia al aliado mas lejano de la zona
	bool _aliados_tienen_arma;				// Indica si algun aliado en la zona tiene arma
	int16_t* _vida_actual_aliado_cerca;	// Vida actual del enemigo cercano
	int16_t _vida_maxima_aliado_cerca;		// Vida maxima del enemigo cercano
	float _porcentaje_vida_aliado_cerca;	// Porcentaje vida actual del enemigo cercano (¿Se calcula en cada iteracion?)
	unsigned short _n_aliados_cerca;				// Nº de aliados a menos de 3 metros
	unsigned short _n_aliados_medio;				// Nº de aliados a menos de 5 metros
	unsigned short _n_aliados_lejos;				// Nº de aliados a menos de 7 metros


	//Con informacion de la zona
	//int8_t _level_of_detail;				// Level of detail que se aplica
	Nodo_blackboard* _zona;					// Blackbaord de la zona
	int8_t* _n_enemigos_zona;				// Nº de enemigos en la zona 	(PUNTERO A ZONA Y GET?)
	int8_t* _n_aliados_zona;				// Nº de aliados en la zona 	(PUNTERO A ZONA Y GET?)
	float _n_aliados_por_n_enemigos;		// Nº aliados / nº de enemigos

	unsigned short _n_pasillos;				// Nº de pasillos de la zona
	unsigned short* _distancia_pasillos;	// Distancia a los pasillos de menor a mayor (Eso o crear tantas variables como max de pasillos posible y si no hay pues vale ushortmax o algo asi)
	unsigned short _n_enemigos_min_pasillo;	// Nº de enemigos entre yo y el pasillo mas cercano
	unsigned short _n_paredes_cerca;		// Nº de paredes a menos de 3 metros
	unsigned short _n_paredes_medio;		// Nº de paredes a menos de 5 metros
	unsigned short _n_paredes_lejos;		// Nº de paredes a menos de 7 metros
	bool _jugador_entre_pasillo_y_yo;		// Indica si el jugador esta entre el pasillo mas cercano y yo


	//Con otras zonas
	unsigned short _zonas_adyacentes;		// Nº de zonas adyacentes
	unsigned short _zonas_enemigas;			// Nº de zonas de los enemigos
	unsigned short _zonas_jugador;			// Nº de zonas de los jugadores
	enum Enum_zonas _tipo_zona_cercana;		// Tipo de la zona mas cercana
	bool _puedo_ir_zona_cercana;			// Indica si se puede acceder a la zona cercana


	//Con objetos interactuables
	bool _interruptor_en_zona;				// Indica si hay un interruptor en la zona
	bool _interruptor_activado;				// Indica si hay un interruptor activado
	bool _soy_enemigo_mas_cerca_interruptor;// Indica si se es el enemigo mas cercano al interruptor
	unsigned short _dist_jug_interruptor; 	// Distancia del jugador al interruptor
	bool _powerup_zona_adyacente;			// Indica si hay una zona de powerup en una zona adyacente
	unsigned short _id_zona_powerup;		// ID de la zona donde hay un powerup

};

#endif /* SRC_BLACKBOARD_H_ */
