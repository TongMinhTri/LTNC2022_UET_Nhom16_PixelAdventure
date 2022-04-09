#include "BaseData.h"
#include "BaseObject.h"
#include "Map.h"
#include "MainObject.h"
#include "Timer.h"
#include "Fruits.h"
#include "Stone.h"
#include "CheckCollisions.h"
#include "Spike.h"
#include "Checkpoints.h"

using namespace std;

BaseOject background;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
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

bool loadSound()
{
	bool success = true;
	game_music = Mix_LoadMUS("Adv-music/level/Level-01.wav");
	soundEffect[jump_sound] = Mix_LoadWAV("Adv-SFX/Jump 4.wav");
	soundEffect[collect_sound] = Mix_LoadWAV("Adv-SFX/Collect 5.wav");
	soundEffect[hitSpike_sound] = Mix_LoadWAV("Adv-SFX/Hit 1.wav");
	soundEffect[hitRock_sound] = Mix_LoadWAV("Adv-SFX/Hit 5.wav");

	for (int i = 0; i < sound_total; i++)
	{
		if (soundEffect[i] == NULL)
		{
			success = false;
			break;
		}
	}

	if (game_music == NULL)
	{
		success = false;
	}

	return success;
}

void close()
{
	for (int i = 0; i < sound_total; i++)
	{
		Mix_FreeChunk(soundEffect[i]);
		soundEffect[i] = NULL;
	}

	Mix_FreeMusic(game_music);
	game_music = NULL;

	background.Free();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	Mix_Quit();
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
	if (!loadSound())
	{
		return -1;
	}

	Mix_PlayMusic(game_music, -1);

	GameMap gm;
	gm.loadTiles(renderer);

	Checkpoints point[3];
	point[0].set_checkpoints(renderer, 912, 384, 8,48, "Checkpoints/End/End(48x48).png");
	point[1].set_checkpoints(renderer, 0, 368, 17,64, "Checkpoints/Start/Start (Moving) (64x64).png");
	point[2].set_checkpoints(renderer, 624, 96, 26,48, "Checkpoints/Checkpoint/Checkpoint (Flag Out) (48x48).png");
	for(int i=0;i<=2;i++)
		point[i].set_clips();

	MainObject character;
	character.setIMG(renderer);
	character.setClips();

	bool quit = false;
	Fruits* fruits = new Fruits[9];
	fruits[0].setFruits(renderer, 240, 288, "Fruits/Cherries.png");
	fruits[1].setFruits(renderer, 288, 288, "Fruits/Melon.png");
	fruits[2].setFruits(renderer, 192, 144, "Fruits/Apple.png");
	fruits[3].setFruits(renderer, 240, 144, "Fruits/Orange.png");
	fruits[4].setFruits(renderer, 288, 144, "Fruits/Kiwi.png");
	fruits[5].setFruits(renderer, 864, 48, "Fruits/Melon.png");
	fruits[6].setFruits(renderer, 864, 96, "Fruits/Cherries.png");
	fruits[7].setFruits(renderer, 576, 144, "Fruits/Apple.png");
	fruits[8].setFruits(renderer, 432, 144, "Fruits/Melon.png");
	for (int i = 0; i < 9; i++)
	{
		fruits[i].set_clips();
	}
	Stone stone[7];
	stone[0].init_stone(renderer, 480, 384, 192, 480, "Stones/Spike_Idle.png");
	stone[1].init_stone(renderer, 576, 96, 432, 240, "Stones/Spike_Idle.png");
	stone[2].init_stone(renderer, 768, 0, 0, 192, "Stones/Spike_Idle.png");
	stone[3].init_stone(renderer, 288, 144, 192, 192, "Stones/Spike_Idle.png");
	stone[4].init_stone(renderer, 48, 48, 48, 864, "Stones/Spike_Idle.png");
	stone[5].init_stone(renderer, 720, 288, 288, 384, "Stones/Spike_Idle.png");
	stone[6].init_stone(renderer, 816, 0, 0, 144, "Stones/Spike_Idle.png");
	stone[0].set_clips();

	Spike spike[5];
	spike[0].set_spike(renderer, 196, 416, 0, "Spikes/spike_bottom.png");
	spike[1].set_spike(renderer, 48, 144, 1, "Spikes/spike_right.png");
	spike[2].set_spike(renderer, 176, 96, 2, "Spikes/spike_left.png");
	spike[3].set_spike(renderer, 436, 272, 0, "Spikes/spike_bottom.png");
	spike[4].set_spike(renderer, 672, 336, 1, "Spikes/spike_right.png");

	while (!quit)
	{
		timer.start();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			character.handleMovement(event, renderer, soundEffect);
		}

		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		background.Render(renderer, NULL);
		gm.DrawMap(renderer);
		Map map_data = gm.getMap();

		point[0].showImg(renderer);
		point[1].showImg(renderer);
		point[2].showImg(renderer);
		
		stone[0].stone_move(renderer, map_data);
		stone[1].DoStone_Circle();
		stone[1].Stone_Move_Circle(renderer, map_data);
		stone[2].stone_move_up(renderer, map_data);
		stone[3].DoStone_Circle();
		stone[3].Stone_Move_Circle(renderer, map_data);
		stone[4].stone_move(renderer, map_data);
		stone[5].stone_move_up(renderer, map_data);
		stone[6].stone_move_up(renderer, map_data);

		for (int i = 0; i < 5; i++)
		{
			spike[i].showImg(renderer);
		}

		character.updatePlayerPosition(map_data);
		character.showImage(renderer);

		for (int i = 0; i < 9; i++)
		{

			if (checkCollision(fruits[i].getRect_fruits(), character.getRect(), 13, 4) && fruits[i].alive == true)
			{
				fruits[i].kill();
				Mix_PlayChannel(-1, soundEffect[collect_sound], 0);
			}
			fruits[i].showImg(renderer);
		}


		for (int i = 0; i < 7; i++)
		{
			if (checkCollision(stone[i].getRect_stone(), character.getRect(), 4, 4))
			{
				Mix_PlayChannel(-1, soundEffect[hitRock_sound], 0);
				character.setPos(0, 400);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (checkCollision_spike(spike[i].getRect_spike(), character.getRect(), i % 3, 4))
			{
				Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
				character.setPos(0, 400);
			}
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