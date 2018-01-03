#ifndef SRC_NPC_MANAGER_H_
#define SRC_NPC_MANAGER_H_

class NPC;

class NPC_Manager {
public:
	NPC_Manager();
	~NPC_Manager();

	NPC** get_npcs();
	unsigned short get_n_enemigos();
	void inserta_npc_nivel();
	
private:
	NPC** _npc;

	unsigned short _n_enemigos;
	unsigned short _n_aliados;
};

#endif /* SRC_NPC_MANAGER_H_ */