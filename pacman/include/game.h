#ifndef GAME_H
#define GAME_H

#include <vector>
using std::vector;

#include "timer.h"
#include "map.h"

#include "movement.h"
#include "player.h"
#include "ghost.h"

#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"

#include "draw.h"

class Game {
public:
	void play();
};

#endif /* GAME_H */