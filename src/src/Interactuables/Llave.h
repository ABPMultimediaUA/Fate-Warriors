#ifndef LLAVE_H_
#define LLAVE_H_

#include "../Objeto.h"

#include <tuple>

class Llave : public Objeto{
public:
	Llave(short _i_id, float _i_x, float _i_y, float _i_z, short _i_id_puerta);
	~Llave();
    
    short get_id_puerta();

	std::tuple<float, float> get_posicion();

private:
	short _id_puerta; // Puerta que puede abrir
};

#endif /* LLAVE_H_ */
