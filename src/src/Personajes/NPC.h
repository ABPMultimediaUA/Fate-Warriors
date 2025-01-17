#ifndef SRC_NPC_H_
#define SRC_NPC_H_
#include "Character.h"

class Blackboard;
class Motor;

class NPC : public Character {
public:
	NPC(float _i_x, float _i_z, int16_t _i_vida, float _i_velocidad, int16_t _i_danyo_ataque_normal, int16_t _i_danyo_ataque_fuerte, Enum_Equipo equipo);
	virtual ~NPC();
	
	void stop();

	void danyar(int16_t _danyo) override;
	void morir() override;

	void set_blackboard(Blackboard* _i_blackboard);
	inline Blackboard* get_blackboard() { return _blackboard;}

	void play_voces_ataque() override;
	void play_animaciones_ataque() override;
	void play_animaciones_recibir_danyo() override;

	void animacion_idle();
	void animacion_andar() override;
	void animacion_correr() override;

	void aparecer_muerto();

protected:
	Blackboard* _blackboard; //Informacion de la memoria almacenada en el Blackboard

private:
	uint8_t _tipo_npc;
	void anim_ataque_tipo_1();
	void anim_ataque_tipo_2();
};

#endif /* SRC_NPC_H_ */
