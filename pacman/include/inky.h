#ifndef INKY_H
#define INKY_H

#include "ghost.h"
#include "blinky.h"

#include "constant.h"

class Inky : public Ghost {
private:
	Blinky* blinky;
public:
	Inky(
		Map*    map       = nullptr,
		Player* player    = nullptr,
		Blinky* blinky    = nullptr,
		char    sprite    = 'I',
		int     i         = GHOST::INKY::I,
		int     j         = GHOST::INKY::J,
		int     dir       = 0,
		int     speed     = GHOST::SPEED,
		int     scatter_i = GHOST::INKY::SI,
		int     scatter_j = GHOST::INKY::SJ
	);

	pair<int, int> getOwnTarget();
};

#endif /* INKY_H */