#include "CATengine.hpp"

using namespace std;

SDL_Control::SDL_Control() {
	up = false;
	down = false;
	left = false;
	right = false;
	quit = false;
}

// all em gets...

bool SDL_Control::arrow_up() {
	return up;
}

bool SDL_Control::arrow_down() {
	return down;
}

bool SDL_Control::arrow_left() {
	return left;
}

bool SDL_Control::arrow_right() {
	return right;
}

bool SDL_Control::action_quit() {
	return quit;
}

void SDL_Control::poll_events() {
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
			        case SDLK_UP:
			        case SDLK_w:
						up = true;
						break;
			        case SDLK_DOWN:
			        case SDLK_s:
						down = true;
						break;
					case SDLK_LEFT:
					case SDLK_a:
						left = true;
						break;
			        case SDLK_RIGHT:
			        case SDLK_d:
						right = true;
						false;
				}
				
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
			        case SDLK_UP:
			        case SDLK_w:
						up = false;
						break;
			        case SDLK_DOWN:
			        case SDLK_s:
						down = false;
						break;
					case SDLK_LEFT:
					case SDLK_a:
						left = false;
						break;
			        case SDLK_RIGHT:
			        case SDLK_d:
						right = false;
						false;
				}
				
				break;
		}
	}
}
