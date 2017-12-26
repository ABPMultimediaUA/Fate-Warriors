#include "NPC_Manager.h"
#include <iostream>
#include "NPC.h"
#include "../Nivel/Nivel.h"

NPC_Manager::NPC_Manager() {
	_n_enemigos = 2;
	_n_aliados = 0;
	Nivel* nivel=Nivel::nivel_instancia();

	_npc = new NPC*[_n_enemigos];
	_npc[0] = new NPC(0,18*metro,0,18*metro,50,15, 5, 10);
	nivel->nivel_inserta_NPC(_npc[0]);
	_npc[1] = new NPC(0,6*metro,0,6*metro,50,15, 5, 10);
	nivel->nivel_inserta_NPC(_npc[1]);
}

NPC_Manager::~NPC_Manager() {
	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

NPC** NPC_Manager::get_npcs(){
	return _npc;
}

unsigned short NPC_Manager::get_n_enemigos(){
	return _n_enemigos;
}