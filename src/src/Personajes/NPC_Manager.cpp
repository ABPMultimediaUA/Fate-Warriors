#include "NPC_Manager.h"

#include "NPC.h"
#include "../Nivel/Nivel.h"

#include <iostream>

NPC_Manager::NPC_Manager() {

	_n_npc = 0;

	_npc = new NPC*[_n_npc];
	/*
	_npc[0] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	/*
	_npc[1] = new NPC(0, 34*metro, 0, 34*metro, 1, .15, 10, 20, Enum_Equipo_A);
	
	_npc[2] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[3] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	_npc[4] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[5] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	_npc[6] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[7] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	_npc[8] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[9] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	
	_npc[10] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	_npc[11] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	_npc[12] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[13] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);

	*/
	/*
	_npc[14] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[15] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[16] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[17] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[18] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_B);
	_npc[19] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[20] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[21] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[22] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[23] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[24] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	
	_npc[25] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_A);
	_npc[26] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[27] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[28] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[29] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[30] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[31] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[32] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[33] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[34] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[35] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[36] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[37] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[38] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[39] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[40] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[41] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[42] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[43] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[44] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[45] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[46] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[47] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[48] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	_npc[49] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 1, 10, Enum_Equipo_B);
	*/

	
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