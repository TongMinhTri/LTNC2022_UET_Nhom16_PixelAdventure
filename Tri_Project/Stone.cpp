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

void Stone::init_stone(SDL_Renderer* renderer, int a, int b, int limitx, int limity, string path, int k_)
{
	frame = 0;
	x = a;
	y = b;
	number_frame = k_;
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
	input_type.left = 0;
	input_type.right = 0;
	setImg(renderer, path);
}

void Stone::set_clips()
{
	for (int i = 0; i < number_frame; i++)
	{
		frame_clips[i].x = i * w_h;
		frame_clips[i].y = 0;
		frame_clips[i].w = w_h;
		frame_clips[i].h = w_h;
	}
}

void Stone::Stone_Move_Circle(SDL_Renderer* renderer)
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

void Stone::stone_move_up(SDL_Renderer* renderer)
{
	v_y += speedy;
	if (state == 0)
	{
		if (y - int(v_y) > limit_x) y -= int(v_y);
		else
		{
			y = limit_x;
			state = 1;
			v_y = 0;
		}
	}
	else if (state == 1)
	{
		if (y + int(v_y) < limit_y) y += int(v_y);
		else
		{
			y = limit_y;
			state = 0;
			v_y = 0;
		}
	}
	setPos(x, y);
	SDL_RenderCopy(renderer, body, &test, &stone);
}

void Stone::show_stand(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, body, NULL, &stone);
}

void Stone::stone_move(SDL_Renderer* renderer)
{
	v_x += speedx;
	if (state == 0)
	{
		if (x - int(v_x) > limit_x) x -= int(v_x);
		else
		{
			x = limit_x;
			state = 1;
			v_x = 0;
		}
	}
	else if (state == 1)
	{
		if (x + int(v_x) < limit_y) x += int(v_x);
		else
		{
			x = limit_y;
			state = 0;
			v_x = 0;
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

void Stone::show_frame_up(SDL_Renderer* renderer,double speed_run)
{
	v_y += speed_run;
	if (state == 0)
	{
		if (y - int(v_y) > limit_x) y -= int(v_y);
		else
		{
			y = limit_x;
			state = 1;
			v_y = 0;
		}
	}
	else if (state == 1)
	{
		if (y + int(v_y) < limit_y) y += int(v_y);
		else
		{
			y = limit_y;
			state = 0;
			v_y = 0;
		}
	}
	setPos(x, y);
	frame++;
	if (2 * frame / 3 >= number_frame) frame = 0; // ngan cho frame ko qua 3
	SDL_Rect* current_clips = &frame_clips[2 * frame / 3]; // rect nguon de in ra anh
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
	SDL_Rect test1;
	test1.x = stone.x;
	test1.y = stone.y;
	test1.w = frame_w;
	test1.h = frame_h;
	return test1;
}

void Stone::set_Stand(SDL_Renderer* renderer, int a, int b, string path)
{
	x = a;
	y = b;
	stone.w = 5;
	stone.h = 48;
	setPos(x, y);
	setImg(renderer, path);
}