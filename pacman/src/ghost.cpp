#include "ghost.h"

Ghost::Ghost(
			char sprite,
			int i,
			int j,
			int dir,
			int speed,
			int scatter_i,
			int scatter_j,
			Map* map,
			Player* player
		)
		:
			Movement(
				i,
				j,
				dir,
				speed,
				map
			),
			scatter_i(scatter_i),
			scatter_j(scatter_j),
			sprite(sprite),
			player(player)
		{}

pair<int, int> Ghost::getTarget() {
	pair<int, int> target;
	switch(mode) {
		case GHOST_MODE::SCATTER:
			target = make_pair(scatter_i, scatter_j);
			break;
		case GHOST_MODE::ATTACK:
			target = getOwnTarget();
			break;
		case GHOST_MODE::FRIGHTENED:
			target = getRandomTarget();
			break;
		default: /* Should never happen */
			target = getRandomTarget();
			break;
	} 
	return target;
}

pair<int, int> Ghost::getRandomTarget() {
	return make_pair(
		(i * 2 + scatter_i * 7 + phase * 3 + player->i) % map->height,
		(j * 2 + scatter_j * 7 + phase * 3 + player->j) % map->width
	);
}

bool Ghost::changeDirection(int) {
	pair<int, int> target = getTarget();
	vector<int> directions;

	for(DIRECTION direction : Movement::directions) {
		if(dir != static_cast<int>(Movement::reverse(direction))) {
			directions.push_back( static_cast<int>(direction) );
		}
	}

	int new_dir = _dir;
	int new_dis = 0x3f3f3f3f;

	for(int cur_dir : directions) {
		swap(_dir, cur_dir);

		int di = i;
		int dj = j;

		nextPosition(di, dj);

		swap(_dir, cur_dir);

		if(map->valid(di, dj)) {
			int cur_dis = sqr(di - target.first) + sqr(dj - target.second);

			if(cur_dis < new_dis) {
				new_dis = cur_dis;
				new_dir = cur_dir;
			}
		}
	}

	bool changed = new_dir != dir;

	_dir = new_dir;

	return changed;
}

void Ghost::changeMode(GHOST_MODE new_mode) {
	if(mode != new_mode) if(mode == GHOST_MODE::SCATTER || mode == GHOST_MODE::ATTACK) {
		_dir = Movement::reverse(_dir);
	}

	mode = new_mode;
}

void Ghost::reset() {
	Movement::reset();
	// mode
	_got_pacman = false;
}

void Ghost::lookForPacman() {
	if(i == player->i && j == player->j) {
		_got_pacman = true;
	}
}
