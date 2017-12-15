#include "Interfaz_Datos.h"

#include "../Datos_Partida.h"
#include "../Game.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/NPC.h"
#include "../Personajes/NPC_Manager.h"
#include "../Personajes/Player.h"

#include<iostream>

Interfaz_Datos::Interfaz_Datos() {
	Game *_game = Game::game_instancia();
	_datos = _game->game_get_datos();
	_npc_manager = _datos->get_npc_manager();
	_game = nullptr;
}

Interfaz_Datos::~Interfaz_Datos() {
	_datos = nullptr;
	_npc_manager = nullptr;
}

// Se trabaja con 2 ejes (X,Y)
// Calcula la distancia absoluta entre el enemigo indicado y el personaje
float Interfaz_Datos::get_distancia_enemigo_personaje(unsigned short _i_n_enemigo) {
	float _x_enemigo, _y_enemigo, _x_player, _y_player, _distancia_total;

	get_pos_enemigo(_i_n_enemigo, _x_enemigo, _y_enemigo);
	get_pos_player(_x_player, _y_player);

	_distancia_total = lib_math_distancia_2_puntos(_x_player, _y_player, _x_enemigo, _y_enemigo);

	return _distancia_total;
}


NPC** Interfaz_Datos::get_enemigos() {
	return _npc_manager->get_npcs();

}

NPC* Interfaz_Datos::get_enemigo(unsigned short _i_n_enemigo) {
	NPC** _enemigos = _npc_manager->get_npcs();
	NPC* _enemigo = _enemigos[_i_n_enemigo];
	_enemigos = nullptr;
	return _enemigo;
}

unsigned short Interfaz_Datos::get_n_enemigos() {
	return _npc_manager->get_n_enemigos();
}

void Interfaz_Datos::get_pos_player(float& _i_x, float& _i_y) {
	Player* _player = _datos->get_player();
	_i_x = _player->getX();
	_i_y = _player->getZ();

	_player = nullptr;
}

void Interfaz_Datos::get_pos_enemigo(unsigned short _i_n_enemigo, float& _i_x, float& _i_y) {
	NPC* _enemigo = get_enemigo(_i_n_enemigo);
	_i_x = _enemigo->getX();
	_i_y = _enemigo->getZ();

	_enemigo = nullptr;
}


