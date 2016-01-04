#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

const double tick = 0.016;

class Timer {
private:
	timeval startTime;
	timeval pauseTime;
	double pausedTime;
	bool _paused;
public:
	Timer();

	void start();
	double time();
	void pause();
	void unpause();

	double time(const timeval& start);
	double time(const timeval& start, const timeval& end);

	const bool& paused = _paused;
};

#endif /* TIMER_H */