#include "Interfaz_Toma_Decision.h"

#include "../Datos_Partida.h"
#include "../Game.h"
#include "../Interfaz_Libs/Lib_Math.h"
#include "../Personajes/NPC.h"
#include "../Personajes/Player.h"

Interfaz_Toma_Decision::Interfaz_Toma_Decision() {
	Game *_game = Game::game_instancia();
	_datos = _game->game_get_datos();
	_game = nullptr;
}

Interfaz_Toma_Decision::~Interfaz_Toma_Decision() {
	_datos = nullptr;
}


float Interfaz_Toma_Decision::interfaz_decision_distancia_enemigo_personaje(unsigned short _i_n_enemigo) {
	float _x_enemigo, _y_enemigo, _x_player, _y_player;

	this->interfaz_decision_get_pos_enemigo(_i_n_enemigo, _x_enemigo, _y_enemigo);
	this->interfaz_decision_get_pos_player(_x_player, _y_player);

	float _d_x = _x_enemigo - _x_player;
	float _d_y = _y_enemigo - _y_player;

	float _distancia_total = sqrt(_d_x*_d_x + _d_y*_d_y);

	return _distancia_total;
}


NPC** Interfaz_Toma_Decision::interfaz_decision_get_enemigos() {
	return _datos->get_npcs();

}

NPC* Interfaz_Toma_Decision::interfaz_decision_get_enemigo(unsigned short _i_n_enemigo) {
	NPC** _enemigos = _datos->get_npcs();
	NPC* _enemigo = _enemigos[_i_n_enemigo];
	_enemigos = nullptr;
	return _enemigo;
}

unsigned short Interfaz_Toma_Decision::interfaz_decision_get_n_enemigos() {
	return _datos->get_n_enemigos();
}

void Interfaz_Toma_Decision::interfaz_decision_get_pos_player(float& _i_x, float& _i_y) {
	Player* _player = _datos->get_player();
	_i_x = _player->getX();
	_i_y = _player->getZ();

	_player = nullptr;
}

void Interfaz_Toma_Decision::interfaz_decision_get_pos_enemigo(unsigned short _i_n_enemigo, float& _i_x, float& _i_y) {
	NPC* _enemigo = this->interfaz_decision_get_enemigo(_i_n_enemigo);
	_i_x = _enemigo->getX();
	_i_y = _enemigo->getZ();

	_enemigo = nullptr;
}


