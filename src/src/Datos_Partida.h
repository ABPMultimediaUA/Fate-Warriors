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
//class Respawn_Points; 

#include <vector>


class Datos_Partida {
public:
//	virtual Datos_Partida(Input* _i_input);
	virtual ~Datos_Partida(){};

	virtual Player* get_player() = 0;

	virtual Trampas_manager* get_trampas_manager() = 0;

	virtual NPC_Manager* get_npc_manager() = 0;

	virtual Consumible_Manager * get_Consumible_Manager()= 0;
    
    virtual Interactuable_Manager* get_interactuable_manager()=0;
	virtual Armas_Manager* get_armas_manager()=0;

	virtual Zonas_Manager* get_zonas_manager()=0;

	virtual void inserta_npc_nivel()=0;

	virtual Character** get_characters()=0;
	virtual inline uint16_t get_num_characters(){
		return _num_characters;
	}
	virtual Player* crear_jugador(float x, float y)=0;
	virtual std::vector<Player*> dame_jugadores_online()=0;
	virtual std::vector<Player*> todos_jugadores_de_la_sesion()=0;
	virtual inline bool get_is_server(){return isServer;}


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

#endif /* SRC_DATOS_PARTIDA_H_ */
