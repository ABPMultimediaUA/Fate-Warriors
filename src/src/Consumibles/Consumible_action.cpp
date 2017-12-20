#include "Consumible_action.h"

#include "../Tiempo/Time.h"
#include "Consumible_carne.h"
#include "Consumible_patata.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "Consumible_manager.h"
#include "../Personajes/Player.h"
#include "../Utilidades/Vector.h"

Consumible_action::Consumible_action() : _player(nullptr), _consumibles_manager(nullptr){
	Game* punterito 		= Game::game_instancia();
	Datos_Partida * datitos	= punterito->game_get_datos();

	_player 				= datitos->get_player();
	_consumibles_manager 	= datitos->get_consumible_manager();
	_consumibles 			= _consumibles_manager->get_consumibles();
}

Consumible_action::~Consumible_action(){
	_consumibles_manager 	= nullptr;
	_player					= nullptr;
}

void Consumible_action::comprobar_consumibles(){

	Vector2 vec_player	= _player->get_vector();
	short tamanio =(*_consumibles).size();
	
	for(short a=0; a<tamanio; a++){
		Vector2 vec_mina	= (*_consumibles)[a]->get_vector();
		
		if(comprobar_colision_teniendo_tambien_radio(vec_player, 50, vec_mina, 20)){
			if(_player->puede_subir_vida_((*_consumibles)[a]->get_valor())){
				_player->modificar_vida_en((*_consumibles)[a]->get_valor());
				_consumibles_manager->borrar_consumible(a);
				--tamanio;
			}
		}
	}
}