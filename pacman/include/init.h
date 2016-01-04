#ifndef INIT_H
#define INIT_H

#include <cstdlib>

#include "ncurses.h"

inline void init() {
	/* ncurses */
	initscr();
	
	/* ncurses colors */
	/*
	if(has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	*/
	
	/* ncurses input */
	curs_set(FALSE);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

inline void deinit() {
	endwin();
}

#endif /* INIT_H */