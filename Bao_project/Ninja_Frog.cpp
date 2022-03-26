#include "Ninja_Frog.h"


Ninja_Frog::Ninja_Frog()
{
	x = 434;
	y = 187;
	setPos(x, y);
	frame = 0;
	status = -1;
	dichuyen = false;
}

Ninja_Frog::~Ninja_Frog()
{
}


Ninja_Frog::Ninja_Frog(SDL_Renderer* renderer)
{
	x = 434;
	y = 187;
	setPos(x, y);
	frame = 0;
	setImg(renderer, "Ninja_Frog_Fall.png");
	input_type.idle_l = 1;
	status = Idle_left;
}

void Ninja_Frog::setImg(SDL_Renderer* renderer, string path)
{
	body = BG::loadTexture(renderer, path);
}

void Ninja_Frog::setPos(int a, int b)
{
	ninja_frog.x = a;
	ninja_frog.y = b;
}

string xoa_string(string k, char r)
{
	string s = "";
	for (int i = 0; i < k.length(); i++)
	{
		if (k[i] != r) s += k[i];
	}
	//if (s == "") s += r;
	return s;
}

void Ninja_Frog::keyboard_input(SDL_Event e, SDL_Renderer* renderer)
{
	if (e.type == SDL_KEYDOWN /*&& e.key.repeat == 0*/) // SDL_KEYDWON khi chung ta nhan phim xuong
	{
		dichuyen = true;

		switch (e.key.keysym.sym)
		{
		case SDLK_UP: // phan khac source
		{

			input_type.up = 1;
			input_type.idle_l = 0;
			input_type.idle_r = 0;
			direct1 += 'u';

			std::cout << direct1 << '\n';
			break;
		}
		case SDLK_DOWN: // phan khac source
		{
			input_type.down = 1;
			input_type.idle_l = 0;
			input_type.idle_r = 0;
			direct1 += 'd';
			break;
			std::cout << direct1 << '\n';
		}
		case SDLK_LEFT:
		{
			input_type.left = 1; // luu trang thai left
			if (input_type.right != 1)
			{
				status = Walk_left; // luu trang thai left
				direct1 += 'l';
				cout << direct1 << '\n';
			}
			break;
		}
		case SDLK_RIGHT:
		{
			input_type.right = 1; // luu trang thai right 
			if (input_type.left != 1)
			{
				status = Walk_right; // luu trang thai right
				direct1 += 'r';
				cout << direct1 << '\n';
			}
			break;
		}
		}
	}
	else if (e.type == SDL_KEYUP /*&& e.key.repeat == 0*/) // khi chung ta khong giu phim ra 
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			if (input_type.right != 1)
			{
				status = Idle_left;
				input_type.idle_l = 1;
			}
			input_type.left = 0;
			string s = xoa_string(direct1, 'l');
			direct1.resize(s.length());
			direct1 = s;
			cout << "xoa_l " << direct1 << '\n';

			break;
		}
		case SDLK_RIGHT:
		{
			if (input_type.left != 1)
			{
				status = Idle_right;
				input_type.idle_r = 1;
			}
			input_type.right = 0;
			string s = xoa_string(direct1, 'r');
			direct1.resize(s.length());
			
			direct1 = s;
			cout << "xoa_r " << direct1 << '\n';
			break;
		}
		case SDLK_DOWN:// phan khac source
		{
			if (input_type.right = 1 )
			{
				input_type.idle_r = 1;
				input_type.right = 0;
			}
			if (input_type.left = 1)
			{
				input_type.idle_l = 1;
				input_type.left = 0;
			}
			input_type.down = 0;
			string s = xoa_string(direct1, 'd');
			direct1.resize(s.length());
			direct1 = s;
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
			input_type.up = 0;
			string s = xoa_string(direct1, 'u');
			direct1.resize(s.length());
			direct1 = s;
			break;
		}
		}
		if (input_type.down == 0 && input_type.right == 0 && input_type.left == 0 && input_type.up == 0) dichuyen = false;
	}
}

void Ninja_Frog::handle_move()
{
	if (dichuyen)
	{
		if (/*direct1[direct1.length() - 1] == 'l'*/ input_type.left == 1 && input_type.right == 0)
		{
			if (x >= 9 + 32) x -= 8;
		}
		if (/*direct1[direct1.length() - 1] == 'r'*/ input_type.right == 1 && input_type.left == 0 )
		{
			if (x <= 503 - 32) x += 8;
		}
		if (/*direct1[direct1.length() - 1] == 'u'*/ input_type.up == 1 )
		{
			if (y >= 0 + 32 + 8) y -= 24;
		}
		if (/*direct1[direct1.length() - 1] == 'd'*/ input_type.down == 1 )
		{
			if (y <= 288 - 8 - 32) y += 8;
		}
	}
	setPos(x, y);
}

void Ninja_Frog::set_clips()
{
	for (int i = 0; i < 11; i++)
	{
		frame_clips[i].x = i * 32;
		frame_clips[i].y = 0;
		frame_clips[i].w = 32;
		frame_clips[i].h = 32;
	}
}

void Ninja_Frog::show_frame(SDL_Renderer* renderer)
{
	//cout << "status:" << status << '\n';
	if (status == Walk_right )
	{
		// in ra anh neu nhan right
		setImg(renderer, "Terrain_Project/Run_(32x32).png");
	}
	else if (status == Walk_left )
	{
		// in ra anh neu nhan left

		setImg(renderer, "Terrain_Project/Run_(32x32)_l.png");
	}
	else if (status == Idle_right)// phan khac source
	{
		setImg(renderer, "Terrain_Project/Idle_(32x32).png");
	}
	else if( status == Idle_left)// phan khac source
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
	SDL_Rect renderquad = { ninja_frog.x, ninja_frog.y, 32, 32 };
	SDL_RenderCopy(renderer, body, current_clips, &renderquad);
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




