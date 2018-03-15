#include "Opcion_Jugar_Online.h"

#include "../Game.h"

Opcion_Jugar_Online::Opcion_Jugar_Online(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Jugar_Online::~Opcion_Jugar_Online(){

}


Opcion* Opcion_Jugar_Online::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_input->get_saltar()){
    	Game::game_instancia()->crea_partida();
    	Game::game_instancia()->cambio_a_update_online();
    }
	return _this;
}