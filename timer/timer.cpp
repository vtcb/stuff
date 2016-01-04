#include "timer.h"

Timer::Timer() {
	gettimeofday(&startTime, NULL);
	pauseTime = startTime;
	pausedTime = 0;
	_paused = true;
}

void    Timer::start() {
	gettimeofday(&startTime, NULL);
	pausedTime = 0;
	_paused = false;
}

double  Timer::time() {
	if(_paused) {
		return time(startTime, pauseTime) - pausedTime;	
	} else {
		return time(startTime) - pausedTime;
	}
}

void    Timer::pause() {
	if(!_paused) {
		gettimeofday(&pauseTime, NULL);
		_paused = true;
	}
}

void    Timer::unpause() {
	if(_paused) {
		pausedTime += time(pauseTime);
		_paused = false;
	}
}

void    Timer::reduce(double reducing) {
	pausedTime += reducing;
}

bool    Timer::paused() {
	return _paused;
}

double  Timer::time(const timeval& start) {
	timeval end;
	gettimeofday(&end, NULL);

	return time(start, end);
}

double  Timer::time(const timeval& start, const timeval& end) {
	long seconds, useconds;
	double duration;

	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;

	duration = seconds + useconds/1000000.0;

	return duration;
}
