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
#include "../Interfaz_Libs/Lib_Math.h"



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

  	Character** npc =  Game::game_instancia()->game_get_datos()->get_characters();
	uint16_t numnpc = Game::game_instancia()->game_get_datos()->get_num_characters();
	bool se_ha_borrado = false;
	

	for(short a=0; a<tamanio; a++){
		
		for (short i=0; i<numnpc && !se_ha_borrado; i++){
			update_lod((*_consumibles)[a]);
			if(npc[i]->get_vida_actual()>0 && (*_consumibles)[a]->usar(npc[i])){
				Vector2 pos((*_consumibles)[a]->getX(), (*_consumibles)[a]->getZ());
				_consumibles_manager->borrar_consumible(a);
				--tamanio;
				se_ha_borrado=true;
			}
			
		}
		se_ha_borrado=false;
	}

	_consumibles_manager->crear_todos_consumibles_que_faltan();

}


bool Consumible_Action::update_lod(Consumible* _consumible){

	bool _esta_lejos;
	Player* _player = Game::game_instancia()->game_get_datos()->get_player();

	if (lib_math_distancia_2_puntos(_player->getX(), _player->getZ(), _consumible->getX(), _consumible->getZ()) > 150){
		_esta_lejos = true;
	}

	else {
		_esta_lejos = false;
	}

	if(_consumible->get_esta_lejos() != _esta_lejos){
		_consumible->cambiar_modelado();
	}

	return _esta_lejos;
}


void Consumible_Action::borrar_power_up(Consumible_Power_Up* _i_power_up){
	_consumibles_manager->borrar_consumible(_i_power_up);
}
