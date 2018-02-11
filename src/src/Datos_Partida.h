#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

#include <cstdint>

class NPC_Manager;
class NPC;
class Player;
class Character;
class Consumible_Manager;
class Trampas_manager;
class Interactuable_Manager;
class Armas_Manager;
class Input;
class Zonas_Manager;


class Datos_Partida {
public:
	Datos_Partida(Input* _i_input);
	virtual ~Datos_Partida();

	Player* get_player();

	Trampas_manager* get_trampas_manager();

	NPC_Manager* get_npc_manager();

	Consumible_Manager * get_Consumible_Manager();
    
    Interactuable_Manager* get_interactuable_manager();
	Armas_Manager* get_armas_manager();

	Zonas_Manager* get_zonas_manager();

	void inserta_npc_nivel();

private:
	Player* _jugador;
	Character ** _characters;
	uint16_t _num_characters;
	NPC_Manager* _npc_manager;
	Trampas_manager *_trampas_manager;
	Consumible_Manager * _consumibles_manager;
    Interactuable_Manager * _interactuable_manager;
	Armas_Manager * _armas_manager;
	Zonas_Manager * _zonas_manager;
};

#endif /* SRC_DATOS_PARTIDA_H_ */
