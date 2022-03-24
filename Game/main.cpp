#include "BaseData.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "Timer.h"
using namespace std;

BaseOject background;

bool init()
{
	bool success = true;
	int ref = SDL_Init(SDL_INIT_VIDEO);
	if (ref < 0)
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
			SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
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
	gm.loadMap("map.dat.txt");
	gm.loadTiles(renderer);

	MainObject character;
	character.LoadIMG("Character/Idle_right.png", renderer);
	character.setClips();

	bool quit = false;
	while (!quit)
	{
		timer.start();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			character.handleEvents(event, renderer);
		}

		SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(renderer);

		background.Render(renderer, NULL);
		gm.DrawMap(renderer);
		Map map_data = gm.getMap();
			
		character.doPlayer(map_data);
		character.show(renderer);
		SDL_RenderPresent(renderer);

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