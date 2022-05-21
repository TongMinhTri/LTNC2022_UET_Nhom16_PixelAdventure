#include "Bullet.h"

Bullet::Bullet()
{
	x_pos = 0;
	y_pos = 0;
	isMove = true;
	speed_bullet = 2;
	setImg(renderer,"Images/Enemies/Trunk/Bullet.png");
	bullet.x = 240;
	bullet.y = 432;
	bullet.w = 16;
	bullet.h = 16;
}

Bullet::~Bullet()
{
}

void Bullet::set_bullet(SDL_Renderer* renderer,int x_, int y_,string path)
{
	x_pos = x_;
	y_pos = y_;
	isMove = true;
	speed_bullet = 2;
	test.x = test.y = test.w = test.h = 0;
	bullet.w = 16;
	bullet.h = 16;
	setImg(renderer, path);
	setPos(x_, y_);
}

void Bullet::show(SDL_Renderer* renderer)
{
	if(isMove == true)
	SDL_RenderCopy(renderer, body, NULL, &bullet);
}

void Bullet::Free()
{
	SDL_DestroyTexture(body);
	body = NULL;
}

void Bullet::fire_left()
{
	if(isMove == true)
		bullet.x -= 10;
	if (bullet.x - 10 <= 192 )
	{
		bullet.x = 192;
		isMove = false;
	}
}
void Bullet::fire_right()
{
	if (isMove == true)
		bullet.x += 10;
	if (bullet.x + 10 >= 528)
	{
		bullet.x = 528;
		isMove = false;
	}
}

void Bullet::setStatus(bool isMove_)
{
	isMove = isMove_;
}

void Bullet::setImg(SDL_Renderer* renderer, string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			bullet.w = loadedSurface->w;
			bullet.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	body = newTexture;
}

void Bullet::setPos(int x_, int y_)
{
	bullet.x = x_;
	bullet.y = y_;
	isMove = true;
}

SDL_Rect Bullet::getRect_bullet()
{
	test.x = bullet.x;
	test.y = bullet.y;
	test.w = test.h = 16;
	return test;
}
