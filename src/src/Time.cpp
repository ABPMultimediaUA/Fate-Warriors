#include "Time.h"

Time* Time::instancia=0;

Time* Time::Instance(){
	if(instancia==0){
	instancia= new Time();
	}
	return instancia;
}

Time::Time() {
	_startTime = clock();
}

Time::~Time() {
}


double Time::getDeltaTime(double _i_ahora, double _i_antes){
	return((_i_ahora-_i_antes)/1000);
}

double Time::get_start(){
	return _startTime;
}

double Time::get_current(){
	return clock();
}