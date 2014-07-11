#include "CATengine.hpp"

using namespace std;

SDL_Music::SDL_Music(string path, int flags) {
	int init = Mix_Init(flags);
	
	if (init & flags != flags) {
		err("Mix_Init: failed to init, flags mismatch");
	}
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
	    err(Mix_GetError());
	}
	
	music = Mix_LoadMUS(path.c_str());
}

SDL_Music::~SDL_Music() {
	Mix_FreeMusic(music);
}

void SDL_Music::play() {
	if (Mix_PlayMusic(music, -1) == -1) {
		err(Mix_GetError());
	}
}

void SDL_Music::play_fadein(int ms) {
	if (Mix_FadeInMusic(music, -1, ms) == -1) {
		err(Mix_GetError());
	}
}

void SDL_Music::pause() {
	Mix_PauseMusic();
}

void SDL_Music::resume() {
	Mix_ResumeMusic();
}

void SDL_Music::rewind() {
	Mix_RewindMusic();
}

void SDL_Music::stop() {
	Mix_HaltMusic();
}

void SDL_Music::stop_fadeout(int ms) {
	Mix_FadeOutMusic(ms);
}

void SDL_Music::setVolume(int percent) {
	Mix_VolumeMusic(percent*128/100);
}
int SDL_Music::getVolume() {
	int v = Mix_VolumeMusic(-1);
	
	return v*100/128;
}

void SDL_Music::load(int flags) {
	int init = Mix_Init(flags);
	
	if (init & flags != flags) {
		err("Mix_Init: failed to init, flags mismatch");
	}
}

void SDL_Music::unload() {
	Mix_CloseAudio();
	Mix_Quit();
}
