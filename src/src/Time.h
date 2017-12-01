#ifndef TIME_H_
#define TIME_H_
#include <iostream>
#include <ctime>
#include <cstdlib>

class Time {
public:
	Time();
	~Time();
	bool count_down();
	void set_count_down(const short _i_countDown);
	void set_start_time();
	short get_elapsed_time_btw_last_start_time();

private:
	time_t _frist;
	clock_t _startTime; //Start timer
	short _countDownValue;

};

#endif /* TIME_H_ */
