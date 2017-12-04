#include "Datos_Partida.h"

Datos_Partida::Datos_Partida() {
	_jugador = new Player(10, 0, 10);

	_n_enemigos = 1;

	_npc = new NPC*[_n_enemigos];

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		_npc[_cont] = new NPC(5, 0, 0);
	}

}

Datos_Partida::~Datos_Partida() {
	delete _jugador;

	for(unsigned short _cont=0; _cont<_n_enemigos; _cont++) {
		delete _npc[_cont];
	}
	delete [] _npc;
}

unsigned short Datos_Partida::get_n_enemigos(){
	return _n_enemigos;
}

Player* Datos_Partida::get_player(){
	return _jugador;
}

NPC** Datos_Partida::get_npcs(){
	return _npc;
}
