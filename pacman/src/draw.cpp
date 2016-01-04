#include "draw.h"

char Draw::buffer[100][100] = {};

void Draw::put() {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
		 	printw("%c", buffer[i][j]);
		}
		printw("\n");
	}
}

void Map::draw() const {
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			Draw::buffer[i][j] = map[i][j].draw();
		}
	}
}

char Tile::draw() const {
	char sprite = '?';
	// return '0' + _type;
	       if(type == WALL) {
		sprite = 'x';
	} else if(type == PASS) {
		if(eatable) {
			sprite = '.';
		} else {
			sprite = ' ';
		}
	} else if(type == DOOR) {
		sprite = '-';
	}
	return sprite;
}

void Player::draw() const {
	char sprite = 'o';
	switch(static_cast<DIRECTION>(dir)) {
		case DIRECTION::UP:
			sprite = 'v';
			break;
		case DIRECTION::DOWN:
			sprite = '^';
			break;
		case DIRECTION::LEFT:
			sprite = '>';
			break;
		case DIRECTION::RIGHT:
			sprite = '<';
			break;
	}

	Draw::buffer[i][j] = sprite;
}

void Ghost::draw() const {
	Draw::buffer[i][j] = sprite;
}