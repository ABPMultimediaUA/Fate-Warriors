#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

class NPC;
class Player;

class Datos_Partida {
public:
	Datos_Partida();
	virtual ~Datos_Partida();

	unsigned short get_n_enemigos();
	Player* get_player();
	NPC** get_npcs();

private:
	Player* _jugador;
	NPC** _npc;

	unsigned short _n_enemigos;
};

#endif /* SRC_DATOS_PARTIDA_H_ */
