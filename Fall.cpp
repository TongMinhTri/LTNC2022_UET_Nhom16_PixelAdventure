#include "Fall.h"

Fall::Fall(SDL_Renderer *renderer)
{ 
	x = SCREEN_WIDTH/2;
	y = SCREEN_HEIGHT*3/4;
	setPos(x, y);
	setImg(renderer, "Fall.png");
}

void Fall::move(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym)
		{
			case SDLK_UP:
			{
				cout << "Up" << '\n';
				Gety(-20);
				break;
			}
			case SDLK_DOWN:
			{
				cout << "Down" << '\n';
				Gety(20);
				break;
			}
			case SDLK_LEFT:
			{
				cout << "Left" << '\n';
				Getx(-20);
				break;
			}
			case SDLK_RIGHT:
			{
				cout << "Right" << '\n';
				Getx(20);
				break;
			}
		}
	}
}

Fall::~Fall()
{
}
