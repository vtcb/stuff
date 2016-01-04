#include "tile.h"

Tile::Tile(
		bool walkable,
		bool eatable
	) :
		_walkable(walkable),
		_eatable(eatable)
	{
}

Tile::Tile(
			char type,
			bool eatable
		) :
			_eatable(eatable)
		{
	       if(type == '0') {
		_type = WALL;
		_walkable = false;
	} else if(type == '1') {
		_type = PASS;
		_walkable = true;
	} else if(type == 'D') {
		_type = DOOR;
		_walkable = false;
	} else {
		_type = UNKNOWN;
		_walkable = false;
	}
}

Tile& Tile::operator = (const Tile& that) {
	_walkable = that.walkable;
	_eatable  = that.eatable;
	_type     = that.type;
}

bool        Tile::eat() {
	bool ate = _eatable;
	
	_eatable = false;

	return ate;
}
