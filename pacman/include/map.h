#ifndef MAP_H
#define MAP_H

#include "debug.h"

#include "tile.h"
#include "default_map.h"

#include "constant.h"

class Map;

class Map {
private:
	int _height;
	int _width;

	Tile** map;
public:
	Map(
			int height = MAP::HEIGHT,
			int width  = MAP::WIDTH
	);
	~Map();

	bool valid(int, int);

	bool eat(int, int);

	void draw() const;

	const int& height = _height;
	const int& width  = _width;

	// Tile* operator [](int i) { return map[i]; }
};

#endif /* MAP_H */
