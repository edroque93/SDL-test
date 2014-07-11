#ifndef catengine_hpp
#define catengine_hpp

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#define err(x) {cerr << x << endl;}

class SDL_Sprite {
	public:
		SDL_Sprite(SDL_Renderer* display, 
			std::string sprite_path, 
			int flags = IMG_INIT_PNG);
		SDL_Sprite(SDL_Renderer* display, 
			std::string sprite_path, 
			int width,
			int height,
			int flags = IMG_INIT_PNG);
		~SDL_Sprite();
		SDL_Texture* getTexture();
		int getWidth();
		int getHeight();
		int getX();
		int getY();
		void draw();
		void draw(int x, int y);
		void draw(int selector, int x, int y);
		void draw(int xsel, int ysel, int x, int y);
		void draw_rotate(int xsel, 
			int ysel, 
			int x, 
			int y, 
			double angle, 
			SDL_Point* center = NULL,
			SDL_RendererFlip flip = SDL_FLIP_NONE);
		void draw_primitive(int xsel, 
			int ysel, 
			int x, 
			int y, 
			double zoom = 1.0, 
			double angle = 0.0, 
			SDL_Point* center = NULL, 
			SDL_RendererFlip flip = SDL_FLIP_NONE);
		bool inArea(int x, int y);
		
		static void load(int flags);
		static void unload();
		
	private:
		int width;
		int height;
		int x;
		int y;
		SDL_Renderer* display;
		SDL_Texture* texture;
		
		void load_texture(std::string path);
};

class SDL_Music {
	public:
		SDL_Music(std::string path, int flags = MIX_INIT_MP3);
		~SDL_Music();
		void setVolume(int percent);
		int getVolume();
		void play();
		void play_fadein(int ms = 1000);
		void pause();
		void resume();
		void rewind();
		void stop();
		void stop_fadeout(int ms = 1000);
		
		static void load(int flags);
		static void unload();
		
	private:
		Mix_Music* music;
};

class SDL_Sound {
	public:
		SDL_Sound(std::string path, int flags = MIX_INIT_OGG);
		~SDL_Sound();
		void play(int loop = 0);
		void play_fadein(int ms = 1000, int loop = 0);
		void stop();
		void stop_fadeout(int ms = 1000);
		void pause();
		void resume();
		void allocate_channels(int extra);
		
		static void load(int flags);
		static void unload();
		
	private:
		Mix_Chunk* sound;
		int channel;
};

class SDL_Control {
	public:
		SDL_Control();
		bool arrow_up();
		bool arrow_down();
		bool arrow_left();
		bool arrow_right();
		bool action_quit();
		void poll_events();		
		
	private:
		bool up, down, left, right, quit;
		SDL_Event event;
};

#endif
