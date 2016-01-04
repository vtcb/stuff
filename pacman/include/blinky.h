#ifndef BLINKY_H
#define BLINKY_H

#include "ghost.h"

#include "constant.h"

class Blinky : public Ghost {
public:
	Blinky(
		Map*    map       = nullptr,
		Player* player    = nullptr,
		char    sprite    = 'B',
		int     i         = GHOST::BLINKY::I,
		int     j         = GHOST::BLINKY::J,
		int     dir       = 0,
		int     speed     = GHOST::SPEED,
		int     scatter_i = GHOST::BLINKY::SI,
		int     scatter_j = GHOST::BLINKY::SJ
	);

	pair<int, int> getOwnTarget();
};

#endif /* BLINKY_H */