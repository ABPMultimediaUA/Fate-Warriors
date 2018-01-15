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
		
		if((*_consumibles)[a]->usar(_player)){
				(*_consumibles)[a]->setPositionXZ(9000,9000);
				_consumibles_manager->borrar_consumible(a);
				--tamanio;
			}
		}
	}
