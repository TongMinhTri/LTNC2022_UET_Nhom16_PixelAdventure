#include "Heart.h"

Heart::Heart()
{
	x = 0;
	y = 0;
	size = 32;
	heart.x = 0;
	heart.y = 0;
	heart.w = 32;
	heart.h = 32;
	test.x = test.y = test.w = test.h = 0;
	setImg(renderer, "heart.png");
}

Heart::~Heart()
{
}

void Heart::show(SDL_Renderer* renderer)
{
	if (dead == false)
		SDL_RenderCopy(renderer, body, NULL, &heart);
}

void Heart::setImg(SDL_Renderer* renderer, string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			heart.w = loadedSurface->w;
			heart.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	body = newTexture;
}

void Heart::setPos(int x, int y)
{
	heart.x = x;
	heart.y = y;
}

void Heart::setHeart(SDL_Renderer* renderer, int a, int b)
{
	dead = false;
	x = a;
	y = b;
	heart.w = 32;
	heart.h = 32;
	setPos(x, y);
	setImg(renderer, "Heart/heart.png");
	test.x = test.y = test.w = test.h = 0;
}