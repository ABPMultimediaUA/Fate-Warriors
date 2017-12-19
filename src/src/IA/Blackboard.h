#ifndef SRC_BLACKBOARD_H_
#define SRC_BLACKBOARD_H_

#include <cstdint>

#include "Enum_Decisiones.h"
#include "Enum_Acciones.h"

#include "Enum_Acciones.h"

#include "../Personajes/Enum_Tipo_Ataque.h"
#include "../Personajes/Enum_Tipo_Enemigo.h"

class Interfaz_Datos;

class Blackboard {
public:
	Blackboard(Interfaz_Datos& _i_interfaz, unsigned short _i_n_enemigo);
	~Blackboard();


	//FUNCIONES DE REFRESCO Y OBTENCION DE DATOS
	void actualiza_datos();									//Actualiza los datos del blackboard para cada iteracion


	//FUNCIONES DE TOMA DE DECISION
	void set_decision(enum Enum_Decisiones _i_decision);	//Set la decision actual
	void set_accion(enum Enum_Acciones _i_accion);			//Set la accion actual


	//FUNCIONES DE DATOS EN PERSONAJE
	unsigned short get_vida();


	//FUNCIONES DE DATOS ALMACENADOS
	unsigned short get_n_enemigo();
	enum Enum_Tipo_Enemigo get_tipo_enemigo();
	unsigned short get_rango_ataque();

	enum Enum_Decisiones get_decision();
	enum Enum_Acciones get_accion();

	int8_t* get_level_of_detail();
	bool get_alertado();

	bool get_tiene_arma();
	bool get_tiene_arma_corta();
	unsigned short get_rango_arma_corta();
	bool get_tiene_arma_larga();
	unsigned short get_rango_arma_larga();

	float get_distancia_jugador();
	enum Enum_Acciones get_accion_jugador();
	bool get_se_acerca();
	bool get_jugador_tiene_arma();

	unsigned short get_n_aliados_zona();

	float get_distancia_objeto();
	bool get_jugador_entre_objeto();

	unsigned short get_n_enemigos_zona();
	float get_distancia_enemigo_cercano();
	float get_distancia_enemigo_lejano();
	bool get_enemigos_tienen_arma();

	unsigned short get_n_pasillos();
	unsigned short get_distancia_pasillos(unsigned short _i_n_pasillo);
	unsigned short get_n_enemigos_min_pasillo();
	unsigned short get_n_paredes_cerca();
	unsigned short get_n_paredes_medio();
	unsigned short get_n_paredes_lejos();

	unsigned short get_zonas_adyacentes();
	unsigned short get_zonas_enemigas();
	unsigned short get_zonas_jugador();

	bool get_interactuable_en_zona_adyacente();
	unsigned short get_id_zona_interactuable();
	bool get_interruptor_en_zona();
	bool get_interruptor_activado();
	unsigned short get_dist_jug_interruptor();
	bool get_powerup_zona_adyacente();
	unsigned short get_id_zona_powerup();

private:
	Interfaz_Datos* _interfaz;

	// Datos de identidad del NPC
	unsigned short _n_npc;					// Numero del NPC
	enum Enum_Tipo_Enemigo *_tipo_npc;		// Tipo de NPC que es

	// Datos de estado
	int16_t* _vida_actual;					// Vida actual
	int16_t _vida_max;						// Vida maxima
	float _porcentaje_vida;					// Porcentaje vida actual (Se calcula en cada iteracion)
	uint8_t* _rango_ataque_normal;			// Rango de ataque normal
	uint8_t* _rango_ataque_fuerte;			// Rango de ataque normal


	// Datos de accion y decision propio de cada enemigo
	enum Enum_Decisiones _decision;			// Decision actual 			(Controlado por Pablo)
	enum Enum_Acciones _accion;				// Accion actual   			(Controlado por Pablo)
	enum Enum_Tipo_Ataque _ataque;			// Ataque actual 			(Controlado por Pablo)


