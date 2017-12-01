#ifndef SRC_NPC_H_
#define SRC_NPC_H_

#include "Character.h"
#include "Enum_Acciones.h"

class NPC : public Character {
public:
	NPC(float _i_vida, float _i_x, float _i_y);
	virtual ~NPC();

	void set_action(enum Enum_Acciones _i_accion);
	void do_action();
	enum Enum_Acciones get_action();

	void move(unsigned long _i_direccion);

private:
	enum Enum_Acciones _accion_actual;
};

#endif /* SRC_NPC_H_ */
