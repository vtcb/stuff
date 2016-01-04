#ifndef DRAW_H
#define DRAW_H

/* Draw stuff using ncurses */

#include <vector>
using std::vector;

#include "ncurses.h"

#include "debug.h"

#include "tile.h"
#include "map.h"
#include "player.h"
#include "ghost.h"

class Draw {
private:
	int height;
	int width;
	static char buffer[100][100];
public:
	Draw(int height, int width) : height(height), width(width) {} 
	// void draw(const Player& player);
	// void draw(const Player& player, const Map& map, vector<Ghost*>);

	void put();

	friend class Map;
	friend class Player;
	friend class Ghost;
};

#endif /* DRAW_H */