	// Datos de estado
	int8_t _level_of_detail;				// Level of detail que se aplica
	bool _alertado;							// Esta alertado o no  (Controlado por Pablo)


	// Datos de inventario
	bool* _tiene_arma_corta;				// Tiene un arma de corta distancia
	unsigned short* _rango_arma_corta;		// Rango del arma corta
	bool* _tiene_arma_larga;				// Tiene un arma de larga distancia
	unsigned short* _rango_arma_larga;		// Rango del arma larga


	// Blackboard del NPC contrario (PARA LOS ALIADOS PUEDEN SER DE CUALQUIER TIPO DE ENEMIGO Y PARA LOS ENEMIGOS DE TIPO ALIADO)
	Blackboard* _npc_contrario;						// Blackboard del enemigo
	enum Enum_Decisiones _decision_contrario;		// Decision actual 	(VARIABLE DE REFERENCIA)
	enum Enum_Acciones _accion_contrario;			// Accion actual 	(VARIABLE DE REFERENCIA)
	enum Enum_Tipo_Ataque _ataque_contrario;		// Ataque actual 	(VARIABLE DE REFERENCIA)


	// Datos de distancia y percepcion con elementos del entorno

		//Con el jugador
	float _distancia_jugador;				// Distancia a la que se encuentra del jugador
	enum Enum_Acciones _accion_jugador;		// Accion que realiza el jugador actualmente
	enum Enum_Tipo_Ataque _ataque_jugador;		// Ataque actual del jugador
	bool _se_acerca;						// Indica si el jugador se aleja o acerca con respecto a el ultimo instante de tiempo
	bool _jugador_tiene_arma;				// Indica si el jugador tiene arma o no

		//Con aliados (aliados del jugador)
	unsigned short _n_aliados_zona;			// Nº de aliados en la zona

		//Con objetos
	float _distancia_objeto;				// Distancia al objeto mas cercano
	bool _jugador_entre_objeto;				// Dice si el jugador esta entre el objeto mas cercano y yo

		//Con otros enemigos
	unsigned short _n_enemigos_zona;		// Nº de enemigos en la zona
	float _distancia_enemigo_cercano;		// Distancia al enemigo mas cercano
	float _distancia_enemigo_lejano;		// Distancia al enemigo mas lejano de la zona
	bool _enemigos_tienen_arma;				// Indica si algun enemigo en la zona tiene arma

		//Con la propia zona
	unsigned short _n_pasillos;				// Nº de pasillos de la zona
	unsigned short* _distancia_pasillos;	// Distancia a los pasillos de menor a mayor (Eso o crear tantas variables como max de pasillos posible y si no hay pues vale ushortmax o algo asi)
	unsigned short _n_enemigos_min_pasillo;	// Nº de enemigos entre yo y el pasillo mas cercano
	unsigned short _n_paredes_cerca;		// Nº de paredes a menos de 1 metro
	unsigned short _n_paredes_medio;		// Nº de paredes a menos de 3 metros
	unsigned short _n_paredes_lejos;		// Nº de paredes a menos de 6 metros

		//Con otras zonas
	unsigned short _zonas_adyacentes;		// Nº de zonas adyacentes
	unsigned short _zonas_enemigas;			// Nº de zonas de los enemigos
	unsigned short _zonas_jugador;			// Nº de zonas de los jugadores

		//Con objetos interactuables
	bool _interactuable_en_zona_adyacente;	// Indica si hay un interactuable en una zona adyacente
	unsigned short _id_zona_interactuable;	// ID de la zona donde hay interactuable (puede ser una array si hay varias)
	bool _interruptor_en_zona;				// Indica si hay un interruptor en la zona
	bool _interruptor_activado;				// Indica si hay un interruptor activado
	unsigned short _dist_jug_interruptor; 	// Distancia del jugador al interruptor
	bool _powerup_zona_adyacente;			// Indica si hay una zona de powerup en una zona adyacente
	unsigned short _id_zona_powerup;		// ID de la zona donde hay un powerup

};

#endif /* SRC_BLACKBOARD_H_ */
