#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

#include <cstdint>

class NPC_Manager;
class NPC;
class Player;
class Character;
class Consumible_Manager;
class Interactuable_Manager;
class Input;
class Zonas_Manager;
//class Respawn_Points; 


class Datos_Partida {
public:
	Datos_Partida(Input* _i_input);
	virtual ~Datos_Partida();

	Player* get_player();

	NPC_Manager* get_npc_manager();

	Consumible_Manager * get_Consumible_Manager();
    
    Interactuable_Manager* get_interactuable_manager();

	Zonas_Manager* get_zonas_manager();

	void inserta_npc_nivel();

	Character** get_characters();
	inline uint16_t get_num_characters(){
		return _num_characters;
	}

private:
	Player* _jugador;
	Character ** _characters;
	uint16_t _num_characters;
	NPC_Manager* _npc_manager;
	Consumible_Manager * _consumibles_manager;
    Interactuable_Manager * _interactuable_manager;
	Zonas_Manager * _zonas_manager;

};

#endif /* SRC_DATOS_PARTIDA_H_ */
