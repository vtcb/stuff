#ifndef TILE_H
#define TILE_H

#include "debug.h"

enum TILE_TYPE {
	PASS     = 1,
	WALL     = 2,
	DOOR     = 3,

	UNKNOWN  = 4
};

class Tile;

class Tile {
private:
	bool _walkable;
	bool _eatable;

	int _type;
public:
	// Tile(const Tile& t) : Tile(t) {}
	Tile(
		bool walkable    = true,
		bool eatable     = false
	);

	Tile(
		char type,
		bool eatable     = false
	);

	Tile& operator = (const Tile&);

	const int & type     = _type;
	const bool& walkable = _walkable;
	const bool& eatable  = _eatable;


	bool eat();

	char draw() const;
};

#endif /* TILE_H */
