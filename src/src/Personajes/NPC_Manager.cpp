#include "NPC_Manager.h"

#include "NPC.h"
#include "../Nivel/Nivel.h"

#include <iostream>

NPC_Manager::NPC_Manager() {
	_n_npc = 1;

	_npc = new NPC*[_n_npc];
	_npc[0] = new NPC(0, 34*metro, 0, 34*metro, 50, .15, 1, 10, Enum_Equipo_B);
	//_npc[1] = new NPC(0, 32*metro, 0, 29*metro, 50, .15, 1, 10, Enum_Equipo_A);
	//_npc[2] = new NPC(0, 34*metro, 0, 24*metro, 50, .15, 1, 10, Enum_Equipo_B);
	//_npc[3] = new NPC(0, 34*metro, 0, 34*metro, 50, .15, 1, 10, Enum_Equipo_A);
	//_npc[4] = new NPC(0, 35*metro, 0, 35*metro, 50, .15, 1, 10, Enum_Equipo_B);
	//_npc[5] = new NPC(0, 33*metro, 0, 33*metro, 50, .15, 1, 10, Enum_Equipo_A);
}

NPC_Manager::~NPC_Manager() {
	for(uint16_t _cont=0; _cont<_n_npc; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

NPC** NPC_Manager::get_npcs(){
	return _npc;
}

uint16_t NPC_Manager::get_n_npc(){
	return _n_npc;
}
void NPC_Manager::inserta_npc_nivel(){
	Nivel* nivel=Nivel::nivel_instancia();
	for(uint8_t cont=0;cont<(_n_npc);++cont){
		nivel->nivel_inserta_NPC(_npc[cont]);
	}
}