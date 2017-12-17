#ifndef PUERTA_H_
#define PUERTA_H_

#include "Objeto.h"

class Puerta : public Objeto{
public:
	Puerta(short _i_id, float _i_x, float _i_y, float _i_z, bool _i_abierta);
	virtual ~Puerta();
    void update(){};
	void render(){};

	void set_abierta(bool _i_abierta);

private:
	bool _abierta;
};

#endif /* PUERTA_H_ */
