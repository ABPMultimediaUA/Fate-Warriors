#ifndef SRC_ARMA_H_
#define SRC_ARMA_H_

#include "../Objeto.h"
#include "../Time/Time.h"

class Arma : public Objeto{

public:	
	
	Arma(short _id, float _i_x, float _i_y, float _i_z, short _tipo, short _i_uses, short _i_frecuencia, short _i_rango);
	virtual ~Arma();
	virtual bool usar(float _i_x, float _i_y, float _i_z) = 0;

	bool 	preparado_siguiente_ataque();
	void 	actualizar_tiempo_siguiente_ataque();
	bool 	decrease_uses();
	
	short 	get_tipo();
	short 	get_uses();
	short 	get_frecuencia();
	short 	get_rango();

protected:
	
	double 	_tiempo_siguiente_disponible;
	short 	_tipo;
	short 	_uses;
	short 	_frecuencia;
	short 	_rango;

};

#endif /* SRC_ARMA_H_ */
