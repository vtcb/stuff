#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include <ctime>
#include <cstdlib>

#include <ncurses.h>

#include "tetrimino.h"

#define dbg(x) cerr << x << endl;
#define _ << ", " <<

using namespace std;

#define fr(a, b, c) for(int a = b; a < c; a++)

typedef vector< vector<int> > Matrix;

#define WIDTH  10
#define HEIGHT 22
#define HIDDEN 0

class Tetris {
private:
	int height;
	int width;
	int hidden;
	Matrix map;
	
	struct Piece {
		int i;
		int j;
		Tetrimino* t = NULL;
		
		const Piece& operator = (const Piece& p) {
			i = p.i;
			j = p.j;
			t = new Tetrimino(*p.t);
		}
	} current, next, ghost;

public:
	bool ghost_enabled;
	int points;
	bool gameover;

	Tetris(
				int height = WIDTH,
				int width  = HEIGHT,
				int hidden = HIDDEN)
			:
				height(height),
				width(width),
				hidden(hidden),
				map(height, vector<int>(width, 0)),
				
				ghost_enabled(true),
				
				points(0),
				gameover(false)
			{
		generatePiece();
		getNextPiece();
	}
	
	void getNextPiece() {
		if(current.t != NULL) delete current.t;
		
		current.t = next.t;
		current.i = 0;
		current.j = width/2 - (current.t->n+1)/2;
		
		if(!check()) {
			gameover = true;
		}
		
		generatePiece();
	}
	
	void generatePiece() {
		static char arr[] = "IJLOSTZ";
		int type_chance = rand()%100;
		if(type_chance < 0) {
			next.t = new Tetrimino('H');
		} else if(type_chance < 0) {
			next.t = new Tetrimino('B');
		} else {
			next.t = new Tetrimino(arr[rand()%7]);
		}
	}
	
	inline bool valid(int i, int j) const {
		return i >= 0 && j >= 0 && i < height && j < width;
	}
	
	bool check(bool ghost = false) {
		Piece* piece;
		if(ghost) {
			piece = &this->ghost;
		} else {
			piece = &this->current;
		}
		
		for(int i = 0; i < piece->t->n; i++) {
			for(int j = 0; j < piece->t->n; j++) {
				if(piece->t->map[i][j]) {
					int di = piece->i + i;
					int dj = piece->j + j;
					if(!valid(di, dj))   return false;
					if(map[di][dj] != 0) return false;
				}
			}
		}
		return true;
	}
	
	int line() {
		static vector<int> empty_line(width, 0);
		
		int cnt = 0;
		for(int i = height-1; i > cnt; i--) {
			map[i] = map[i-cnt];
			
			bool full = true;
			for(int j = 0; j < width; j++) {
				if(map[i][j] == 0) {
					full = false;
					break;
				}
			}
			
			if(full) {
				cnt++;
				i++;
			}
		}
		
		for(int i = 0; i < cnt; i++) {
			map[i] = empty_line;
		}
		
		points += 100 * ( ( cnt * (cnt + 1) ) / 2 );
		
		return 100 * ( ( cnt * (cnt + 1) ) / 2 );
	}

	void nextPiece() {
		for(int i = 0; i < current.t->n; i++) {
			for(int j = 0; j < current.t->n; j++) {
				if(current.t->map[i][j]) {
					map[current.i+i][current.j+j] = current.t->color;
				}
			}
		}
		
		/* Heavy Tetrimino */
		if(current.t->heavy) {
			int cnt = 0;
			for(int i = height - 1; i > cnt; i--) {
				map[i][current.j] = map[i - cnt][current.j];
			
				if(map[i][current.j] == 0) {
					cnt++;
					i++;
				}
			}
			
			for(int i = 0; i < cnt; i++) {
				map[i][current.j] = 0;
			}
		}
		
		/* Blast Tetrimino */
		if(current.t->blast > 0) {
			int cnt = 0;
			for(int i = -current.t->blast; i <= current.t->blast; i++) {
				
				for(int j = -current.t->blast; j <= current.t->blast; j++) {
					int di = current.i + i;	
					int dj = current.j + j;
					if(valid(di, dj)) {
						map[di][dj] = 0;
					}
				}
			}
		}
		getNextPiece();
	}

