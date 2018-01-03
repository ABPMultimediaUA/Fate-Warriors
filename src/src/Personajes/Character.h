#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto_Movil.h"
#include "../IA/Enum_Acciones.h"
#include "Enum_Tipo_Ataque.h"

class Interfaz;
class Inventario;
class Time;

class Character : public Objeto_Movil{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);
	
	virtual ~Character();

	void modificar_vida_en(short _i_vida); // este metodo debe derivar en danyar y curar
	void danyar(short _danyo); // el danyo es lo mismo que los puntos de vida que se le restan
	bool puede_subir_vida_(short _i_vida);
	void set_vida(short _i_vida);
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
		return &_x;
	}
	inline float* get_ref_z(){
		return &_z;
	}
	uint8_t* get_ref_rango_arma_corta();
	uint8_t* get_ref_rango_arma_larga();
    Inventario* get_inventario();
	bool isDead();
	short get_danyo_ataque_normal();
	short get_danyo_ataque_fuerte();
	void interactuar_con_objeto();
	void atacar(Enum_Tipo_Ataque _i_tipo_ataque);
	void bloquear_input(double _i_duracion_bloqueo_actual); //Cuando ha empezado a realizar el Tipo_Accion que bloquea los inputs
	void morir();
	Enum_Acciones get_accion();
	void set_accion(Enum_Acciones _i_accion);
	Enum_Tipo_Ataque get_tipo_ataque();
	void set_tipo_ataque(Enum_Tipo_Ataque _i_tipo_ataque);
	void bucle_ataque();
	bool esta_bloqueado();
	void desbloquear_input();

protected:
	int16_t _vida_maxima;
	int16_t _vida;
	short _velocidad;
	uint8_t _rango_arma_corta;
	uint8_t _rango_arma_larga;
	short _danyo_ataque_normal;
	short _danyo_ataque_fuerte;
	double _tiempo_inicio_bloqueado; // El tiempo cuando ha empezado a realizar el Tipo_Accion que bloquea los inputs
	//bool _bloqueado; // Si se encuentra bloqueado por el Tipo_Accion
    Inventario* _inventario;
	bool _tiene_arma_corta;
	bool _tiene_arma_larga;
	Enum_Acciones _accion;
	Enum_Tipo_Ataque _tipo_ataque;
	Time * _tiempo;
	double _duracion_bloqueo_actual; // Duracion del bloqueo actual
};

#endif /* SRC_CHARACTER_H_ */
