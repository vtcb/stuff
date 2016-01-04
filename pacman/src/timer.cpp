#include "timer.h"

Timer::Timer() {
	gettimeofday(&startTime, NULL);
	pauseTime = startTime;
	pausedTime = 0;
	_paused = true;
}

void
Timer::start() {
	gettimeofday(&startTime, NULL);
	pausedTime = 0;
	_paused = false;
}

double
Timer::time() {
	if(paused) {
		return time(startTime, pauseTime) - pausedTime;	
	} else {
		return time(startTime) - pausedTime;
	}
}

void
Timer::pause() {
	if(!paused) {
		gettimeofday(&pauseTime, NULL);
		_paused = true;
	}
}

void
Timer::unpause() {
	if(paused) {
		pausedTime += time(pauseTime);
		_paused = false;
	}
}

double
Timer::time(const timeval& start) {
	timeval endTime;
	long seconds, useconds;
	double duration;

	gettimeofday(&endTime, NULL);

	seconds  = endTime.tv_sec  - start.tv_sec;
	useconds = endTime.tv_usec - start.tv_usec;

	duration = seconds + useconds/1000000.0;

	return duration;
}

double 
Timer::time(const timeval& start, const timeval& end) {
	long seconds, useconds;
	double duration;

	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;

	duration = seconds + useconds/1000000.0;

	return duration;
}