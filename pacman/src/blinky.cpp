#include "blinky.h"

Blinky::Blinky(
			Map*    map,
			Player* player,
			char    sprite,
			int     i,
			int     j,
			int     dir,
			int     speed,
			int     scatter_i,
			int     scatter_j
		)
		:
			Ghost(
				sprite,
				i,
				j,
				dir,
				speed,
				scatter_i,
				scatter_j,
				map,
				player
			)
		{}

pair<int, int> Blinky::getOwnTarget() {
	return pair<int, int>(player->i, player->j);
}