#include "Game.hpp"

SDL_Renderer* display;
SDL_Sprite* table;
SDL_Sprite* tiles;
mutex shared;
bool active;
game_move last_move;
int board[4][4];

void drop_random() {
	if (isTerminal()) return;
	
	shared.lock();
	
	int i, j;
	
	i = rand() % 4;
	j = rand() % 4;
	
	while (board[i][j] != 0) {
		i = rand() % 4;
		j = rand() % 4;
	}
	
	board[i][j] = 2 + (rand() % 2) * 2;
	
	
	shared.unlock();
}

void move_up() {
	shared.lock();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((j - 1 >= 0) && (board[i][j] != 0)) {
				while ((j - 1 >= 0) && (board[i][j] != 0) && (board[i][j-1] == 0)) {
					board[i][j-1] = board[i][j];
					board[i][j] = 0;
					j--;
				}
				
				if (board[i][j-1] == board[i][j]) {
					board[i][j-1] <<= 1;
					board[i][j] = 0;
				}
			}
		}
	}
	
	shared.unlock();
	
	last_move = UP;
	drop_random();
}

void move_down() {
	shared.lock();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j >= 0; j--) {
			if ((j + 1 < 4) && (board[i][j] != 0)) {
				while ((j + 1 < 4) && (board[i][j] != 0) && (board[i][j+1] == 0)) {
					board[i][j+1] = board[i][j];
					board[i][j] = 0;
					j++;
				}
				
				if (board[i][j+1] == board[i][j]) {
					board[i][j+1] <<= 1;
					board[i][j] = 0;
				}
			}
		}
	}
	
	shared.unlock();
	
	last_move = DOWN;
	drop_random();
}

void move_left() {
	shared.lock();
	
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if ((i - 1 >= 0) && (board[i][j] != 0)) {
				while ((i - 1 >= 0) && (board[i][j] != 0) && (board[i-1][j] == 0)) {
					board[i-1][j] = board[i][j];
					board[i][j] = 0;
					i--;
				}
				
				if (board[i-1][j] == board[i][j]) {
					board[i-1][j] <<= 1;
					board[i][j] = 0;
				}
			}
		}
	}
	
	shared.unlock();
	
	last_move = LEFT;
	drop_random();
}

void move_right() {
	shared.lock();
	
	for (int j = 0; j < 4; j++) {
		for (int i = 3; i >= 0; i--) {
			if ((i + 1 < 4) && (board[i][j] != 0)) {
				while ((i + 1 < 4) && (board[i][j] != 0) && (board[i+1][j] == 0)) {
					board[i+1][j] = board[i][j];
					board[i][j] = 0;
					i++;
				}
				
				if (board[i+1][j] == board[i][j]) {
					board[i+1][j] <<= 1;
					board[i][j] = 0;
				}
			}
		}
	}
	
	shared.unlock();
	
	last_move = RIGHT;
	drop_random();
}

void draw_tile(int number, int x, int j) {
	if (!isPowerOfTwo(number)) return;
	
	int offset = log2(number) - 1;
	
	tiles->draw(offset, 120 * x , 120 * j);
}

void draw_tilexy(int number, int px, int py) {
	if (!isPowerOfTwo(number)) return;
	
	int offset = log2(number) - 1;
	
	tiles->draw(offset, px , py);
}

bool isPowerOfTwo(int x) {
	return ((x != 0) && !(x & (x - 1)));
}

int log2(int x) {
	return log(x) / log(2);
}

bool board_eq(int b1[4][4], int b2[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b1[i][j] != b2[i][j]) {
					return false;
			}
		}
	}
	
	return true;
}

// Let's finish each move and then build this like a pro

void move_tile(int x, int y) {
	shared.lock();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if ((j - 1 >= 0) && (board[i][j] != 0)) {
				while ((j + y >= 0) && (i + x >= 0) && (board[i][j] != 0) && (board[i+x][j+y] == 0)) {
					board[i+x][j+y] = board[i][j];
					board[i][j] = 0;
					j += y;
					i += x;
				}
				
				if (board[i+x][j+y] == board[i][j]) {
					board[i+x][j+y] <<= 1;
					board[i][j] = 0;
				}
			}
		}
	}
	
	shared.unlock();	
}

bool isTerminal() {
	shared.lock();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				shared.unlock();
				return false;
			}
		}
	}
	
	shared.unlock();
	
	return true;
}
