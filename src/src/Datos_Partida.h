#ifndef SRC_DATOS_PARTIDA_H_
#define SRC_DATOS_PARTIDA_H_

class NPC;
class Player;
class Trigger_zona_vida;
class Trigger_region;
class AD_Ametralladora;



class Datos_Partida {
public:
	Datos_Partida();
	virtual ~Datos_Partida();

	unsigned short get_n_enemigos();
	Player* get_player();
	NPC** get_npcs();
	Trigger_zona_vida* get_trigger();

private:
	
	Player* _jugador;
	NPC** _npc;
	AD_Ametralladora* _ametralladora;
	Trigger_zona_vida* trigger_zona_vida1; 
	unsigned short _n_enemigos;
};

#endif /* SRC_DATOS_PARTIDA_H_ */
