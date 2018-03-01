#ifndef PUERTA_H_
#define PUERTA_H_

#include "Objeto.h"

class Puerta : public Objeto{
public:
	Puerta(short _i_id, float _i_x, float _i_y, float _i_z, float _i_rotacion, bool _i_abierta, uint16_t _i_id_pasillo_que_abre);
	virtual ~Puerta();
    void update(){};
	void render(){};

	void set_abierta(bool _i_abierta);
	bool get_abierta();

private:
	bool _abierta;
	uint8_t _id_pasillo_que_abre;
};

#endif /* PUERTA_H_ */
