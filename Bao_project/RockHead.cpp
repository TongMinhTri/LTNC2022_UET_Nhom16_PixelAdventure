#include "RockHead.h"
RockHead::RockHead()
{
	x_val = 0;
	y_val = 0;
	x = 0;
	y = 0;
	frame = 0;
	input_type_.left = 0;
	input_type_.up = 0;
	type_move = STATIC_THREAT;
}
RockHead::RockHead(SDL_Renderer* renderer, int x, int y)
{
	setPos(x, y);
	frame = 0;
	z = 0;
	x_val = x;
	y_val = y;
	status = -1;
	input_type_.left = 1;
	input_type_.up = 1;
	setImg(renderer, "Rock_Head/Idle.png");
}
RockHead::RockHead(SDL_Renderer* renderer, int x, int y,int z)
{
	setPos(x, y);
	frame = 0;
	x_val = x;
	y_val = y;
	status = -1;
	input_type_.left = 0;
	input_type_.up = 0;
	setImg(renderer, "Rock_Head/Idle.png");
}
RockHead::~RockHead()
{
}

void RockHead::set_clips()
{
	for (int i = 0; i < 4; i++)
	{

		frame_clips[i].x = 42 * i;
		frame_clips[i].y = 0;
		frame_clips[i].w = 42;
		frame_clips[i].h = 42;
	}
}

void RockHead::show_frames(SDL_Renderer* renderer)
{
	setImg(renderer, "Rock_Head/Blink (42x42).png");
	frame++;
	if(frame >= 4)
	{
		frame = 0;
	}
	SDL_Rect* current_clip = &frame_clips[frame];
	SDL_Rect renderquad = { rect.x,rect.y, 42 , 42 };
	SDL_RenderCopy(renderer, body, current_clip, &renderquad);
}
void RockHead::Doplayer_left()
{
	if (input_type_.left == 1)
	{
		rect.x = rect.x - 3;
	}
	else
	if (input_type_.right == 1 )
		{
			rect.x = rect.x + 3;
		}
}

void RockHead::Doplayer_up()
{
	if (input_type_.up == 1)
	{
		rect.y = rect.y -3;
	}
	else
		if (input_type_.down == 1)
		{
			rect.y = rect.y + 3;
		}
}

void RockHead::ImMoveType(SDL_Renderer* renderer)
{
		if (rect.x > animation_b )
		{
			input_type_.left = 1;
			input_type_.right = 0;
			/*setImg(renderer, "Rock_Head/Left Hit (42x42).png");
			frame++;
			if (frame >= 4)
			{
				frame = 0;
			}
			SDL_Rect* current_clip = &frame_clips[frame];
			SDL_Rect renderquad = { rect.x,rect.y, 42 , 42 };
			SDL_RenderCopy(renderer, body, current_clip, &renderquad);*/
		}
		else 
		if (rect.x < animation_a)
			{
				input_type_.right = 1;
				input_type_.left = 0;
				/*setImg(renderer, "Rock_Head/Right Hit (42x42).png");
				frame++;
				if (frame >= 4)
				{
					frame = 0;
				}
				SDL_Rect* current_clip = &frame_clips[frame];
				SDL_Rect renderquad = { rect.x,rect.y, 42 , 42 };
				SDL_RenderCopy(renderer, body, current_clip, &renderquad);*/
			}
}

void RockHead::ImMoveType_Up(SDL_Renderer* renderer)
{
	if (rect.y > animation_b)
	{
		input_type_.up= 1;
		input_type_.down = 0;
	}
	else
		if (rect.y < animation_a)
		{
			input_type_.up = 0;
			input_type_.down = 1;
		}
}

void RockHead::ImMoveType_UpandLeft(SDL_Renderer* renderer)
{
	if (rect.x == x_val && rect.y == y_val)
	{
		input_type_.up = 0;
		input_type_.down = 1;
		input_type_.left = 0;
		input_type_.right = 0;
	}
	else

	if(rect.x== x_val && rect.y==animation_b)
	{
		input_type_.up = 0;
		input_type_.down = 0;
		input_type_.left = 1;
		input_type_.right = 0;
	} else
	if(rect.x== animation_a && rect.y==animation_b)
	{
		input_type_.up = 1;
		input_type_.down = 0;
		input_type_.left = 0;
		input_type_.right = 0;
	}
	else
	if(rect.x== animation_a && rect.y==y_val)
	{
		input_type_.up = 0;
		input_type_.down = 0;
		input_type_.left = 0;
		input_type_.right = 1;
	}
}
void RockHead::Doplayer_upandleft()
{
	if (input_type_.up == 1)
	{
		rect.y = rect.y - 5;
		//cout << "rect.x" << " " << rect.x << " " << "rect.y" << " " << rect.y << endl;
	}
	if (input_type_.down == 1)
	{
		rect.y = rect.y + 5;
		//cout << "rect.x" << " " << rect.x << " " << "rect.y" << " " << rect.y << endl;
	}
	if (input_type_.left == 1)
	{
		rect.x = rect.x - 5;
		//cout << "rect.x" << " " << rect.x << " " << "rect.y" << " " << rect.y << endl;
	}
	if (input_type_.right == 1)
	{
		rect.x = rect.x + 5;
		//cout << "rect.x" << " " << rect.x << " " << "rect.y" << " " << rect.y << endl;
	}
}