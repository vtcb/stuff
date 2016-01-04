#ifndef VTCB_TIMER_H
#define VTCB_TIMER_H

#include <cstdlib>     /* NULL */
#include <sys/time.h>  /* timeval, gettimeofday */

class Timer {
private:
	timeval startTime;
	timeval pauseTime;
	double  pausedTime;
	bool    _paused;

	double  time        (const timeval& start);
	double  time        (const timeval& start, const timeval& end);
public:
	        Timer       ();

	void    start       ();
	double  time        ();
	void    pause       ();
	void    unpause     ();

	void    reduce      (double);

	bool    paused      ();
};

#endif /* VTCB_TIMER_H */
