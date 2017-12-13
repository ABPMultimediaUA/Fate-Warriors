#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto_Movil.h"

class Interfaz;

class Character : public Objeto_Movil{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad);
	virtual ~Character();
	void modificar_vida_en(short _i_vida);
	void poner_vida_a(short _i_vida);
	short get_vida();

protected:
	short _vida;
	short _velocidad;
};

#endif /* SRC_CHARACTER_H_ */
