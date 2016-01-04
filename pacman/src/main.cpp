#include "init.h"
#include "game.h"

int main() {
	init();

	Game game;

	game.play();

	deinit();

	return 0;
}
