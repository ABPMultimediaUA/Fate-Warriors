#include "Interactuable_Action.h"
#include "Trampas/Pinchos.h"
#include "Tiempo/Time.h"
#include "Game.h"
#include "Datos_Partida.h"
#include "Interactuable_Manager.h"
#include "Interruptor.h"

Interactuable_Action::Interactuable_Action(){
	Game* punterito = Game::game_instancia();
	Datos_Partida * datitos = punterito->game_get_datos();

	_interactuable_manager = datitos->get_interactuable_manager();
}

Interactuable_Action::~Interactuable_Action() {

}

void Interactuable_Action::update(){
	Interruptor** _interruptor = _interactuable_manager->get_interruptores();
	unsigned short n_interruptores = _interactuable_manager->get_n_interruptores();

	for(unsigned short cont=0; cont<n_interruptores; cont++){
		_interruptor[cont]->update();
	}
}

