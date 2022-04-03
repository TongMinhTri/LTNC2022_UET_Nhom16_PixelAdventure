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

Stone::Stone(SDL_Renderer* renderer, int a, int b, int limitx, int limity,string path)
{
	frame = 0;
	x = a; 
	y = b;
	limit_x = limitx;
	limit_y = limity;
	x_val = x;
	y_val = y;
	stone.w = w_h;
	stone.h = w_h;
	test.x = test.y = 0;
	test.w = test.h = w_h;
	setPos(x, y);
	state = 0;
	input_type.down = 1;
	input_type.jump = 0;
	input_type.left= 0;
	input_type.right = 0;
	setImg(renderer,path);
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

void Stone::Stone_Move_Circle(SDL_Renderer* renderer, Map& map_data)
{
	
	if (input_type.left == 1) x -= 4;
	if (input_type.right == 1) x += 4;
	if (input_type.jump == 1) y = y - 4;
	if (input_type.down == 1) y = y + 4;
	setPos(x, y);

	SDL_RenderCopy(renderer, body, &test, &stone);
}

void Stone::DoStone_Circle()
{
	if (stone.x == x_val && stone.y == y_val)
	{
		input_type.down = 1;
		input_type.jump = 0;
		input_type.left = 0;
		input_type.right = 0;
	}
	if (stone.x == x_val && stone.y == limit_y)
	{
		input_type.down = 0;
		input_type.jump = 0;
		input_type.left = 1;
		input_type.right = 0;
	}
	if (stone.x == limit_x && stone.y == limit_y)
	{
		input_type.down = 0;
		input_type.jump = 1;
		input_type.left = 0;
		input_type.right = 0;
	}
	if (stone.x == limit_x && stone.y == y_val)
	{
		input_type.down = 0;
		input_type.jump = 0;
		input_type.left = 0;
		input_type.right = 1;
	}
}

void Stone::stone_move_up(SDL_Renderer* renderer, Map& map_data)
{
	if (state == 0)
	{
		if (y - 2 > limit_x ) y -= 2;
		else
		{
			y = limit_x;
			state = 1;
		}
	}
	else if (state == 1)
	{
		if (y + 2 < limit_y) y += 2;
		else
		{
			y = limit_y;
			state = 0;
		}
	}
	setPos(x, y);
	SDL_RenderCopy(renderer, body, &test, &stone);
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
		if (x - speed > limit_x) x -= speed;
		else
		{
			x = limit_x;
			state = 1;
		}
	}
	else if (state == 1)
	{
		if (x + speed < limit_y) x += speed;
		else
		{
			x = limit_y;
			state = 0;
		}
	}
	setPos(x, y);

	SDL_RenderCopy(renderer, body, &test, &stone);
}