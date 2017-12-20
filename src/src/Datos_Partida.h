#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

class NPC_Manager;
class NPC;
class Player;
class Consumible_manager;
class Trampas_manager;
class Interactuable_Manager;
class Objeto_Estandar;


class Datos_Partida {
public:
	Datos_Partida();
	virtual ~Datos_Partida();

	Player* get_player();

	Trampas_manager* get_trampas_manager();

	NPC_Manager* get_npc_manager();

	Consumible_manager * get_consumible_manager();
    
    Interactuable_Manager* get_interactuable_manager();

private:
	Player* _jugador;
	Objeto_Estandar* _mapa;
	NPC_Manager* _npc_manager;
		Trampas_manager *_trampas_manager;
	Consumible_manager * _consumibles_manager;
    Interactuable_Manager * _interactuable_manager;

};

#endif /* SRC_DATOS_PARTIDA_H_ */
