#include "ND_Set_Objetivo_Personaje_Enemigo_Cerca.h"

#include "../Blackboard.h"
#include "../../Game.h"
#include "../../Datos_Partida.h"
#include "../../Personajes/NPC.h"
#include "../../Interfaz_Libs/Lib_Math.h"

#include<iostream>

ND_Set_Objetivo_Personaje_Enemigo_Cerca::ND_Set_Objetivo_Personaje_Enemigo_Cerca(Nodo_Decision& _i_nodo_izq, Nodo_Decision& _i_nodo_der, float _i_valor) : Nodo_Decision(_i_nodo_izq, _i_nodo_der) {
	_valor = _i_valor;
}

ND_Set_Objetivo_Personaje_Enemigo_Cerca::~ND_Set_Objetivo_Personaje_Enemigo_Cerca() {

}

enum Enum_Acciones ND_Set_Objetivo_Personaje_Enemigo_Cerca::toma_decision(Blackboard* _blackboard){
	float _distancia_enemigo_mas_cercano = 501;

	Objeto * _objetivo = nullptr;

	NPC* _padre = _blackboard->get_npc_padre();
	float x1 = _padre->getX();
	float y1 = _padre->getZ();
	Enum_Equipo _equipo = _padre->get_equipo();
	
    Character ** _characters = Game::game_instancia()->game_get_datos()->get_characters();
	uint16_t _cont, _num_characters;

	_num_characters = Game::game_instancia()->game_get_datos()->get_num_characters();

	for(_cont = 0; _cont < _num_characters; _cont++) {
		if( _characters[_cont]->get_equipo() != _equipo)
		{
			float _distancia = lib_math_distancia_2_puntos(x1, y1, _characters[_cont]->getX(), _characters[_cont]->getZ());
			if(_distancia < _distancia_enemigo_mas_cercano){
				_distancia_enemigo_mas_cercano = _distancia;
				_objetivo = _characters[_cont];
			}
		}	
	}
	

	//std::cout << "distancia= " << _distancia << " y el valor es " << _valor << "\n";
	if(_distancia_enemigo_mas_cercano >= _valor) {
		return _nodo_der->toma_decision(_blackboard);
	}

	_blackboard->objetivo_x = _objetivo->getX();
	_blackboard->objetivo_y = _objetivo->getZ();
	
	return _nodo_izq->toma_decision(_blackboard);
}
