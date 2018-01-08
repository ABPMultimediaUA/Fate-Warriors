#include "Consumible_Action.h"

#include "../Tiempo/Time.h"
#include "Consumible_Carne.h"
#include "Consumible_Patata.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "Consumible_Manager.h"
#include "../Personajes/Player.h"
#include "../Utilidades/Vector.h"

Consumible_Action::Consumible_Action() : _player(nullptr), _consumibles_manager(nullptr){
	Game* punterito 		= Game::game_instancia();
	Datos_Partida * datitos	= punterito->game_get_datos();

	_player 				= datitos->get_player();
	_consumibles_manager 	= datitos->get_Consumible_Manager();
	_consumibles 			= _consumibles_manager->get_consumibles();
}

Consumible_Action::~Consumible_Action(){
	_consumibles_manager 	= nullptr;
	_player					= nullptr;
}

void Consumible_Action::comprobar_consumibles(){

	Vector2 vec_player	= _player->get_vector();
	short tamanio =(*_consumibles).size();
	
	for(short a=0; a<tamanio; a++){
		Vector2 vec_mina	= (*_consumibles)[a]->get_vector();
		
		if(comprobar_colision_teniendo_tambien_radio(vec_player, 2, vec_mina, 2)){
			if(_player->puede_subir_vida_((*_consumibles)[a]->get_valor())){
				_player->modificar_vida_en((*_consumibles)[a]->get_valor());
				(*_consumibles)[a]->setPositionXZ(9000,9000);
				_consumibles_manager->borrar_consumible(a);
				--tamanio;
			}
		}
	}
}