#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

class NPC_Manager;
class NPC;
class Player;
class Objeto_Estandar;

class Datos_Partida {
public:
	Datos_Partida();
	virtual ~Datos_Partida();

	Player* get_player();

	NPC_Manager* get_npc_manager();

private:
	Player* _jugador;
	Objeto_Estandar* _mapa;
	NPC_Manager* _npc_manager;
};

#endif /* SRC_DATOS_PARTIDA_H_ */
