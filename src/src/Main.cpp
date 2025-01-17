#include "Game.h"
#include "Interfaz/Motor.h"
#include "Tiempo/Time.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

const float t_min_IA=(1000/15);


// Función que da el nº de fps en el ultimo segundo
void _imprime_fps(Time* _time, uint8_t& _frames, uint32_t _tiempo_por_frame, uint32_t& _iteraciones) {
	_frames++;
	_tiempo_por_frame = _time->get_current_sin_pausas() - _iteraciones*1000;
	if(_tiempo_por_frame>=1000) {
		_tiempo_por_frame-=1000;

		std::clog << (int)_frames << " fps\n";

		_frames=0;
		_iteraciones++;
	}
}


// Main del juego
int main(){
	srand((int)time(0)); // Inicia la semilla del rand

	Game* _juego = Game::game_instancia();
	Time* time=Time::Instance();

	double _h_ultimo_update=time->get_current_sin_pausas();
	double _interpolacion;
	Time* _time = Time::Instance();

    Motor* _motor = Motor::Motor_GetInstance();
	
	_motor->crearLuz(true, 100, Vector3(0.1, 0.1, 0.1), Vector3(1, 1, 1), Vector3(0.1, 0.1, 0.1), 2000, 20, -500);
	

    //uint8_t _frames = 0;
    //uint32_t _tiempo_por_frame = 0, _iteraciones = 0;

	while(_motor->ventana_abierta()){
		//Evento para cerrar la ventana

		// Recoge inputs
		_juego->recibir_inputs();

		time->set_tiempo_desde_ultimo_update(time->get_current_sin_pausas() - _h_ultimo_update);//actualizacion del reloj
		//std::cout << "Tiempo desde update " << time->get_tiempo_desde_ultimo_update() << std::endl;
		//update
                
		if(time->get_tiempo_desde_ultimo_update()>t_min_IA){
			_h_ultimo_update=time->get_current_sin_pausas();
            //std::cout << "pre update" << std::endl;
            //std::cout << "Tiempo update " << time->get_tiempo_desde_ultimo_update() << "\n";
            _juego->update(time->get_tiempo_desde_ultimo_update());
            time->set_tiempo_desde_ultimo_update(time->get_current_sin_pausas() - _h_ultimo_update);
            //std::cout << "post update" << std::endl;
		}


		//Render
		_interpolacion=fmin(1.f,(double)time->get_tiempo_desde_ultimo_update()/t_min_IA);
		_juego->render(_interpolacion);
		
		//_imprime_fps(_time, _frames, _tiempo_por_frame, _iteraciones);

		//std::cout << "Interpolaicon " << _interpolacion	 << std::endl;
		//_time->cambiar_antes_a_ahora();
	}

	delete _time;

	delete _juego;

	return 0;
}
