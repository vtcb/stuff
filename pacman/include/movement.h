#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "map.h"
#include "constant.h"

class Movement {
protected:
	int __i;
	int __j;
	int __dir;
	int __speed;
	
	int _i;
	int _j;
	int _dir;

	int next_dir;

	int _speed;

	int phase = 0;

	Map* map;

	static const int delta[2][4];
	static const DIRECTION directions[4];

	virtual bool changeDirection(int) = 0;
public:
	Movement(int, int, int, int, Map* = nullptr);
	Movement(Map*);

	void setMapReference(Map*);

	bool changeDirection(DIRECTION new_dir);
	void nextPosition(int&, int&);
	bool move();

	void reset();

	const int& i        = _i;
	const int& j        = _j;
	const int& dir      = _dir;
	const int& speed    = _speed;

	static DIRECTION reverse(DIRECTION dir) {
		DIRECTION reversed = dir;
		
		switch(dir) {
			case DIRECTION::RIGHT:
				reversed = DIRECTION::LEFT;
				break;
			case DIRECTION::UP:
				reversed = DIRECTION::DOWN;
				break;
			case DIRECTION::LEFT:
				reversed = DIRECTION::RIGHT;
				break;
			case DIRECTION::DOWN:
				reversed = DIRECTION::UP;
				break;
		}

		return reversed;
	}

	static int reverse(int dir) {
		return static_cast<int>( reverse(static_cast<DIRECTION>(dir) ) );
	}
};

#endif /* MOVEMENT_H */