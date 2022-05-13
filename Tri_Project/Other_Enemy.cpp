#include "Other_Enemy.h"

Other_Enemy::Other_Enemy()
{
	img_left = NULL;
	img_right = NULL;

	object = NULL;

	enemy.x = enemy.y = 0;
	enemy.w = 44;
	enemy.h = 30;

	number_frclips = 16;
	x = y = 0;
	frame_w = frame_h = 0;
	status = RIGHT;
	test.x = test.y = 0;
	test.w = w_;
	test.h = h_;
	setPos(x, y);
}

Other_Enemy::~Other_Enemy()
{
	delete[]frame_clips;
}

void Other_Enemy::inita_enemy(SDL_Renderer* renderer, int a, int b, int limitx, int limity, int k, int Status, int w, int h)
{
	frame = 0;
	x = a;
	y = b;
	limit_x = limitx;
	limit_y = limity;
	x_val = x;
	y_val = y;
	status = Status;
	test.w = frame_w = enemy.w = w;
	test.h = frame_h = enemy.h = h;
	test.x = test.y = 0;
	setPos(x, y);
	number_frclips = k;
}

SDL_Texture* Other_Enemy::LoadIMG(string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			enemy.w = loadedSurface->w;
			enemy.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	frame_w = enemy.w / number_frclips;
	frame_h = enemy.h;

	return newTexture;
}

void Other_Enemy::setIMG(SDL_Renderer* renderer, string k)
{
	if (k == "Ghost")
	{
		img_left = LoadIMG("Enemies/Ghost/Idle_left.png", renderer);
		img_right = LoadIMG("Enemies/Ghost/Idle_right.png", renderer);
	}
	else if (k == "Chicken")
	{
		img_left = LoadIMG("Enemies/Chicken/Run_left.png", renderer);
		img_right = LoadIMG("Enemies/Chicken/Run_right.png", renderer);
	}
	else if (k == "Pig")
	{
		img_left = LoadIMG("Enemies/AngryPig/Run_left.png", renderer);
		img_right = LoadIMG("Enemies/AngryPig/Run_right.png", renderer);
	}
	else if (k == "Bird")
	{
		img_left = LoadIMG("Enemies/BlueBird/Flying_left.png", renderer);
		img_right = LoadIMG("Enemies/BlueBird/Flying_right.png", renderer);
	}
	object = img_right;
}

void Other_Enemy::setPos(int a, int b)
{
	enemy.x = a;
	enemy.y = b;
}

SDL_Rect Other_Enemy::getRect_enemy()
{
	test.x = enemy.x;
	test.y = enemy.y;
	return test;
}

void Other_Enemy::set_clips()
{
	for (int i = 0; i < number_frclips; i++)
	{
		frame_clips[i].x = i * frame_w;
		frame_clips[i].y = 0;
		frame_clips[i].w = frame_w;
		frame_clips[i].h = frame_h;
	}
}

void Other_Enemy::enemy_move(SDL_Renderer* renderer)
{
	v_x += speedx;
	if (status == LEFT)
	{
		if (x - int(v_x) > limit_x) x -= int(v_x);
		else
		{
			x = limit_x;
			status = RIGHT;
			v_x = 0;
		}
	}
	else if (status == RIGHT)
	{
		if (x + int(v_x) < limit_y) x += int(v_x);
		else
		{
			x = limit_y;
			status = LEFT;
			v_x = 0;
		}
	}
	setPos(x, y);
	show_frame(renderer);
}

void Other_Enemy::show_frame(SDL_Renderer* renderer)
{
	if (status == RIGHT) object = img_right;
	else object = img_left;
	frame++;
	if (frame == number_frclips - 1) frame = 0; // ngan cho frame ko qua 3
	SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
	SDL_Rect renderquad = { x, y, frame_w, frame_h };
	SDL_RenderCopy(renderer, object, current_clips, &renderquad);
}
