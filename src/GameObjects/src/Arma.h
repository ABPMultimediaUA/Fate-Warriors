#ifndef SRC_ARMA_H_
#define SRC_ARMA_H_

#include "Objeto.h"

class Arma : public Objeto{
public:
	Arma(short _id, float _i_x, float _i_y, float _i_z, short _i_uses);
	virtual ~Arma();

	bool decrease_uses();
	short get_uses();

protected:
	short _uses;
};

#endif /* SRC_ARMA_H_ */
