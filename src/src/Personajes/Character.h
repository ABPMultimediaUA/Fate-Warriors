#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto_Movil.h"
#include "../IA/Enum_Acciones.h"
#include "Enum_Tipo_Ataque.h"

class Interfaz;
class Inventario;
class Time;
class Arma;
class Consumible_Power_Up;

class Character : public Objeto_Movil{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);
	
	virtual ~Character();

	virtual void modificar_vida_en(short _i_vida); // este metodo debe derivar en danyar y curar
	void danyar_comun(short _danyo); // el danyo es lo mismo que los puntos de vida que se le restan
	virtual void danyar(short _danyo) = 0;
	bool puede_subir_vida_(short _i_vida);
	virtual void set_vida(short _i_vida);
	short get_vida();
	inline int16_t get_vida_maxima(){
		return _vida_maxima;
	}
	inline int16_t* get_ref_vida_actual(){
		return &_vida;
	}
	inline bool* get_ref_tiene_arma_corta(){
    	return &_tiene_arma_corta;
	}
	inline bool* get_ref_tiene_arma_larga(){
    	return &_tiene_arma_larga;
	}
	inline float* get_ref_x(){
		//return &_x; Tiene que coger la posicion del motor
	}
	inline float* get_ref_z(){
		//return &_z; Tiene que coger la posicion del motor
	}
	uint8_t* get_ref_rango_arma_corta();
	uint8_t* get_ref_rango_arma_larga();
    Inventario* get_inventario();
	bool isDead();
	short get_danyo_ataque_normal();
	short get_danyo_ataque_fuerte();
	bool interactuar_con_objeto();
	void atacar(Enum_Tipo_Ataque _i_tipo_ataque);
	void morir();
	Enum_Acciones get_accion();
	Enum_Tipo_Ataque get_tipo_ataque();
	void saltar();
	void esquivar(uint16_t _direccion);
	void mover(uint16_t _direccion);
	void disparar(uint16_t _direccion);
	bool esta_bloqueado();
	bool accion_en_curso();

	bool intentar_recoger_arma();
	void coger_arma(Arma* arma);
	void cambiar_arma_seleccionada_a_la_siguiente();
	void cambiar_arma_seleccionada_a_la_anterior();


	void anyadir_power_up(Consumible_Power_Up* _i_power_up);
	void eliminar_power_up_puntero();

	// Gestion de acciones
	void impulso_danyar(Character * atacante, Character * atacado, Enum_Tipo_Ataque tipo_ataque);
	Enum_Tipo_Ataque get_tipo_ataque_combo(Enum_Tipo_Ataque new_tipo_ataque);
	uint8_t get_danyo_ataque(Enum_Tipo_Ataque tipo_ataque);
	int get_impulso_danyar(Enum_Tipo_Ataque tipo_ataque);
	void set_tipo_ataque(Enum_Tipo_Ataque _i_tipo_ataque);
	void set_accion(Enum_Acciones _i_accion);
	int getTiempoAccion(Enum_Acciones _accion);
	btVector3 getPosicionRbAtaque(Enum_Tipo_Ataque _ataque);
	btVector3 getEscalaRbAtaque(Enum_Tipo_Ataque _ataque);
	void gestion_acciones();
	virtual void gestion_ataque();
	void gestion_dash();
	void gestion_saltar();
	void gestion_interactuar();
	void gestion_recibir_danyado();
	void gestion_mover();
	
	void aumentar_danyo_ataque_fuerte(uint8_t _i_valor);
	void aumentar_danyo_ataque_normal(uint8_t _i_valor);
	void disminuir_danyo_ataque_fuerte(uint8_t _i_valor);
	void disminuir_danyo_ataque_normal(uint8_t _i_valor);
	
	void activar_inmunidad_a_danyos();
	void desactivar_inmunidad_a_danyos();

protected:
	
	int16_t _vida_maxima;
	int16_t _vida;
	float _velocidadAndar;		//velocidad al andar
	float _velocidad;
	float _velocidadCorrer;
	uint8_t _rango_arma_corta;
	uint8_t _rango_arma_larga;
	short _danyo_ataque_normal;
	short _danyo_ataque_fuerte;
	double _tiempo_inicio_accion; // El tiempo cuando ha empezado a realizar el Tipo_Accion
	bool _bloqueado; // Si se encuentra bloqueado por el Tipo_Accion
    Inventario* _inventario;
	bool _tiene_arma_corta;
	bool _tiene_arma_larga;
	Enum_Acciones _accion;
	Enum_Tipo_Ataque _tipo_ataque;
	Time * _tiempo;
	double _duracion_accion_actual;
	Consumible_Power_Up* _power_up;
	btRigidBody *_rb_ataque;
	uint16_t _direccion_actual;
	bool _inmortal;
};

#endif /* SRC_CHARACTER_H_ */
