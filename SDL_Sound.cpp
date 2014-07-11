#include "CATengine.hpp"

using namespace std;

SDL_Sound::SDL_Sound(string path, int flags) {
	load(flags);
	
	allocate_channels(1);
	sound = Mix_LoadWAV(path.c_str());
}

SDL_Sound::~SDL_Sound() {
	Mix_FreeChunk(sound);
}

void SDL_Sound::allocate_channels(int extra) {
	Mix_AllocateChannels(extra);
}

void SDL_Sound::play(int loop) {
 	if (channel = Mix_PlayChannel(-1, sound, loop) == -1) {
 		err(Mix_GetError());
 	}
}

void SDL_Sound::play_fadein(int ms, int loop) {
	Mix_FadeInChannel(-1, sound, loop, ms);
}

void SDL_Sound::stop() {
	Mix_HaltChannel(channel);
}

void SDL_Sound::stop_fadeout(int ms) {
	Mix_FadeOutChannel(channel, ms);
}

void SDL_Sound::pause() {
	Mix_Pause(channel);
}

void SDL_Sound::resume() {
	Mix_Resume(channel);
}

void SDL_Sound::load(int flags) {
	int init = Mix_Init(flags);
	
	if (init & flags != flags) {
		err("Mix_Init: failed to init, flags mismatch");
	}
}

void SDL_Sound::unload() {
	Mix_CloseAudio();
	Mix_Quit();
}