	void step() {
		current.i++;
		if(!check()) {
			current.i--;
			nextPiece();
		}
	}
	
	void fall() {
		do {
			current.i++;
		} while(check());
		current.i--;
		nextPiece();
	}

	void getGhost() {
		ghost = current;
		do {
			ghost.i++;
		} while(check(true));
		ghost.i--;
	}
	
	void move(int dir) {
		current.j += dir;
		if(!check()) {
			current.j -= dir;
		}
	}
	
	void rotate() {
		current.t->rotate();
		if(!check()) {
			current.t->rotate_back();
		}
	}
	
	void printTile() {
		attron (COLOR_PAIR(0));
		printw("xx");
		attroff(COLOR_PAIR(0));
	}
		
	void printLine() {
		for(int k = 0; k < 2; k++) {
			for(int i = 0; i < width + 2; i++) {
				printTile();
			}
			printw("\n");
		}
	}

	void draw(bool border = false) {
		static int BASIC = 0;
		static int GHOST = 1;
		static int HEAVY = 2;
		static int BLAST = 4;
		
		static char GHOST_TILE[] = "::";
		static char HEAVY_TILE[] = "++";
		static char BLAST_TILE[] = "><";
		static char BASIC_TILE[] = "  ";
		
		vector< vector<int> > total = map;
		vector< vector<int> > type(map.size(), vector<int>(map[0].size(), BASIC));
		
		// Draw ghost on map		
		if(ghost_enabled) {
			getGhost();
		
			for(int i = max(0, hidden - ghost.i); i < ghost.t->n && ghost.i + i < height; i++) {
				for(int j = 0; j < ghost.t->n && ghost.j + j < width; j++) {
					if(ghost.t->map[i][j]) {
						total[ghost.i+i][ghost.j+j] = ghost.t->color;
						type [ghost.i+i][ghost.j+j] |= GHOST;
					}
				}
			}
		}
		
		// Draw piece on map
		for(int i = max(0, hidden - current.i); i < current.t->n && current.i + i < height; i++) {
			for(int j = 0; j < current.t->n && current.j + j < width; j++) {
				if(current.t->map[i][j]) {
					int di = current.i+i;
					int dj = current.j+j;
					total[di][dj] = current.t->color;
					       if(current.t->heavy) {
						type[di][dj] = HEAVY;
					} else if(current.t->blast > 0) {
						type[di][dj] = BLAST;
					}
				}
			}
		}
		
		if(border) printLine();
		
		// Draw map
		for(int i = hidden; i < height; i++) {
			if(border) printTile();
			for(int j = 0; j < width; j++) {
				attron (COLOR_PAIR(total[i][j]));
				char* tile;
				if(type[i][j] & GHOST) {
					tile = GHOST_TILE;
				} else if(type[i][j] & HEAVY) {
					tile = HEAVY_TILE;
				} else if(type[i][j] & BLAST) {
					tile = BLAST_TILE;
				} else {
					tile = BASIC_TILE;
				}
				printw(tile);
				attroff(COLOR_PAIR(total[i][j]));
			}
			if(border) printTile();
			printw("\n");
		}
		if(border) printLine();
	}
	
