#ifndef CLYDE_H
#define CLYDE_H

#include "ghost.h"

#include "constant.h"

class Clyde : public Ghost {
public:
	Clyde(
		Map*    map       = nullptr,
		Player* player    = nullptr,
		char    sprite    = 'C',
		int     i         = GHOST::CLYDE::I,
		int     j         = GHOST::CLYDE::J,
		int     dir       = 0,
		int     speed     = GHOST::SPEED,
		int     scatter_i = GHOST::CLYDE::SI,
		int     scatter_j = GHOST::CLYDE::SJ
	);

	pair<int, int> getOwnTarget();
};

#endif /* CLYDE_H */