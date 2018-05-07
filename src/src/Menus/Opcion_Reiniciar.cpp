#include "Opcion_Reiniciar.h"

#include "../Game.h"
#include "../Tiempo/Time.h"

#include "../Motor_sonido/Interfaz_sonido.h"

Opcion_Reiniciar::Opcion_Reiniciar(Input* _i_input) : Opcion(_i_input) {

}

Opcion_Reiniciar::~Opcion_Reiniciar(){

}


Opcion* Opcion_Reiniciar::update_opcion(double _i_tiempo, Opcion* _this) {
	if(_input->get_saltar() && Time::Instance()->get_tiempo_inicio_pausa() > 250){
		_sonido->Play_menu(0);
    	Game::game_instancia()->fin_partida();
    	Game::game_instancia()->crea_partida();
    	_input->reiniciar_inputs();
    	Game::game_instancia()->cambio_a_update_partida();
    }
	return _this;
}