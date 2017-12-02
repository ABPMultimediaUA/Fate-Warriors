#ifndef SRC_ARMA_H_
#define SRC_ARMA_H_

#include "../Objeto.h"

class Arma : public Objeto{
public:
	Arma(short _id, float _i_x, float _i_y, float _i_z, short _tipo, short _i_uses, short _i_frecuencia, short _i_rango);
	virtual ~Arma();
	virtual bool usar() = 0;

	short get_tipo();
	bool decrease_uses();
	short get_uses();

protected:
	short _tipo;
	short _uses;
	short _frecuencia;
	short _rango;
};

#endif /* SRC_ARMA_H_ */
