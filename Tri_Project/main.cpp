#include "BaseData.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "Timer.h"
#include "Fruits.h"
#include "Stone.h"
#include <vector>
#include "CheckCollisions.h"
#include "Spike.h"

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
	bool bg = background.loadImg("Background/Pink.png", renderer);
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
	Fruits* fruits = new Fruits[7];
	fruits[0].setFruits(renderer, 240, 288, "Fruits/Cherries.png");
	fruits[1].setFruits(renderer, 288, 288, "Fruits/Melon.png");
	fruits[2].setFruits(renderer, 192, 144, "Fruits/Apple.png");
	fruits[3].setFruits(renderer, 240, 144, "Fruits/Orange.png");
	fruits[4].setFruits(renderer, 288, 144, "Fruits/Kiwi.png");
	fruits[5].setFruits(renderer, 864,  48, "Fruits/Melon.png");
	fruits[6].setFruits(renderer, 864,  96, "Fruits/Cherries.png");
	for (int i = 0; i < 7; i++)
	{
		fruits[i].set_clips();
	}
	Stone stone (renderer, 480, 384, 192, 480, "Stones/Spike_Idle.png");
	Stone stone1(renderer, 576,  96, 432, 240, "Stones/Spike_Idle.png");
	Stone stone2(renderer, 768,   0, 0, 192, "Stones/Spike_Idle.png");
	Stone stone3(renderer, 288, 144, 192, 192, "Stones/Spike_Idle.png");
	Stone stone4(renderer,  48,  48,  48, 864, "Stones/Spike_Idle.png");
	Stone stone5(renderer, 720, 288, 288, 384, "Stones/Spike_Idle.png");
	Stone stone6(renderer, 816,   0, 0, 144, "Stones/Spike_Idle.png");
	Spike spike1(renderer, 196, 416, 0, "Spikes/spike_bottom.png");
	Spike spike2(renderer, 176,  96, 1,"Spikes/spike_left.png");
	Spike spike3(renderer, 436, 272, 0,"Spikes/spike_bottom.png");
	stone.set_clips();

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
		stone6.stone_move_up(renderer, map_data);
		
		spike1.showImg(renderer);
		spike2.showImg(renderer);
		spike3.showImg(renderer);

		character.updatePlayerPosition(map_data);
		character.showImage(renderer);

		for (int i = 0; i < 7; i++)
		{

			if (checkCollision(fruits[i].getRect_fruits(), character.getRect(), 13, 4))
			{
				fruits[i].kill();
			}
			fruits[i].show_frame(renderer);
		}


		if (checkCollision(stone.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision(stone1.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision(stone2.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(720, 144);
		}
		if (checkCollision(stone3.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision(stone4.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision(stone5.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision(stone6.getRect_stone(), character.getRect(), 4, 4))
		{
			character.setPos(720, 144);
		}
		if (checkCollision_spike(spike1.getRect_spike(), character.getRect(), 0, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision_spike(spike2.getRect_spike(), character.getRect(), 1, 4))
		{
			character.setPos(0, 400);
		}
		if (checkCollision_spike(spike3.getRect_spike(), character.getRect(), 0, 4))
		{
			character.setPos(0, 400);
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