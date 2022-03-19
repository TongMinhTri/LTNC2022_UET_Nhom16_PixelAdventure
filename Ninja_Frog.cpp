#include "Ninja_Frog.h"


Ninja_Frog::Ninja_Frog()
{
}

Ninja_Frog::~Ninja_Frog()
{
}

Ninja_Frog::Ninja_Frog(SDL_Renderer *renderer)
{ 
	x = 434;
	y = 187;
	setPos(x, y);
	frame = 0;
	status = -1;
	setImg(renderer, "Fall.png");
}

void Ninja_Frog::move(SDL_Event e, SDL_Renderer* renderer)
{
	if (e.type == SDL_KEYDOWN) // SDL_KEYDWON khi chung ta nhan phim xuong
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_UP: // phan khac source
			{
				std::cout << "Up" << '\n';
				if (rect.y - 64 >= 22)
					Gety(-64);
				else
					Gety(-1 * ( rect.y - 64) );
				std::cout << rect.y << " ";
				break;
			}
			case SDLK_DOWN: // phan khac source
			{
				std::cout << "Down" << '\n';
				Gety(min(235 - rect.y, rect.y + 64));
				break;
				std::cout << rect.y << " ";
			}
			case SDLK_LEFT:
			{
				status = Walk_left; // luu trang thai left
				input_type.left = 1; // luu trang thai left
				input_type.right = 0;
				input_type.idle_l = 0;
				input_type.idle_r = 0;
				Getx(-1*10); 
				break;
			}
			case SDLK_RIGHT:
			{
				status = Walk_right; // luu trang thai right
				input_type.right = 1; // luu trang thai right 
				input_type.left = 0;
				input_type.idle_l = 0;
				input_type.idle_r = 0;
				Getx(10);
				break;
			}
		}
	}
	else if (e.type == SDL_KEYUP) // khi chung ta khong giu phim ra 
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			{
				status = Idle_left;
				input_type.idle_l = 1;
				input_type.left = 0;
				break;
			}
			case SDLK_RIGHT:
			{
				status = Idle_right;
				input_type.idle_r = 1;
				input_type.right = 0;
				break;
			}
			case SDLK_DOWN:// phan khac source
			{
				if (input_type.right = 1)
				{
					input_type.idle_r = 1;
					input_type.right = 0;
				}
				if (input_type.left = 1)
				{
					input_type.idle_l = 1;
					input_type.left = 0;
				}
				break;
			}
			case SDLK_UP:// phan khac source
			{
				if (input_type.right = 1)
				{
					input_type.idle_r = 1;
					input_type.right = 0;
				}
				if (input_type.left = 1)
				{
					input_type.idle_l = 1;
					input_type.left = 0;
				}
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
		frame_clips[i].h = 32;
	}
}

void Ninja_Frog::show_frame(SDL_Renderer* renderer)
{
	if (status == Walk_right)
	{
		// in ra anh neu nhan right
		setImg(renderer, "Terrain_Project/Run_(32x32).png");
	}
	else if (status == Walk_left)
	{
		// in ra anh neu nhan left
		setImg(renderer, "Terrain_Project/Run_(32x32)_l.png");
	}
	else if( status == Idle_right )// phan khac source
	{
		setImg(renderer, "Terrain_Project/Idle_(32x32).png");
	}
	else // phan khac source
	{
		setImg(renderer, "Terrain_Project/Idle_(32x32)_l.png");
	}
	if (input_type.left == 1 || input_type.right == 1 || input_type.idle_l == 1 || input_type.idle_r == 1) // neu trang thai truoc trung voi trang thai sau thi ++ frame
	{
		frame++;
	}
	else frame = 0; 
	if (frame == 11) frame = 0; // ngan cho frame ko qua 11 
	SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
	SDL_Rect renderquad = { rect.x, rect.y, 64, 64 }; 
	SDL_RenderCopy(renderer, body, current_clips, &renderquad );
}

/* phan source
void Ninja_Frog::move(SDL_Event e, SDL_Renderer* renderer)
{
	if (e.type == SDL_KEYDOWN) // SDL_KEYDWON khi chung ta nhan phim xuong
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			{
				status = Walk_left; // luu trang thai left
				input_type.left = 1; // luu trang thai left
				input_type.right = 0;
				Getx(-1*8);
				break;
			}
			case SDLK_RIGHT:
			{
				status = Walk_right; // luu trang thai right
				input_type.right = 1; // luu trang thai right
				input_type.left = 0;
				Getx(8);
				break;
			}
		}
	}
	else if (e.type == SDL_KEYUP) // khi chung ta khong giu phim ra
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_LEFT:
			{
				input_type.left = 0;
				break;
			}
			case SDLK_RIGHT:
			{
				input_type.right = 0;
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
		frame_clips[i].h = 32;
	}
}

void Ninja_Frog::show_frame(SDL_Renderer* renderer)
{
	if (status == Walk_right)
	{
		// in ra anh neu nhan right
		setImg(renderer, "Terrain_Project/Run_(32x32).png");
	}
	else if (status == Walk_left)
	{
		// in ra anh neu nhan left
		setImg(renderer, "Terrain_Project/Run_(32x32)_l.png");
	}
	if (input_type.left == 1 || input_type.right == 1 ) // neu trang thai truoc trung voi trang thai sau thi ++ frame
	{
		frame++;
	}
	else frame = 0;
	if (frame == 11) frame = 0; // ngan cho frame ko qua 11
	SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
	SDL_Rect renderquad = { rect.x, rect.y, 32, 32 };
	SDL_RenderCopy(renderer, body, current_clips, &renderquad );
}
*/




