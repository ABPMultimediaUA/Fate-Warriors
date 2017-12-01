#include "Time.h"

Time::Time() {
	_startTime = clock();
	_countDownValue = 20;
	_frist = 0;
	time(&_frist);
}

Time::~Time() {
}

void Time::set_start_time(){
	_startTime = clock();
}

// GET ELAPSED TIME IN CICLES OF COMPUTER GET TIME ELAPSED BTW START -- DONT FORGET CALL SET START TIME --
short Time::get_elapsed_time_btw_last_start_time(){
	return (clock()-_startTime)/(short)CLOCKS_PER_SEC;
}


void Time::set_count_down(const short _i_countDown){
	time(&_frist);
	_countDownValue = _i_countDown;
}

// USE COUTNDOWN AND set_count_down TO INITIALIZE
bool Time::count_down(){
	//time_t timer;
	//time(&timer);  /* get current time; same as: timer = time(NULL)  */

	short seconds = difftime(time(NULL), _frist);

	if(seconds-_countDownValue==0){										//Final countdown??
		return true;
	}
	else{
		return false;
	}
}
