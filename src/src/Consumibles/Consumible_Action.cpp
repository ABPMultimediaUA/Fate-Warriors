#include "Consumible_Action.h"

#include "../Tiempo/Time.h"
#include "Consumible_Carne.h"
#include "Consumible_Patata.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "Consumible_Manager.h"
#include "../Personajes/Player.h"
#include "../Personajes/NPC.h"

#include "../Utilidades/Vector.h"


Consumible_Action::Consumible_Action() : _consumibles_manager(nullptr){
	Game* punterito 		= Game::game_instancia();
	Datos_Partida * datos	= punterito->game_get_datos();
	_consumibles_manager 	= datos->get_Consumible_Manager();
	_consumibles 			= _consumibles_manager->get_consumibles();
}

Consumible_Action::~Consumible_Action(){
	_consumibles_manager 	= nullptr;
}

void Consumible_Action::comprobar_consumibles(){

	short tamanio =(*_consumibles).size();
	Player* _jugador =  Game::game_instancia()->game_get_datos()->get_player();
	
	for(short a=0; a<tamanio; a++){
		if(_jugador->get_vida_actual()>0 && (*_consumibles)[a]->usar(_jugador)){
			_consumibles_manager->borrar_consumible(a);
			--tamanio;
		}
	}
}
