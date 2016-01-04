#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <vector>

using std::vector;

class Tetrimino {
public:
	int n;
	vector< vector<bool> > map;
	int color;
	char type;
	bool heavy;
	int blast;
	Tetrimino(
				int n,
				const char map[5][5],
				int color,
				char type,
				bool heavy = false,
				int blast = 0
			);
	
	Tetrimino(char type);
	
	void rotate();
	
	void rotate_back();
};

#endif // TETRIMINO_H
