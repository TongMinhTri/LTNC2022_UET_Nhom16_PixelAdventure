#pragma once
#ifndef BoardGame_H
#define BoardGame_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

const int SCREEN_WIDTH  = 512;
const int SCREEN_HEIGHT = 288;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Event event;
static bool quit = false;


namespace BG {
	void init(SDL_Window*& window, SDL_Renderer*& renderer);
	void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
	SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path);

}

#endif // !BoardGame_H


