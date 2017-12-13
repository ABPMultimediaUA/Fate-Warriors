#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

class NPC_Manager;
class NPC;
class Player;
class Trampas_manager;
class Consumible_manager;

class Datos_Partida {
public:
	Datos_Partida();
	virtual ~Datos_Partida();

	Player* get_player();

	NPC_Manager* get_npc_manager();
	Trampas_manager* get_trampas_manager();
	Consumible_manager * get_consumible_manager();


private:
	Player* _jugador;

	NPC_Manager* _npc_manager;
	Trampas_manager *_trampas_manager;
	Consumible_manager * _consumibles_manager;
};

#endif /* SRC_DATOS_PARTIDA_H_ */
