#include "Game.h"
#include "Interfaz/Interfaz.h"
#include "Personajes/Player.h"
#include "Tiempo/Time.h"
#include <iostream>

void pruebas_basura(){

	Vector2 a = Vector2(1,1);
	Vector2 b = Vector2(0,8);
	short ba = 6;
	Vector2 d = a+ba;
	
	std::cout << "Prueba de suma de valores: ";

	std::cout << "suma de los vectores es " << d._x << std::endl;
	float distance = Vector2DistanceSq(a, b);

	std::cout << distance << std::endl;
	
	Vector2 sumaVectores  = a+b;
	std::cout << a._x << "Valor de la x" << a._y << "valor de la y" << std::endl;
	std::cout << sumaVectores._x << "Valor de la x" << sumaVectores._y << "valor de la y" << std::endl;
}



const float t_min_IA=(1000/15);
int main(){

	pruebas_basura();

	Game* _juego = Game::game_instancia();

	Time* time=Time::Instance();
	//double _tiempo_desde_ultimo_update=time->get_current();
	double _h_ultimo_update=time->get_current();
	double _interpolacion;

	_juego->crea_partida();

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
			_juego->update(time->get_tiempo_desde_ultimo_update());
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
