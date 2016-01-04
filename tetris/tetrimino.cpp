#include "tetrimino.h"

Tetrimino::Tetrimino(
			int n,
			const char map[5][5],
			int color,
			char type,
			bool heavy,
			int blast
		) 
		:
			n(n),
			color(color),
			type(type),
			heavy(heavy),
			blast(blast)
		{
		
	this->map.assign(n, vector<bool>(n));
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			this->map[i][j] = map[i][j] == '1';
		}
	}
}

const int  In = 4;
const char Ic[5][5] = {
	"0000",
	"1111",
	"0000",
	"0000"
};

const int  Jn = 3;
const char Jc[5][5] = {
	"100",
	"111",
	"000"
};

const int  Ln = 3;
const char Lc[5][5] = {
	"001",
	"111",
	"000"
};

const int  On = 2;
const char Oc[5][5] = {
	"11",
	"11"
};

const int  Sn = 3;
const char Sc[5][5] = {
	"011",
	"110",
	"000"
};

const int  Tn = 3;
const char Tc[5][5] = {
	"010",
	"111",
	"000"
};

const int  Zn = 3;
const char Zc[5][5] = {
	"110",
	"011",
	"000"
};

const int Hn = 1;
const char Hc[5][5] = {
	"1"
};

const int Bn = 1;
const char Bc[5][5] = {
	"1"
};

const Tetrimino
	/* Basic */
	I(In, Ic, 1, 'I'),
	J(Jn, Jc, 2, 'J'),
	L(Ln, Lc, 3, 'L'),
	O(On, Oc, 4, 'O'),
	S(Sn, Sc, 5, 'S'),
	T(Tn, Tc, 6, 'T'),
	Z(Zn, Zc, 7, 'Z'),

	/* Special */
	H(Hn, Hc, 8, 'H', true),     /* Heavy */
	B(Bn, Bc, 9, 'B', false, 1)  /* Bomb  */
;

Tetrimino::Tetrimino(char type) {
	switch(type) {
		case 'I':
			*this = I;
			break;
		case 'J':
			*this = J;
			break;
		case 'L':
			*this = L;
			break;
		case 'O':
			*this = O;
			break;
		case 'S':
			*this = S;
			break;
		case 'T':
			*this = T;
			break;
		case 'Z':
			*this = Z;
			break;
		case 'H':
			*this = H;
			break;
		case 'B':
			*this = B;
			break;
	}
}

void Tetrimino::rotate() {
	vector< vector<bool> > old = map;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			map[j][n-1-i] = old[i][j];
		}
	}
}

void Tetrimino::rotate_back() {
	vector< vector<bool> > old = map;
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			map[n-1-j][i] = old[i][j];
		}
	}
}