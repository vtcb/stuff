#include "game.h"

void Game::play() {
	Timer  timer    = Timer();
	Map    map      = Map();
	Player player   = Player(&map);


	Blinky blinky   = Blinky(&map, &player);
	Pinky  pinky    = Pinky (&map, &player);
	Inky   inky     = Inky  (&map, &player, &blinky);
	Clyde  clyde    = Clyde (&map, &player);

	vector<Ghost*> ghosts;

	ghosts.push_back(&blinky);
	ghosts.push_back(&pinky);
	ghosts.push_back(&inky);
	ghosts.push_back(&clyde);

	Draw   draw     = Draw(map.height, map.width);

	bool done = false;
	bool need_reset = false;

	timer.start();

	while(!done && player.lives > 0) {
		/* Level Start! */
		if(need_reset) {
			need_reset = false;

			player.reset();
			
			blinky.reset();
			pinky. reset();
			inky.  reset();
			clyde. reset();
		}

		switch(tolower(getch())) {
			case 'q':
				done = true;
				break;
			case KEY_UP:
				player.changeDirection(DIRECTION::UP);
				break;
			case KEY_LEFT:
				player.changeDirection(DIRECTION::LEFT);
				break;
			case KEY_RIGHT:
				player.changeDirection(DIRECTION::RIGHT);
				break;
			case KEY_DOWN:
				player.changeDirection(DIRECTION::DOWN);
				break;
			case 'p':
				timer.pause();
				while(timer.paused) {
					char ch = tolower(getch());
					if(ch == 'p') {
						timer.unpause();
					}
				}
				break;
		}
		//dbg("CARALHO")

		if(timer.time() > tick) {
			timer.start();
			// Should increase counter, not reset timer
			// Whatever...

			/* Do stuff */
			player.move();
			player.eat();
			
			for(Ghost* ghost : ghosts) {
				ghost->lookForPacman();
				ghost->move();
				ghost->lookForPacman();

				if(ghost->got_pacman) {
					player.die();
					need_reset = true;
					break;
				}
			}

			/* Draw stuff */
			map.draw();
			player.draw();
			
			for(Ghost* ghost : ghosts) {
				ghost->draw();
			}
		
			/* Actually draw stuff to screen */
			erase();

			draw.put();

			printw("\n");
			printw("Points: %d\n", player.score);
			printw("Lives:  %d\n", player.lives);
/*
			printw("Player:\t%d, %d, %d\n", player.i, player.j, player.dir);
			printw("Pinky: \t%d, %d, %d\n", pinky.i,  pinky.j,  pinky.dir);
*/
			refresh();
		}
	}

	printw("GAME OVER!!!\n");
	printw("FINAL SCORE: %d\n", player.score);

	while(player.lives == 0 && getch() != 'q');
}