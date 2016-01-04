#include "movement.h"

const int Movement::delta[2][4] = {
	{0, 1, 0, -1},
	{1, 0, -1, 0}
};

const DIRECTION Movement::directions[4] = {
	DIRECTION::RIGHT,
	DIRECTION::DOWN,
	DIRECTION::LEFT,
	DIRECTION::UP
};

Movement::Movement(
			int i,
			int j,
			int dir,
			int speed,
			Map* map)
		:
			__i      (i),
			__j      (j),
			__dir    (dir),
			__speed  (speed),

			_i       (i),
			_j       (j),
			_dir     (dir),
			next_dir (dir),
			_speed   (speed),
			map      (map)
		{}

Movement::Movement(
			Map* map)
		:
			map      (map)
		{}

void Movement::nextPosition(int& di, int& dj) {
	di = di + delta[0][dir];
	dj = dj + delta[1][dir];

	di = (di + map->height) % map->height;
	dj = (dj + map->width ) % map->width;
}

bool Movement::changeDirection(DIRECTION new_dir) {
	return changeDirection(static_cast<int>(new_dir));
}

bool Movement::move() {
	bool moved = false;

	phase++;

	if(phase == speed) {
		phase = 0;

		changeDirection(next_dir);

		int di = i;
		int dj = j;

		nextPosition(di, dj);

		if(map->valid(di, dj)) {
			_i = di;
			_j = dj;
			moved = true;
		}
	}

	return moved;
}

void Movement::setMapReference(Map* map) {
	this->map = map;
}

void Movement::reset() {
	_i     = __i;
	_j     = __j;
	_dir   = __dir;
	_speed = __speed;
	phase  = 0;
}