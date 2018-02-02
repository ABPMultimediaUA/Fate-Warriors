#ifndef SRC_ARMA_H_
#define SRC_ARMA_H_

#include "../Objeto.h"
#include "../Tiempo/Time.h"

class Time;


class Arma : public Objeto{

public:	
	
	Arma(uint16_t _id, float _i_x, float _i_y, float _i_z, short _tipo, short _i_uses, short _i_frecuencia, short _i_rango);
	virtual ~Arma();
	virtual Character* usar(uint16_t _i_direccion) = 0;

	bool 	preparado_siguiente_ataque();
	void 	actualizar_tiempo_siguiente_ataque();
	bool 	decrease_uses();
	
	short 	get_tipo();
	short 	get_uses();
	short 	get_frecuencia();
	short 	get_rango();

protected:
	
	Time*  _reloj;
	double 	_tiempo_siguiente_disponible;
	uint8_t 	_tipo;
	uint8_t 	_uses;
	uint8_t 	_frecuencia;
	uint8_t 	_rango;

};

#endif /* SRC_ARMA_H_ */
