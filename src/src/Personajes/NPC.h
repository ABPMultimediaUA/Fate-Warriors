#ifndef SRC_NPC_H_
#define SRC_NPC_H_
#include "Enum_Tipo_Enemigo.h"
#include "Character.h"

class Blackboard;
class Motor;

class NPC : public Character {
public:
	NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, short _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte, Enum_Tipo_Enemigo _i_tipo_npc);
	
	virtual ~NPC();
  	void update() override;
  	void render() override;
	void move(unsigned long _i_direccion);
	void stop();

	void set_blackboard(Blackboard* _i_blackboard);
	Blackboard* get_blackboard();
	inline enum Enum_Tipo_Enemigo* get_ref_Enum_Tipo_Enemigo(){
		return &_tipo_npc;
	}
	void setPositionXZ(float _i_x, float _i_z);
	

protected:
	Blackboard* _blackboard; //Informacion de la memoria almacenada en el Blackboard
	enum Enum_Tipo_Enemigo _tipo_npc;
};

#endif /* SRC_NPC_H_ */
