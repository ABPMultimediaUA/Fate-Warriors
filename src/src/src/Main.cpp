#include "Game.h"
#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Tiempo/Time.h"
#include <iostream>
//#include <btBulletDynamicsCommon.h>

const float t_min_IA=(1000/15);

int main(){

	Game* _juego = Game::game_instancia();
	_juego->crea_partida();
	Time* time=Time::Instance();
	//double _tiempo_desde_ultimo_update=time->get_current();
	double _h_ultimo_update=time->get_current();
	double _interpolacion;
	//_juego->crea_partida();

	Time* _time = Time::Instance();

	Interfaz* _interface = Interfaz::Interfaz_getInstance(); //moose ninja || 1280 width || 720 height
        
	//_time->updateAntes();
	while(_interface->Interfaz_getDevice()->run()){
		//evento para cerrar la ventana

		time->set_tiempo_desde_ultimo_update(time->get_current() - _h_ultimo_update);//actualizacion del reloj
		//std::cout << "Tiempo desde update " << time->get_tiempo_desde_ultimo_update() << std::endl;
		//update
                
		if(time->get_tiempo_desde_ultimo_update()>t_min_IA){
			_h_ultimo_update=time->get_current();
                        //std::cout << "pre update" << std::endl;
                        _juego->update(time->get_tiempo_desde_ultimo_update());
                        //std::cout << "post update" << std::endl;
		}

		//render
		_interpolacion=fmin(1.f,(double)time->get_tiempo_desde_ultimo_update()/t_min_IA);
		_juego->render(_interpolacion);
		//std::cout << "Interpolaicon " << _interpolacion	 << std::endl;
		//_time->cambiar_antes_a_ahora();
	}

	_juego->fin_partida();

	delete _time;

	delete _juego;
	
	return 0;

}
