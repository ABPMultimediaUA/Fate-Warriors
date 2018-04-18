#include "Opcion_Salir_Partida.h"

#include "../Game.h"

Opcion_Salir_Partida::Opcion_Salir_Partida(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Salir_Partida::~Opcion_Salir_Partida(){

}


Opcion* Opcion_Salir_Partida::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_input->get_saltar()){
    	Game::game_instancia()->cambio_a_update_menu();
    }
	return _this;
}