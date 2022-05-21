#pragma once
#ifndef INIT_H
#define INIT_H

#include "BaseData.h"
#include "BaseObject.h"
#include "Text.h"
using namespace std;

bool init(SDL_Window *window, SDL_Renderer* renderer)
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

			if (TTF_Init() == -1)
			{
				success = false;
			}
		}
	}
	return success;
}

bool initRenderer( SDL_Window *window, SDL_Renderer * renderer)
{
	bool success;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		success = false;
	}
	else
	{
		success = true;
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	}
	return success;
}

bool loadBackground( BaseOject &background, SDL_Renderer* renderer)
{
	bool bg = background.loadImg("Images/Background/Pink.png", renderer);
	if (!bg)
	{
		return false;
	}
	return true;
}

bool loadBackground2(BaseOject& background2, SDL_Renderer* renderer)
{
	bool bg2 = background2.loadImg("Images/Background/Blue.png", renderer);
	if (!bg2)
	{
		return false;
	}
	return true;
}

bool loadInstruction(BaseOject& instruction, SDL_Renderer* renderer)
{
	bool ins = instruction.loadImg("Images/Menu/instruction.png", renderer);
	if (!ins)
	{
		return false;
	}
	return true;
}

bool loadGameOver(BaseOject& game_over, SDL_Renderer* renderer)
{
	bool end = game_over.loadImg("Images/Game over/game_over.png", renderer);
	if (!end)
	{
		return false;
	}
	return true;
}

bool loadMenu(BaseOject& menu, SDL_Renderer* renderer)
{
	bool home = menu.loadImg("Images/Menu/menu.png", renderer);
	if (!home)
	{
		return false;
	}
	return true;
}

bool loadMapChoose(BaseOject& map_choose, SDL_Renderer* renderer)
{
	bool choose = map_choose.loadImg("Images/Menu/map_choose.png", renderer);
	if (!choose)
	{
		return false;
	}
	return true;
}

bool loadWin(BaseOject& win, SDL_Renderer* renderer)
{
	bool check_win = win.loadImg("Images/Win/victory.png", renderer);
	if (!check_win)
	{
		return false;
	}
	return true;
}

bool loadSound()
{
	bool success = true;
	game_music = Mix_LoadMUS("Adv-music/level/Level-04.wav");
	menu_music = Mix_LoadMUS("Adv-music/menu/menu.wav");
	victory_music = Mix_LoadMUS("Adv-music/victory/victory.wav");
	gameover_music = Mix_LoadMUS("Adv-music/lose/game_over.wav");
	soundEffect[jump_sound] = Mix_LoadWAV("Adv-SFX/Jump 4.wav");
	soundEffect[collect_sound] = Mix_LoadWAV("Adv-SFX/Collect 5.wav");
	soundEffect[hitSpike_sound] = Mix_LoadWAV("Adv-SFX/Hit 1.wav");
	soundEffect[hitRock_sound] = Mix_LoadWAV("Adv-SFX/Hit 5.wav");
	soundEffect[extra_life] = Mix_LoadWAV("Adv-SFX/Extra Life.wav");

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
	if (menu_music == NULL)
	{
		success = false;
	}
	if (gameover_music == NULL)
	{
		success = false;
	}
	return success;
}

void close(SDL_Window *window, SDL_Renderer *renderer, LTexture &gPromptTextTexture, LTexture& gInputTextTexture, BaseOject & background)
{
	gPromptTextTexture.free();
	gInputTextTexture.free();
	for (int i = 0; i < sound_total; i++)
	{
		Mix_FreeChunk(soundEffect[i]);
		soundEffect[i] = NULL;
	}

	Mix_FreeMusic(game_music);
	game_music = NULL;

	Mix_FreeMusic(menu_music);
	menu_music = NULL;

	background.Free();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	TTF_CloseFont(gFont);
	gFont = NULL;

	TTF_CloseFont(gFontN);
	gFontN = NULL;

	TTF_CloseFont(fontText);
	fontText = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool loadMedia(LTexture& gPromptTextTexture, SDL_Renderer *renderer)
{
	bool success = true;

	// load front chu
	gFont = TTF_OpenFont("Fonts/SHOWG.ttf", 40);
	if (gFont == NULL)
	{
		cout << "Failed to load lazy font! SDL_ttf Error:" << TTF_GetError() << endl;
		success = false;
	}
	else
	{
		//Render the prompt
		SDL_Color textColor = { 250, 128, 114 };
		if (!gPromptTextTexture.loadFromRenderedText("Enter your Name:", textColor, gFont, renderer))
		{
			cout << "Failed to render prompt text!" << endl;
			success = false;
		}
	}

	return success;
}
bool loadCharacterChoose( BaseOject &character_choose, SDL_Renderer* renderer)
{
	bool check = character_choose.loadImg("Images/Character_choose/select.png", renderer);
	if (!check)
	{
		return false;
	}
	return true;
}
bool loadMapPass1(BaseOject & map_pass1, SDL_Renderer* renderer)
{
	bool check = map_pass1.loadImg("Images/Map_pass/map_pass1.png", renderer);
	if (!check)
	{
		return false;
	}
	return true;
}

bool loadMapPass2(BaseOject & map_pass2, SDL_Renderer* renderer)
{
	bool check = map_pass2.loadImg("Images/Map_pass/map_pass2.png", renderer);
	if (!check)
	{
		return false;
	}
	return true;
}

#endif // !INIT_H
