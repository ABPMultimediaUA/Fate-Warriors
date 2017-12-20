#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include "../Objeto_Movil.h"
#include "Enum_Tipo_Ataque.h"

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
	void interactuar_con_objeto();
	void atacar(Enum_Tipo_Ataque _i_tipo_ataque);
	void set_tiempo_inicio_bloqueado(double i_tiempo_inicio_bloqueado);
	double get_tiempo_inicio_bloqueado();
	void set_bloqueado(bool i_bloqueado);
	bool get_bloqueado();
	
protected:
	short _vida_maxima;
	short _vida;
	short _velocidad;
	short _danyo_ataque_normal;
	short _danyo_ataque_fuerte;
	double _tiempo_inicio_bloqueado; // El tiempo cuando ha empezado a realizar el Tipo_Accion que bloquea los inputs
	bool _bloqueado; // Si se encuentra bloqueado por el Tipo_Accion
    Inventario* _inventario;
};

#endif /* SRC_CHARACTER_H_ */
