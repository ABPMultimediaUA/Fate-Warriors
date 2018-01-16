#ifndef SRC_CONSUMIBLE_H_
#define SRC_CONSUMIBLE_H_

#include "../Objeto.h"

class Character;

class Consumible : public Objeto{
public:
	Consumible(short _id, float _i_x, float _i_y, float _i_z, short _i_valor);
	virtual ~Consumible();
	bool comprobar_colision(Character* _character);
	void render();
	void update() override{};
	virtual bool usar(Character* modificar){};
	short get_valor();

protected:
	short _valor;
};

#endif /* SRC_CONSUMIBLE_H_ */
