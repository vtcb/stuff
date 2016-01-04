#include "pinky.h"

Pinky::Pinky(
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


pair<int, int> Pinky::getOwnTarget() {

	return pair<int, int>(
		player->i + 4 * delta[0][player->dir],
		player->j + 4 * delta[1][player->dir]
	);
}