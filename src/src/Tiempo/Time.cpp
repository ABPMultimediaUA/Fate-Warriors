#include "Time.h"

Time* Time::instancia=0;

Time* Time::Instance(){
	if(instancia==0){
		instancia = new Time();
	}
	return instancia;
}

Time::Time() {
  _reloj = new sf::Clock();
  _tiempo_pausa = sf::seconds(0);
  _esta_pausado = false;
}

Time::~Time() {
	if(_reloj!=nullptr)
		delete _reloj;
}


double Time::getDeltaTime(double _i_ahora, double _i_antes){
	return (_i_ahora-_i_antes);
}

double Time::get_current(){
    return _reloj->getElapsedTime().asMilliseconds() - _tiempo_pausa.asMilliseconds();
}

double Time::get_current_sin_pausas(){
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

void Time::pausar_reloj() {
	//std::cout << "Se pone pausa\n";
  	_esta_pausado = true;
	_tiempo_inicio_pausa = sf::milliseconds(_reloj->getElapsedTime().asMilliseconds());
}

void Time::reanudar_reloj() {
  	_esta_pausado = false;
	_tiempo_inicio_pausa = sf::milliseconds(_reloj->getElapsedTime().asMilliseconds() - _tiempo_inicio_pausa.asMilliseconds());
	_tiempo_pausa += _tiempo_inicio_pausa;
	_tiempo_inicio_pausa = sf::milliseconds(_reloj->getElapsedTime().asMilliseconds());
}