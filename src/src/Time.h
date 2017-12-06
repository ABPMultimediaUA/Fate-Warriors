#ifndef TIME_H_
#define TIME_H_
#include <iostream>
#include <ctime>
#include <cstdlib>

class Time {
public:
	
	~Time();
	double get_start();
	double get_current();
	double getDeltaTime(double _i_ahora,double _i_antes);
	static Time* Instance();

private:
	static Time* instancia;
	Time();

	clock_t _startTime; //Start timer


};

#endif /* TIME_H_ */
