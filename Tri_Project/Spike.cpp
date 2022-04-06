#include "Spike.h"

Spike::Spike(SDL_Renderer* renderer, int a, int b, int c, string path)
{
	x = a;
	y = b;
	tes.x = 0;
	tes.y = 0;
	if (c == 0)
	{
		spike.w = tes.w = 40;
		spike.h = tes.h = 16;
	}
	else
	{
		spike.w = tes.w = 16;
		spike.h = tes.h = 48;
	}
	setImg(renderer, path);
	setPos(a, b);
}

Spike::~Spike()
{
}

void Spike::setImg(SDL_Renderer* renderer, string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			spike.w = loadedSurface->w;
			spike.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	body = newTexture;
}

void Spike::setPos(int x, int y)
{
	spike.x = x;
	spike.y = y;
}

void Spike::showImg(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, body, &tes, &spike);
}

SDL_Rect Spike::getRect_spike()
{
	return spike;
}
