#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

	#include <iostream>
	#define dbg(x) std::cerr << ">>> " << x << std::endl;
	#define _ << ", " <<

	#include <curses.h>

	#define debug printw

#else
	#define debug if(false) printw

#endif /* DEBUG */

#endif /* DEBUG_H */