#ifndef TIME_H_
#define TIME_H_
#include <iostream>
#include <cstdlib>
#include "SFML/Graphics.hpp"

class Time {
public:
	static Time* Instance();
	~Time();

	double get_current();
	double get_current_sin_pausas();

	double getDeltaTime(double _i_ahora, double _i_antes);

	void set_tiempo_desde_ultimo_update(double _set_value);
	double get_tiempo_desde_ultimo_update();
	double get_tiempo_desde_ultimo_update_segundos();

	void pausar_reloj();
	void reanudar_reloj();
	inline double get_tiempo_inicio_pausa() { return _reloj->getElapsedTime().asMilliseconds() - _tiempo_inicio_pausa.asMilliseconds();}

	inline bool get_esta_pausado() { return _esta_pausado;}

private:
	Time();
	static Time* instancia;

	sf::Clock *_reloj;				// Reloj del tiempo total
	sf::Time _tiempo_pausa;			// Tiempo pasado en pausa
	sf::Time _tiempo_inicio_pausa; 	//Tiempo que se inicia la pausa

	double _tiempo_desde_ultimo_update;

	bool _esta_pausado;


};

#endif /* TIME_H_ */
