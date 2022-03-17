#include "Ninja_Frog.h"


Ninja_Frog::Ninja_Frog()
{
}

Ninja_Frog::Ninja_Frog(SDL_Renderer *renderer)
{ 
	x = SCREEN_WIDTH/2;
	y = SCREEN_HEIGHT*3/4;
	setPos(x, y);
	frame = 0;
	width_frame = 32;
	height_frame = 32;
	status = -1;
	setImg(renderer, "Fall.png");
}

void Ninja_Frog::move(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				cout << "Up" << '\n';
				if (rect.y - 10 >= 22)
					Gety(-10);
				else
					Gety(-1 * ( rect.y - 22) );
				break;
			}
			case SDLK_DOWN:
			{
				cout << "Down" << '\n';
				if (rect.y + 10 <= 235)
					Gety(+10);
				else
					Gety( 235-rect.y );
				break;
			}
			case SDLK_LEFT:
			{
				status = Walk_left;
				input_type.left = 1;
				break;
			}
			case SDLK_RIGHT:
			{
				status = Walk_right;
				input_type.right = 1;
				break;
			}
		}
	}
}

void Ninja_Frog::set_clips()
{
	for (int i = 0; i < 12; i++)
	{
		frame_clips[i].x = i * 32;
		frame_clips[i].y = 0;
		frame_clips[i].w = 32;
		frame_clips[0].h = 32;
	}
}

void Ninja_Frog::show_frame(SDL_Renderer* renderer)
{
	if (status == Walk_right)
	{
		setImg(renderer, "Terrain_Project/Run_(32x32).png");
	}
	else
	{
		setImg(renderer, "Terrain_Project/Run_(32x32)_l.png");
	}
	if (input_type.left == 1 || input_type.right == 1)
	{
		frame++;
	}
	else frame = 0;
	SDL_Rect* current_clips = &frame_clips[frame];
	SDL_Rect renderquad = { rect.x, rect.y, 32, 32 };
	SDL_RenderCopy(renderer, body, current_clips, &renderquad);
}

Ninja_Frog::~Ninja_Frog()
{
}