	void drawNext() {
		for(int i = 0; i < next.t->n; i++) {
			for(int j = 0; j < next.t->n; j++) {
				int current_color = next.t->map[i][j] ? next.t->color : 0;
				attron (COLOR_PAIR(current_color));
				printw("  ");
				attroff(COLOR_PAIR(current_color));
			}
			printw("\n");
		}
	}
	/*
	vector<string> drawASCII() {
		vector< vector<int> > total = map;
		// Draw piece
		
		for(int i = max(0, hidden - piece.i); i < piece.t->n && piece.i + i < height; i++) {
			for(int j = 0; j < piece.t->n && piece.j + j < width; j++) {
				if(piece.t->map[i][j]) {
					total[piece.i+i][piece.j+j] = piece.t->color;
				}
			}
		}
		
		// Draw map
		vector<string> drawing;
		for(int i = hidden; i < height; i++) {
			stringstream line;
			for(int j = 0; j < width; j++) {
				line << Color::Modifier(total[i][j]) << "  ";
			}
			line << Color::Modifier(Color::RESET);
			drawing.push_back(line.str());
		}
		
		
		return drawing;
	}
	
	static void print(const vector<string>& draw) {
		
		cout << Color::Modifier(Color::FG_RED);
		for(int i = 0; i < WIDTH + 2; i++) cout << "::";
		cout << Color::Modifier(Color::FG_DEFAULT);
		cout << '\n';
		
		
		for(vector<string>::const_iterator line = draw.begin();
			line != draw.end();
			line++) {
			
			//printf("%s", Color::Modifier(Color::FG_RED));
			cout << Color::Modifier(Color::FG_RED);
			cout << "::";
			cout << Color::Modifier(Color::FG_DEFAULT);
			
			cout << *line;
			
			cout << Color::Modifier(Color::FG_RED);
			cout << "::";
			cout << Color::Modifier(Color::FG_DEFAULT);
			
			cout << '\n';
		}
		
		cout << Color::Modifier(Color::FG_RED);
		for(int i = 0; i < WIDTH + 2; i++) cout << "::";
		cout << Color::Modifier(Color::FG_DEFAULT);
		cout << '\n';
	}
	*/
};

inline void init() {
	/* ncurses */
	initscr();
	
	/* ncurses colors */
	if(has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_BLACK, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_WHITE);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_YELLOW);
	init_pair(9, COLOR_BLACK, COLOR_YELLOW);

	/* ncurses input */
	curs_set(FALSE);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

	/* random generator (to be improved) */
	srand(time(NULL));
}

inline void deinit() {	
	endwin();
}

time_t pause() {
	time_t pause_time = time(NULL);
	bool paused = true;
	while(paused) {
		int ch = getch();
		if(ch == ' ') paused = false;
		if(ch == 10)  paused = false;
		if(ch == 'p') paused = false;
	}
	return difftime(time(NULL), pause_time);
}

int exec() {
	Tetris t(HEIGHT, WIDTH);
	time_t start_time, current_time;
	time(&start_time);
	time(&current_time);
	double tick = 0.3;
	
	bool done    = false;
	bool changed = true;
	
	while(!t.gameover && !done) {
		int ch = getch();
		switch(tolower(ch)) {
			case 'q':
				done = true;
				break;
			case KEY_UP:
				t.rotate();
				changed = true;
				break;
			case KEY_LEFT:
				t.move(-1);
				changed = true;
				break;
			case KEY_RIGHT:
				t.move(1);
				changed = true;
				break;
			case KEY_DOWN:
				t.step();
				changed = true;
				break;
			case ' ':
				t.fall();
				changed = true;
				break;
			case 'g':
				t.ghost_enabled = !t.ghost_enabled;
				changed = true;
				break;
			case 'p':
				current_time += pause();
				break;
		}
		if(difftime(time(NULL), current_time) > tick) {
			time(&current_time);
			t.step();
			changed = true;
		}
		if(changed) {
			t.line();
			erase();
			t.draw(true);
			printw("Points: %d\n", t.points);
			printw("Next:\n");
			t.drawNext();
			
			refresh();
			changed = false;
		}
    }
}

int main (int argc, char const *argv[]) {
	init();
/*
	for(int i = 0; i < 200; i++) {
		string s = "";
		s += i;
		printw(s.c_str());
	}
	refresh();
*/

	exec();
	
	nodelay(stdscr, FALSE);
	getch();

	deinit();

	return 0;
}

