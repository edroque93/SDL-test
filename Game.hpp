#ifndef game_hpp
#define game_hpp

#include "CATengine.hpp"
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <thread>
#include <mutex>

using namespace std;

enum game_move {
	UP,
	DOWN,
	LEFT,
	RIGHT
};


extern SDL_Renderer* display;
extern SDL_Sprite* table;
extern SDL_Sprite* tiles;
extern mutex shared;
extern bool active;
extern game_move last_move;
extern int board[4][4];

void move_tile(int x, int y);
void move_up();
void move_down();
void move_left();
void move_right();
void drop_random();
bool isTerminal();
bool board_eq(int b1[4][4], int b2[4][4]);
void draw_tile(int number, int x, int j);
void draw_tilexy(int number, int px, int py);
bool isPowerOfTwo(int x);
int log2(int x);

#endif
