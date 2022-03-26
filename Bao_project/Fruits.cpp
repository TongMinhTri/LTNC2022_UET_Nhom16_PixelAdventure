#include "Fruits.h"


Fruits::~Fruits()
{
	fruits.x = 0;
	fruits.y = 0;
	fruits.w = 32;
	fruits.y = 32;
	x = 0;
	y = 0;
	frame = 0;
}

Fruits::Fruits()
{
	fruits.x = 0;
	fruits.y = 0;
	fruits.w = 32;
	fruits.y = 32;
	x = 0;
	y = 0;
	frame = 0;
}

Fruits::Fruits(SDL_Renderer* renderer,string path)
{
	x = 0;
	y = 0;
	setPos(x, y);
	frame = 0;
	setImg(renderer, path);
}

void Fruits::set_clips()
{
	for (int i = 0; i < 16; i++)
	{
		frame_clips[i].x = i * 32;
		frame_clips[i].y = 0;
		frame_clips[i].w = 32;
		frame_clips[i].h = 32;
	}
}

void Fruits::setImg(SDL_Renderer* renderer, string path)
{
	body = BG::loadTexture(renderer, path);
}

void Fruits::show_frame(SDL_Renderer* renderer, string path)
{
	setImg(renderer, path);
	frame++;
	if (frame == 16) frame = 0; // ngan cho frame ko qua 11 
	SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
	SDL_Rect renderquad = { x, y, 32, 32 };
	SDL_RenderCopy(renderer, body, current_clips, &renderquad);
}



void Fruits::setPos(int x, int y)
{
	fruits.x = x;
	fruits.y = y;
}

void Fruits::setFruits(SDL_Renderer* renderer, int a, int b,string path)
{
	x = a;
	y = b;
	setPos(x, y);
	frame = 0;
	setImg(renderer, path);
}

void Fruits::Getx( int a)
{
	fruits.x = a;
}

