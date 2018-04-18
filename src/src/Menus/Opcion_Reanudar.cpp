#include "Opcion_Reanudar.h"

#include "../Game.h"
#include "../Tiempo/Time.h"

Opcion_Reanudar::Opcion_Reanudar(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Reanudar::~Opcion_Reanudar(){

}


Opcion* Opcion_Reanudar::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_input->get_saltar() && Time::Instance()->get_tiempo_inicio_pausa() > 250){
    	Game::game_instancia()->cambio_a_update_partida();
    	_input->quita_saltar();
    }
	return _this;
}