#ifndef SRC_NPC_H_
#define SRC_NPC_H_
#include "Enum_Tipo_Enemigo.h"
#include "Character.h"

class Blackboard;
class Motor;
class Armas_Manager;

class NPC : public Character {
public:
	NPC(short _i_id, float _i_x, float _i_y, float _i_z, short _i_vida, float _i_velocidad, short _i_danyo_ataque_normal, 
	short _i_danyo_ataque_fuerte, Enum_Equipo equipo);
	virtual ~NPC();
	
	void comprobar_si_asignar_arma_y_asignarla(Armas_Manager* _armas_manager);
	void stop();

	void danyar(short _danyo) override;
	void morir() override;

	void set_blackboard(Blackboard* _i_blackboard);
	inline Blackboard* get_blackboard() { return _blackboard;}

protected:
	Blackboard* _blackboard; //Informacion de la memoria almacenada en el Blackboard
};

#endif /* SRC_NPC_H_ */
