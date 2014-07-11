#include "Game.hpp"

#include <windows.h>
void thread_paint();

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		err("Couldn't initalize SDL");
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("2048 - CATengine", 
											SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
											480, 480,  // 640x480
											SDL_WINDOW_SHOWN);
	
	display = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	if (display == NULL) {
		err("Couldn't create renderer")
	}
	
	table = new SDL_Sprite(display, ".\\res\\table.png");
	tiles = new SDL_Sprite(display, ".\\res\\tiles.png", 120, 120);
	
	SDL_Control* c = new SDL_Control();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			board[i][j] = 0;
		}
	}
	
	active = true;	
	thread t(thread_paint);

	srand(time(NULL));
	drop_random();
	drop_random();

	while (active) {
		c->poll_events();
		if (c->action_quit()) {
			active = false;	
		}
		
		if (c->arrow_up()) {
			move_up();
			
			c->poll_events();
			while (c->arrow_up()) {
				c->poll_events();
			}
		} else
		if (c->arrow_down()) {
			move_down();
			
			c->poll_events();
			while (c->arrow_down()) {
				c->poll_events();
			}
		} else
		if (c->arrow_left()) {
			move_left();
			
			c->poll_events();
			while (c->arrow_left()) {
				c->poll_events();
			}
		} else
		if (c->arrow_right()) {
			move_right();
			
			c->poll_events();
			while (c->arrow_right()) {
				c->poll_events();
			}
		}
		
		SDL_Delay(10);
	}
	
	t.join(); // safe join
	
	table->~SDL_Sprite();
	
	SDL_Sprite::unload();
	
	SDL_DestroyRenderer(display);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void thread_paint() {
	int old[4][4];
	bool move;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			old[i][j] = 0;
		}
	}
	
	while (active) {
		move = false;
		
		shared.lock();
		
		move = board_eq(old, board);
		
		if (move) { // Slide frameS <-
			
			// TO-DO
		
		/*
			SDL_RenderClear(display);
			table->draw();
		
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (old[i][j] != board[i][j]) {
						switch (last_move) {
							UP:
								for (int c = j; c >= 0; c--) {
									if (board[i][c] == 0) {
										
										
										
										SDL_RenderPresent(display);
										SDL_Delay(100);
									}
								}
								break;
							DOWN:
								break;
							LEFT:
								break;
							RIGHT:
								break;
						}
					}
				}
			}*/
		} else { // Normal frame
			SDL_RenderClear(display);
			table->draw();
			
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					draw_tile(board[i][j], i, j);
				}
			}
			
			SDL_RenderPresent(display);
		}
		
		shared.unlock();
		//usleep(10 * 1000); // VSYNC...
	}
}
