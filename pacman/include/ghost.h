#ifndef GHOST_H
#define GHOST_H

#include <vector>
using std::vector;

#include <algorithm>
using std::pair;
using std::make_pair;

#include "movement.h"
#include "player.h"

#include "constant.h"

class Ghost : public Movement {
protected:
	Player* player;

	int scatter_i;
	int scatter_j;

	GHOST_MODE mode = GHOST_MODE::ATTACK;

	bool _got_pacman = false;

	char sprite;
public:
	Ghost(
		char    sprite,
		int     i,
		int     j,
		int     dir,
		int     speed,
		int     scatter_i,
		int     scatter_j,
		Map*    map    = nullptr,
		Player* player = nullptr
	);


	/* Ghost AI ans Targeting System */
	pair<int, int> getTarget();
	pair<int, int> getRandomTarget();
	virtual pair<int, int> getOwnTarget() = 0;
	bool changeDirection(int);

	void changeMode(GHOST_MODE);


	/* Game logic */
	void reset();
	void lookForPacman();


	/* Seriously, why doesn't c++ already defines this?! */
	static int sqr(int x) { return x * x; }


	void draw() const;

	const bool& got_pacman = _got_pacman;
};

#endif /* GHOST_H */
