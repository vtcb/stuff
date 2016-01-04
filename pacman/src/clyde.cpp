#include "clyde.h"

Clyde::Clyde(
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


pair<int, int> Clyde::getOwnTarget() {
	if(sqr(i - player->i) + sqr(j - player->j) > 64) {
		return pair<int, int>(
			player->i,
			player->j
		);
	} else {
		return pair<int, int>(
			scatter_i,
			scatter_j
		);
	}
}