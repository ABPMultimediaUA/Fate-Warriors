#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto_Movil.h"

class Interfaz;
class Inventario;

class Character : public Objeto_Movil{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad);
	virtual ~Character();

	void modificar_vida_en(short _i_vida);
	bool puede_subir_vida_(short _i_vida);
	void poner_vida_a(short _i_vida);
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
	
protected:
	short _vida_maxima;
	short _vida;
	short _velocidad;
	uint8_t _rango_arma_corta;
	uint8_t _rango_arma_larga;
    Inventario* _inventario;
	bool _tiene_arma_corta;
	bool _tiene_arma_larga;
};

#endif /* SRC_CHARACTER_H_ */
