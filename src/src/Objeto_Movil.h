#ifndef SRC_OBJETO_MOVIL_H_
#define SRC_OBJETO_MOVIL_H_

#include "Objeto.h"

class Objeto_Movil : public Objeto{
public:
	Objeto_Movil(short _id, float _i_x, float _i_y, float _i_z);
	~Objeto_Movil();
	virtual void update() = 0;

};

#endif /* SRC_OBJETO_MOVIL_H_ */
