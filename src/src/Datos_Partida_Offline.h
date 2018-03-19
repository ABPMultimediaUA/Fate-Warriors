#ifndef SRC_DATOS_PARTIDA_OFFLINE_H_
#define SRC_DATOS_PARTIDA_OFFLINE_H_

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


class Datos_Partida_Offline : public Datos_Partida {
public:
	Datos_Partida_Offline(Input* _i_input);
	~Datos_Partida_Offline();

	Player* get_player() override;

	Trampas_manager* get_trampas_manager()override;

	NPC_Manager* get_npc_manager()override;

	Consumible_Manager * get_Consumible_Manager()override;
    
    Interactuable_Manager* get_interactuable_manager()override;
	Armas_Manager* get_armas_manager()override;

	Zonas_Manager* get_zonas_manager()override;

	void inserta_npc_nivel()override;

	Character** get_characters();
	inline uint16_t get_num_characters(){
		return _num_characters;
	}
	Player* crear_jugador(float x, float y);
	std::vector<Player*> dame_jugadores_online() override;
	std::vector<Player*> todos_jugadores_de_la_sesion() override;
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

#endif /* SRC_DATOS_PARTIDA_OFFLINE_H_ */
