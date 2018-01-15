#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

class NPC_Manager;
class NPC;
class Player;
class Consumible_Manager;
class Trampas_manager;
class Interactuable_Manager;
class Armas_Manager;
class Input;


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


	void inserta_npc_nivel();

private:
	Player* _jugador;

	NPC_Manager* _npc_manager;
	Trampas_manager *_trampas_manager;
	Consumible_Manager * _consumibles_manager;
    Interactuable_Manager * _interactuable_manager;
	Armas_Manager * _armas_manager;


};

#endif /* SRC_DATOS_PARTIDA_H_ */
