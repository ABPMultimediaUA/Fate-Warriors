#ifndef SRC_CONSUMIBLE_H_
#define SRC_CONSUMIBLE_H_

#include "../Objeto.h"

class Character;

class Consumible : public Objeto{
public:
	Consumible(short _id, float _i_x, float _i_y, float _i_z, short _i_valor);
	virtual ~Consumible();
	
	bool comprobar_colision(Character* _character);
	virtual bool usar(Character* modificar){};
	short get_valor();

	inline void set_esta_lejos(bool estado){_esta_lejos = estado;};
	inline bool get_esta_lejos(){return _esta_lejos;};
	virtual void cambiar_modelado() = 0;
	
protected:
	short _valor;
	bool _esta_lejos;
};

#endif /* SRC_CONSUMIBLE_H_ */
