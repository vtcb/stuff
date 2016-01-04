#include "inky.h"

Inky::Inky(
			Map*    map,
			Player* player,
			Blinky* blinky,
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
			),
			blinky(blinky)
		{}


pair<int, int> Inky::getOwnTarget() {
	int di = player->i + 2 * delta[0][player->dir];
	int dj = player->j + 2 * delta[1][player->dir];

	return pair<int, int>(
		2 * di - blinky->i,
		2 * dj - blinky->j
	);
}