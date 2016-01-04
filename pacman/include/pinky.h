#ifndef PINKY_H
#define PINKY_H

#include "ghost.h"

#include "constant.h"

class Pinky : public Ghost {
public:
	Pinky(
		Map*    map       = nullptr,
		Player* player    = nullptr,
		char    sprite    = 'P',
		int     i         = GHOST::PINKY::I,
		int     j         = GHOST::PINKY::J,
		int     dir       = 0,
		int     speed     = GHOST::SPEED,
		int     scatter_i = GHOST::PINKY::SI,
		int     scatter_j = GHOST::PINKY::SJ
	);

	pair<int, int> getOwnTarget();
};

#endif /* PINKY_H */