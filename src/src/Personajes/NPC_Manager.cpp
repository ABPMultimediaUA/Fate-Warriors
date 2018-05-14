#include "NPC_Manager.h"

#include "NPC.h"
#include "../Nivel/Nivel.h"

#include <iostream>

NPC_Manager::NPC_Manager() {
	_n_npc = 50;
	_npc = new NPC*[_n_npc];
	for(uint16_t i=0; i<_n_npc; i++) {
		int16_t _vida;
		float _velocidad;
		int16_t _danyo_d;
		int16_t _danyo_f;
		Enum_Equipo _equipo;

		if(rand()%2 == 0) {
			_equipo = Enum_Equipo_A;

			_vida = 225;
			_velocidad = .14;
			_danyo_d = 20;
			_danyo_f = 30;
		}
		else {
			_equipo = Enum_Equipo_B;

			_vida = 120;
			_velocidad = .17;
			_danyo_d = 15;
			_danyo_f = 25;
		}

		_npc[i] = new NPC(34*metro, 34*metro, _vida, _velocidad, _danyo_d, _danyo_f, _equipo);
	}
	/*_npc[0] = new NPC(0, 34*metro, 0, 34*metro, 100, .15, 10, 20, Enum_Equipo_A);
	// PLAYER DMG - 50, 75

	// Equipo A - CASCOS

	+ VIDA
	- VELOCIDAD


	// Equipo B - PUNKY

	+ VELOCIDAD
	+ ATAQUE


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