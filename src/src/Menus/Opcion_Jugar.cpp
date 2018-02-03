#include "Opcion_Jugar.h"

#include "../Game.h"

Opcion_Jugar::Opcion_Jugar(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Jugar::~Opcion_Jugar(){

}


Opcion* Opcion_Jugar::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_input->get_saltar()){
    	Game::game_instancia()->crea_partida();
    	Game::game_instancia()->cambio_a_update_partida();
    }
	return _this;
}