#include "Background.h"

Background::Background()
{
	rect.x = 0;
	rect.y = 0;
}

Background::~Background()
{
}

Background::Background(SDL_Renderer* renderer, string path)
{
	body = BG::loadTexture(renderer, path);
}

void Background::show(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopy(renderer, body, NULL, &rect);
}

void Background::setImg(SDL_Renderer* renderer, string path)
{
	body = BG::loadTexture(renderer, path);
}