#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto_Movil.h"

class Interfaz;
class Inventario;

class Character : public Objeto_Movil{
public:
	Character(short _id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte);
	
	virtual ~Character();

	void modificar_vida_en(short _i_vida);
	bool puede_subir_vida_(short _i_vida);
	void poner_vida_a(short _i_vida);
	short get_vida();
    Inventario* get_inventario();
	bool isDead();
	short get_danyo_ataque_normal();
	short get_danyo_ataque_fuerte();
	
protected:
	short _vida_maxima;
	short _vida;
	short _velocidad;
	short _danyo_ataque_normal;
	short _danyo_ataque_fuerte;
    Inventario* _inventario;
};

#endif /* SRC_CHARACTER_H_ */
