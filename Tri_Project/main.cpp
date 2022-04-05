#include "BaseData.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "Timer.h"
#include "Fruits.h"
#include "Stone.h"
#include <vector>

using namespace std;

BaseOject background;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		success = false;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow("Pixel Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		success = false;
	}
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			success = false;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false;
			}
		}
	}
	return success;
}


bool loadBackground()
{
	bool bg = background.loadImg("Pink.png", renderer);
	if (!bg)
	{
		return false;
	}
	return true;
}


void close()
{
	background.Free();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(SDL_Rect, SDL_Rect, int A, int B);

int main(int argc, char* args[])
{
	Time timer;

	if (!init())
	{
		return -1;
	}
	if (!loadBackground())
	{
		return -1;
	}


	GameMap gm;
	gm.loadTiles(renderer);

	MainObject character;
	character.setIMG(renderer);
	character.setClips();

	bool quit = false;
	Fruits* kiwi = new Fruits[5];
	kiwi[0].setFruits(renderer, 240, 288, "Fruits/Cherries_48.png");
	kiwi[1].setFruits(renderer, 288, 288, "Fruits/Cherries_48.png");
	kiwi[2].setFruits(renderer, 192, 144, "Fruits/Cherries_48.png");
	kiwi[3].setFruits(renderer, 240, 144, "Fruits/Cherries_48.png");
	kiwi[4].setFruits(renderer, 288, 144, "Fruits/Cherries_48.png");
	for (int i = 0; i < 5; i++)
	{
		kiwi[i].set_clips();
		kiwi[i].setImg(renderer, "Fruits/Cherries_48.png");
	}
	Stone stone(renderer, 480, 384,192,480, "Spike_Idle.png");
	stone.set_clips();
	Stone stone1(renderer, 576, 96, 432, 240, "Spike_Idle.png");
	//stone1.set_clips();
	Stone stone2(renderer, 768, 48,48,192, "Spike_Idle.png");
	Stone stone3(renderer,288,144,192,192,"Spike_Idle.png");
	Stone stone4(renderer, 48, 48,48,864, "Spike_Idle.png");
	Stone stone5(renderer, 720, 288, 288, 384, "Spike_Idle.png");

	while (!quit)
	{
		timer.start();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			character.handleMovement(event, renderer);
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		background.Render(renderer, NULL);
		gm.DrawMap(renderer);
		Map map_data = gm.getMap();

		stone.stone_move(renderer, map_data);

		stone1.DoStone_Circle();
		stone1.Stone_Move_Circle(renderer, map_data);
		stone2.stone_move_up(renderer, map_data);
		stone3.DoStone_Circle();
		stone3.Stone_Move_Circle(renderer, map_data);
		stone4.stone_move(renderer, map_data);
		stone5.stone_move_up(renderer, map_data);
		
		character.updatePlayerPosition(map_data);
		character.showImage(renderer);

		for (int i = 0; i < 5; i++)
		{

			if (checkCollision(kiwi[i].getRect_fruits(), character.getRect(), 13, 4 ) )
			{
				kiwi[i].kill();
				SDL_Rect rest = character.getRect();
			}
			kiwi[i].show_frame(renderer);
		}


		if (checkCollision(stone.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
			SDL_Rect rest = character.getRect();
		}
		if (checkCollision(stone1.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
			SDL_Rect rest = character.getRect();
		}
		if (checkCollision(stone2.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
			SDL_Rect rest = character.getRect();
		}
		if (checkCollision(stone3.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
			SDL_Rect rest = character.getRect();
		}
		if (checkCollision(stone4.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
			SDL_Rect rest = character.getRect();
		}
		if (checkCollision(stone5.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
			SDL_Rect rest = character.getRect();
		}


		SDL_RenderPresent(renderer);

		// Xu ly thoi gian va FPS

		int real_time = timer.get_ticks();
		int time_one_frame = 1000 / FPS;

		if (real_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_time;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}
	}

	close();
	return 0;
}

bool checkCollision(SDL_Rect a, SDL_Rect b, int A, int B)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x+A;
	rightA = a.x + a.w-A;
	topA = a.y+A;
	bottomA = a.y + a.h-A;

	//Calculate the sides of rect B
	leftB = b.x+B;
	rightB = b.x + b.w-B;
	topB = b.y + B;
	bottomB = b.y + b.h;
	if (bottomB > topA && rightB > leftA && rightB - b.w < leftA && bottomB - b.w < topA) return true;
	if (bottomB > topA && rightA > leftB && rightA - b.w < leftB && bottomB - b.w < topA) return true;
	if (bottomA > topB && rightB > leftA && rightB - b.w < leftA && bottomA - b.w < topB) return true;
	if (bottomA > topB && rightA > leftB && rightA - b.w < leftB && bottomA - b.w < topB) return true;

	return false;
}