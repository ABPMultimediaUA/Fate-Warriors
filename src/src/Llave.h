#ifndef LLAVE_H_
#define LLAVE_H_

#include "Objeto.h"

class Llave : public Objeto{
public:
	Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta);
	virtual ~Llave();
	void update(){};
	void render(){};
    
    short get_id_puerta();

private:
	short _id_puerta; // Puerta que puede abrir
};

#endif /* LLAVE_H_ */
