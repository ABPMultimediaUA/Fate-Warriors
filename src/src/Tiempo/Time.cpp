#include "Time.h"
#include "SFML/Graphics.hpp"

Time* Time::instancia=0;

Time* Time::Instance(){
	if(instancia==0){
	instancia= new Time();
	}
	return instancia;
}

Time::Time() {
  _reloj = new sf::Clock();
  _startTime = _reloj->getElapsedTime().asMilliseconds();
}

Time::~Time() {
	if(_reloj!=nullptr)
		delete _reloj;
}


double Time::getDeltaTime(double _i_ahora, double _i_antes){
	return((_i_ahora-_i_antes));
}

double Time::get_start(){
    return _startTime;
}

double Time::get_current(){
    return _reloj->getElapsedTime().asMilliseconds();

}

void Time::set_tiempo_desde_ultimo_update(double _last){
	_tiempo_desde_ultimo_update = _last;
}

double Time::get_tiempo_desde_ultimo_update(){
	return _tiempo_desde_ultimo_update;
}

double Time::get_tiempo_desde_ultimo_update_segundos(){
	return _tiempo_desde_ultimo_update/1000;
}