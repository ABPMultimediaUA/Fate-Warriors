#ifndef SRC_NPC_MANAGER_H_
#define SRC_NPC_MANAGER_H_

#include <cstdint>

class NPC;
class Ally;

class NPC_Manager {
public:
	NPC_Manager();
	~NPC_Manager();

	NPC** get_npcs();
	uint16_t get_n_enemigos();
	void inserta_npc_nivel();
	
private:
	NPC** _npc;
	Ally** _aliados;

	uint16_t _n_npc;
	uint16_t _n_enemigos;
	uint16_t _n_aliados;
};

#endif /* SRC_NPC_MANAGER_H_ */