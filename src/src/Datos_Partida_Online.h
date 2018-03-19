#ifndef SRC_DATOS_PARTIDA_ONLINE_H_
#define SRC_DATOS_PARTIDA_ONLINE_H_

#include <cstdint>

#include "Datos_Partida.h"

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
//class Respawn_Points; 

#include <vector>


class Datos_Partida_Online : public Datos_Partida{
public:
	Datos_Partida_Online(Input* _i_input);
	~Datos_Partida_Online();

	Player* get_player();

	Trampas_manager* get_trampas_manager();

	NPC_Manager* get_npc_manager();

	Consumible_Manager * get_Consumible_Manager();
    
    Interactuable_Manager* get_interactuable_manager();
	Armas_Manager* get_armas_manager();

	Zonas_Manager* get_zonas_manager();

	void inserta_npc_nivel();

	Character** get_characters();
	inline uint16_t get_num_characters(){
		return _num_characters;
	}
	Player* crear_jugador(float x, float y);
	std::vector<Player*> dame_jugadores_online();
	std::vector<Player*> todos_jugadores_de_la_sesion();
	inline bool get_is_server(){return isServer;}


private:

	std::vector<Player*> _jugadores_online;
	std::vector<Player*> _jugadores_online_incluyendo_player;
	Player* _jugador;
	Character ** _characters;
	uint16_t _num_characters;
	NPC_Manager* _npc_manager;
	Trampas_manager *_trampas_manager;
	Consumible_Manager * _consumibles_manager;
    Interactuable_Manager * _interactuable_manager;
	Armas_Manager * _armas_manager;
	Zonas_Manager * _zonas_manager;
		bool isServer;


};

#endif /* SRC_DATOS_PARTIDA_ONLINE_H_ */
