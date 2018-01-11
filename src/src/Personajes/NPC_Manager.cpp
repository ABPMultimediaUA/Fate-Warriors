#include "NPC_Manager.h"

#include "NPC.h"

#include "NPC/Ally.h"
#include "NPC/Enemy_Normal.h"

#include "../Nivel/Nivel.h"

#include <iostream>

NPC_Manager::NPC_Manager() {
	_n_enemigos = 4;
	_n_aliados = 0;


	_npc = new NPC*[_n_enemigos];
	_npc[0] = new Enemy_Normal(0, 34*metro, 0, 34*metro, 50, 15, 5, 10);
	_npc[1] = new Enemy_Normal(0, 32*metro, 0, 29*metro, 50, 15, 5, 10);
	_npc[2] = new Enemy_Normal(0, 34*metro, 0, 24*metro, 50, 15, 5, 10);
	_npc[3] = new Ally(0, 45*metro, 0, 40*metro, 50, 15, 5, 10);
}

NPC_Manager::~NPC_Manager() {
	for(uint16_t _cont=0; _cont<_n_enemigos; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

NPC** NPC_Manager::get_npcs(){
	return _npc;
}

uint16_t NPC_Manager::get_n_enemigos(){
	return _n_enemigos;
}
void NPC_Manager::inserta_npc_nivel(){
	Nivel* nivel=Nivel::nivel_instancia();
	for(u_int8_t cont=0;cont<(_n_enemigos);++cont){
		nivel->nivel_inserta_NPC(_npc[cont]);
	}
}