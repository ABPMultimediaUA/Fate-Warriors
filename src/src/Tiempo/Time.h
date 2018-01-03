#ifndef TIME_H_
#define TIME_H_
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

class Time {
public:
	
	~Time();
	double get_start();
	double get_current();
	double getDeltaTime(double _i_ahora, double _i_antes);
	static Time* Instance();
	void set_tiempo_desde_ultimo_update(double _set_value);
	double get_tiempo_desde_ultimo_update();
	double get_tiempo_desde_ultimo_update_segundos();


private:
	static Time* instancia;
	Time();
	sf::Clock *_reloj;
	double _startTime; //Start timer
	double _tiempo_desde_ultimo_update;


};

#endif /* TIME_H_ */
