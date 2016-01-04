#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
using std::swap;

#include "debug.h"

#include "movement.h"

#include "map.h"
#include "tile.h"

#include "constant.h"

class Player;

class Player : public Movement {
private:
	int _score;
	int _lives;
	
	bool changeDirection(int);
public:
	Player(
		Map* map    = nullptr,
		int  i      = PACMAN::I,
		int  j      = PACMAN::J,
		int  dir    = static_cast<int>(DIRECTION::LEFT),
		int  speed  = PACMAN::SPEED,
		int  lives  = PACMAN::LIVES
	);
	
	using Movement::changeDirection;

	bool eat();

	void die();

	void draw() const;
	void draw(char [100][100]) const;

	const int& score    = _score;
	const int& lives    = _lives;
};

#endif /* PLAYER_H */
