#include "CATengine.hpp"

using namespace std;

/*
 * flags: see IMG_Init
 */
SDL_Sprite::SDL_Sprite(SDL_Renderer* display, string sprite_path, int width, int height, int flags) {
	load(flags);
	
	this->display = display;
	this->width = width;
	this->height = height;
	texture = IMG_LoadTexture(display, sprite_path.c_str());
	
	if (texture == NULL) {
		err(IMG_GetError());
	}
}

SDL_Sprite::SDL_Sprite(SDL_Renderer* display, string sprite_path, int flags) {
	load(flags);
	
	this->display = display;
	
	load_texture(sprite_path);
	
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	this->width = width;
	this->height = height;
}

SDL_Sprite::~SDL_Sprite() {
	SDL_DestroyTexture(texture);
}

void SDL_Sprite::load(int flags) {
	int init = IMG_Init(flags);
	
	if (init & flags != flags) {
		err("IMG_Init: failed to init, flags mismatch");
	}
}

void SDL_Sprite::unload() {
	IMG_Quit();
}

SDL_Texture* SDL_Sprite::getTexture() {
	return texture;
}

int SDL_Sprite::getWidth() {
	return width;
}

int SDL_Sprite::getHeight() {
	return height;
}

int SDL_Sprite::getX() {
	return x;
}

int SDL_Sprite::getY() {
	return y;
}

void SDL_Sprite::draw() {
	draw_primitive(0, 0, 0, 0);
}

void SDL_Sprite::draw(int x, int y) {
	draw_primitive(0, 0, x, y);
}

void SDL_Sprite::draw(int selector, int x, int y) {
	draw_primitive(selector, 0, x, y);
}

void SDL_Sprite::draw(int xsel, int ysel, int x, int y) {
	draw_primitive(xsel, ysel, x, y);
}

void SDL_Sprite::draw_rotate(int xsel, 
	int ysel, 
	int x, 
	int y, 
	double angle, 
	SDL_Point* center, 
	SDL_RendererFlip flip) {
	draw_primitive(xsel, ysel, x, y, 1.0, angle, center);
}

void SDL_Sprite::draw_primitive(int xsel, 
	int ysel, 
	int x, 
	int y, 
	double zoom, 
	double angle, 
	SDL_Point* center, 
	SDL_RendererFlip flip) {
	this->x = x;
	this->y = y;
	
	SDL_Rect* intexture = new SDL_Rect();
	SDL_Rect* indisplay = new SDL_Rect();

	intexture->x = width*xsel;
	intexture->y = height*ysel;
	intexture->w = this->width;
	intexture->h = this->height;

	indisplay->x = x;
	indisplay->y = y;
	indisplay->w = this->width*zoom;
	indisplay->h = this->height*zoom;

	SDL_RenderCopyEx(display, texture, intexture, indisplay, angle, center, flip);
	
	delete intexture;
	delete indisplay;
}

void SDL_Sprite::load_texture(string path) {
	texture = IMG_LoadTexture(display, path.c_str());
	
	if (texture == NULL) {
		err(IMG_GetError());
	}
}

bool SDL_Sprite::inArea(int x, int y) {
	int tx = this->x;
	int ty = this->y;

	if (x >= tx && x <= tx+width && 
		y >= ty && y <= ty+height)
		return true;
	return false;
}
