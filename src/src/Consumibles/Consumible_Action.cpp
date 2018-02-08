#include "Consumible_Action.h"

#include "../Tiempo/Time.h"
#include "Consumible_Carne.h"
#include "Consumible_Patata.h"
#include "../Game.h"
#include "../Datos_Partida.h"
#include "Consumible_Manager.h"
#include "../Personajes/Player.h"
#include "../Personajes/NPC.h"
#include "../Personajes/NPC_Manager.h"

#include "../Utilidades/Vector.h"


Consumible_Action::Consumible_Action() : _player(nullptr), _consumibles_manager(nullptr){
	Game* punterito 		= Game::game_instancia();
	Datos_Partida * datitos	= punterito->game_get_datos();

	_npc_manager = datitos->get_npc_manager();

	_player 				= datitos->get_player();
	_consumibles_manager 	= datitos->get_Consumible_Manager();
	_consumibles 			= _consumibles_manager->get_consumibles();
}

Consumible_Action::~Consumible_Action(){
	_consumibles_manager 	= nullptr;
	_player					= nullptr;
}

void Consumible_Action::comprobar_consumibles(){

	short tamanio =(*_consumibles).size();

  	NPC** npc = _npc_manager->get_npcs();
	uint16_t numnpc = _npc_manager->get_n_enemigos();
	bool se_ha_borrado = false;
	
	for(short a=0; a<tamanio; a++){

		if((*_consumibles)[a]->usar(_player)){
			//(*_consumibles)[a]->setPositionXZ(9000,9000);
			_consumibles_manager->borrar_consumible(a);
			--tamanio;
			std::cout << tamanio<< "tamaaaaño" <<std::endl;
			continue;
		}

		for (short i=0; i<numnpc && !se_ha_borrado; i++){
          //NPC
			if((*_consumibles)[a]->usar(npc[i])){
				//(*_consumibles)[a]->setPositionXZ(9000,9000);
				_consumibles_manager->borrar_consumible(a);
				--tamanio;
				std::cout << tamanio<< "tamaaaaño" <<std::endl;
				se_ha_borrado=true;
			}
		 }
		se_ha_borrado=false;
	}

		
	}


void Consumible_Action::borrar_power_up(Consumible_Power_Up* _i_power_up){
	_consumibles_manager->borrar_consumible(_i_power_up);
}