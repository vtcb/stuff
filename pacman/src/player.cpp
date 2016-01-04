#include "player.h"

Player::Player(
			Map* map,
			int i,
			int j,
			int dir,
			int speed,
			int lives
		)
		:
			Movement(
				i,
				j,
				dir,
				speed,
				map
			),
			_score(0),
			_lives(lives)
		{}

bool Player::changeDirection(int new_dir) {
	bool changed = false;

	int last = next_dir;

	next_dir = new_dir;

	swap(_dir, next_dir);

	int di = i;
	int dj = j;

	nextPosition(di, dj);

	swap(_dir, next_dir);

	if(map->valid(di, dj)) {
		_dir = next_dir;
		changed = true;
	} else {
		changed = false;
	}

	return changed;
}


bool Player::eat() {
	bool ate = map->eat(i, j);

	if(ate) {
		_score += SCORE::BASIC;
		phase -= PACMAN::DIGESTION;
	}
	return ate;			
}

void Player::die() {
	_lives--;
}