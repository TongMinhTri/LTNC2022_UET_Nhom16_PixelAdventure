#include "Fruits.h"

Fruits::Fruits()
{
	fruits.x = 0;
	fruits.y = 0;
	x = 0;
	y = 0;
	frame = 0;
	alive = true;
}

Fruits::~Fruits()
{
}

void Fruits::set_clips()
{
	for (int i = 0; i < 16; i++)
	{
		frame_clips[i].x = i * w_h;
		frame_clips[i].y = 0;
		frame_clips[i].w = w_h;
		frame_clips[i].h = w_h;
	}
}

void Fruits::setImg(SDL_Renderer* renderer, string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			fruits.w = loadedSurface->w;
			fruits.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	body = newTexture;
}

void Fruits::show_frame(SDL_Renderer* renderer)
{
	if (alive)
	{
		frame++;
		if (frame == 16) frame = 0; // ngan cho frame ko qua 16
		SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
		SDL_Rect renderquad = { x, y, frame_w, frame_h };
		SDL_RenderCopy(renderer, body, current_clips, &renderquad);
	}
}

void Fruits::setFruits(SDL_Renderer* renderer, int a, int b, string path)
{
	alive = true;
	x = a;
	y = b;
	fruits.w = w_h;
	fruits.h = w_h;
	setPos(x, y);
	frame = 0;
	setImg(renderer, path);
	tes.x = tes.y = tes.w = tes.h = 0;
}

void Fruits::setPos(int x, int y)
{
	fruits.x = x;
	fruits.y = y;
}

SDL_Rect Fruits::getRect_fruits()
{
	tes.x = fruits.x;
	tes.y = fruits.y;
	tes.w = w_h;
	tes.h = w_h;
	return tes;
}



