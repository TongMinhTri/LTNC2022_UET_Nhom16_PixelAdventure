#include "Stone.h"

Stone::Stone()
{
	x = 480;
	y = 384;
	stone.x = stone.y = stone.h = stone.w = 0;
	test.x = test.y = 0;
	test.w = test.h = w_h;
}

Stone::~Stone()
{
}

void Stone::set_clips()
{
	for (int i = 0; i < 4; i++)
	{
		frame_clips[i].x = i * w_h;
		frame_clips[i].y = 0;
		frame_clips[i].w = w_h;
		frame_clips[i].h = w_h;
	}
}

void Stone::setImg(SDL_Renderer* renderer, string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			stone.w = loadedSurface->w;
			stone.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	body = newTexture;
}

void Stone::show_frame(SDL_Renderer* renderer, string path)
{
	setImg(renderer, path);
	frame++;
	if (frame == 3) frame = 0; // ngan cho frame ko qua 11 
	SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
	SDL_Rect renderquad = { x, y, frame_w, frame_h };
	SDL_RenderCopy(renderer, body, current_clips, &renderquad);
}

void Stone::setPos(int x, int y)
{
	stone.x = x;
	stone.y = y;
}

SDL_Rect Stone::getRect_stone()
{
	return stone;
}

void Stone::set_Stone(SDL_Renderer* renderer, int a, int b, string path)
{
	x = a;
	y = b;
	stone.w = w_h;
	stone.h = w_h;
	setPos(x, y);
	setImg(renderer, path);
}


void Stone::stone_move(SDL_Renderer* renderer, Map& map_data)
{
	if (state == 0)
	{
		if (x - speed > 192) x -= speed;
		else
		{
			x = 192;
			state = 1;
		}
	}
	else if (state == 1)
	{
		if (x + speed < 480) x += speed;
		else
		{
			x = 480;
			state = 0;
		}
	}
	setPos(x, y);
	int x1 = x / TILE_SIZE + 6;
	int x2 = ( x + frame_w - 1) / TILE_SIZE+6;
	map_data.tile[8][x1] = x1;
	map_data.tile[8][x2] = x2;
	for (int i = 4; i <= 10; i++)
	{
		if (i != x1 || i != x2)
		{
			map_data.tile[8][i] = 0;
		}
	}
	SDL_RenderCopy(renderer, body, &test, &stone);
}

//void Stone::show(SDL_Renderer* renderer)
//{
//	SDL_RenderCopy(renderer, body, &test, &stone);
//}