#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto.h"
#include "../IA/Enum_Acciones.h"

#include "Enum_Tipo_Ataque.h"

class Interfaz;
class Inventario;
class Time;
class Arma;
class Consumible_Power_Up;
class Zona;
class Interfaz_sonido;

class Character : public Objeto{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte, Enum_Equipo equipo);
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
	inline int16_t get_vida_actual(){
		return _vida;
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
	inline int get_npcs_persiguiendome(){
		return _npcs_persiguiendome;
	}
	inline void incrementar_npcs_persiguiendome(){
		_npcs_persiguiendome++;
	}
	inline void decrementar_npcs_persiguiendome(){
		_npcs_persiguiendome--;
	}
	inline void reiniciar_npcs_persiguiendome(){
		_npcs_persiguiendome = 0;
	}
	uint8_t* get_ref_rango_arma_corta();
	uint8_t* get_ref_rango_arma_larga();
    Inventario* get_inventario();
	bool isDead();
	short get_danyo_ataque_normal();
	short get_danyo_ataque_fuerte();
	bool interactuar_con_objeto();
	void atacar(Enum_Tipo_Ataque _i_tipo_ataque);
	virtual void morir();
	void revivir(Vector2 pos);
	Enum_Acciones get_accion();
	Enum_Tipo_Ataque get_tipo_ataque();
	void saltar();
	void esquivar(uint16_t _direccion);
	void mover(uint16_t _direccion);
	void mover_direccion(uint16_t _i_direccion, uint16_t _i_direccion_mover);
	bool esta_bloqueado();
	bool accion_en_curso();

	bool intentar_recoger_arma();
	void coger_arma(Arma* arma);
	void cambiar_arma_seleccionada_a_la_siguiente();
	void cambiar_arma_seleccionada_a_la_anterior();

	uint16_t get_direccion_actual();
	void set_direccion_actual(uint16_t nueva_direccion);


	void anyadir_power_up(Consumible_Power_Up* _i_power_up);
	void eliminar_power_up_puntero();

	Enum_Equipo get_equipo();

	// Gestion de acciones
	void impulso_danyar(Character * atacante, Character * atacado, int impulso);
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
	virtual void gestion_dash();
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
	void rotar_cuerpo(uint16_t _i_valor);
	void rotar_cuerpo_sin_interpolacion(uint16_t _i_valor);

	bool _bloqueado; // Si se encuentra bloqueado por el Tipo_Accion

	void set_zona_en_la_que_se_encuentra(Zona * _zona);
	Zona* get_zona();

	virtual void play_voces_ataque();
	virtual void play_animaciones_ataque();

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
	Enum_Equipo _equipo;
	Zona* _zona_en_la_que_se_encuentra;

	Interfaz_sonido* _sonido;

	int _npcs_persiguiendome;
};

#endif /* SRC_CHARACTER_H_ */
