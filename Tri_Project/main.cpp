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
#include "Text.h"
#include "TextScore.h"
#include "Heart.h"
#include "Update_dataplayers.h"

using namespace std;

BaseOject background;
BaseOject instruction;
BaseOject game_over;

LTexture gPromptTextTexture;
LTexture gInputTextTexture;

int Game_Status = ENTER_NAME;

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

			if (TTF_Init() == -1)
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

bool loadInstruction()
{
	bool ins = instruction.loadImg("Instruction/instruction.png", renderer);
	if (!ins)
	{
		return false;
	}
	return true;
}

bool loadGameOver()
{
	bool end = game_over.loadImg("Game over/game_over.png", renderer);
	if (!end)
	{
		return false;
	}
	return true;
}

bool loadSound()
{
	bool success = true;
	game_music = Mix_LoadMUS("Adv-music/level/Level-04.wav");
	menu_music = Mix_LoadMUS("Adv-music/menu.wav");
	soundEffect[jump_sound] = Mix_LoadWAV("Adv-SFX/Jump 4.wav");
	soundEffect[collect_sound] = Mix_LoadWAV("Adv-SFX/Collect 5.wav");
	soundEffect[hitSpike_sound] = Mix_LoadWAV("Adv-SFX/Hit 1.wav");
	soundEffect[hitRock_sound] = Mix_LoadWAV("Adv-SFX/Hit 5.wav");
	soundEffect[extra_life] = Mix_LoadWAV("Adv-SFX/Extra Life.wav");
	soundEffect[lose_sound] = Mix_LoadWAV("Adv-music/lose/game_over.wav");

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

	return success;
}

void close()
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

	background.Free();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	TTF_CloseFont(gFont);
	gFont = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool loadMedia()
{
	bool success = true;

	//Open the font
	// load front chu
	gFont = TTF_OpenFont("SHOWG.ttf", 40);
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


int main(int argc, char* args[])
{
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

	string inputText = "";
	int sco = 0;
	int heart_game = 0;
	bool put_data = false;

	if (Game_Status == ENTER_NAME || Game_Status == INSTRUCTION)
	{
		Mix_PlayMusic(menu_music, -1);
	}

	if (Game_Status == ENTER_NAME)
	{
		if (!loadMedia())
		{
			return -1;
		}
		else
		{
			bool quit = false;
			SDL_Color textColor = { 0, 128, 128 };
			gFontN = TTF_OpenFont("SHOWG.ttf", 30);
			gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, gFontN, renderer);

			//Enable text input
			SDL_StartTextInput();

			while (!quit)
			{
				bool renderText = false;

				while (SDL_PollEvent(&e_name) != 0)
				{
					//User requests quit
					if (e_name.type == SDL_QUIT)
					{
						quit = true;
					}
					//Special key input
					else if (e_name.type == SDL_KEYDOWN)
					{
						//Handle backspace
						if (e_name.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
						{
							//lop off character
							inputText.pop_back();
							renderText = true;
						}
						//Handle copy
						else if (e_name.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
						{
							SDL_SetClipboardText(inputText.c_str());
						}
						//Handle paste
						else if (e_name.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
						{
							inputText = SDL_GetClipboardText();
							renderText = true;
						}
						else if (e_name.key.keysym.sym == SDLK_RETURN)
						{
							Game_Status = INSTRUCTION;
						}
					}
					//Special text input event
					else if (e_name.type == SDL_TEXTINPUT)
					{
						//Not copy or pasting
						if (!(SDL_GetModState() & KMOD_CTRL && (e_name.text.text[0] == 'c' || e_name.text.text[0] == 'C' || e_name.text.text[0] == 'v' || e_name.text.text[0] == 'V')))
						{
							//Append character
							inputText += e_name.text.text;
							renderText = true;
						}
					}
				}
				if (inputText.length() >= 20) inputText.resize(20);
				//Rerender text if needed
				if (renderText)
				{
					//Text is not empty
					if (inputText != "")
					{
						//Render new text
						gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, gFontN, renderer);
					}
					//Text is empty
					else
					{
						//Render space texture
						gInputTextTexture.loadFromRenderedText(" ", textColor, gFontN, renderer);
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(renderer);

				//Render text textures
				gPromptTextTexture.render((SCREEN_WIDTH - gPromptTextTexture.getWidth()) / 2, 204, renderer);
				gInputTextTexture.render((SCREEN_WIDTH - gInputTextTexture.getWidth()) / 2, 254, renderer);

				//Update screen
				SDL_RenderPresent(renderer);
				if (Game_Status == INSTRUCTION)
				{
					goto Instruction;
				}
			}

			//Disable text input
			SDL_StopTextInput();
		}
	}
	if (Game_Status == INSTRUCTION)
	{
	Instruction:
		if (!loadInstruction())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&e_ins) != 0)
			{
				if (e_ins.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e_ins.type == SDL_KEYDOWN || e_ins.type == SDL_MOUSEBUTTONDOWN)
				{
					Game_Status = PLAY;
				}
			}
			instruction.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
			if (Game_Status == PLAY)
			{
				Mix_FreeMusic(menu_music);
				menu_music = NULL;
				instruction.Free();
				goto Play;
			}
		}
	}
	if (Game_Status == PLAY || Game_Status == GAME_OVER)
	{
	Play:
		if (Game_Status == GAME_OVER)
		{
			game_music = Mix_LoadMUS("Adv-music/level/Level-04.wav");
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				return -1;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
			if (!loadBackground())
			{
				return -1;
			}
			Game_Status = PLAY;
		}

		put_data = false;
		sco = 0;

		Time timer;
		soundEffect[lose_sound] = Mix_LoadWAV("Adv-music/lose/game_over.wav");

		Mix_PlayMusic(game_music, -1);

		GameMap gm;
		gm.loadTiles(renderer);


		Checkpoints* point = new Checkpoints[3];
		point[0].set_checkpoints(renderer, 912, 432,  8, 48, "Checkpoints/End/End(48x48).png");
		point[1].set_checkpoints(renderer,   0, 416, 17, 64, "Checkpoints/Start/Start (Moving) (64x64).png");
		point[2].set_checkpoints(renderer, 624, 144, 26, 48, "Checkpoints/Checkpoint/Checkpoint (Flag Out) (48x48).png");
		for (int i = 0; i <= 2; i++)
			point[i].set_clips();

		MainObject character;
		character.setIMG(renderer);
		character.setClips();
		bool quit = false;

		Fruits* fruits = new Fruits[9];
		fruits[0].setFruits(renderer, 240, 336, "Fruits/Cherries.png");
		fruits[1].setFruits(renderer, 288, 336, "Fruits/Melon.png");
		fruits[2].setFruits(renderer, 192, 192, "Fruits/Apple.png");
		fruits[3].setFruits(renderer, 240, 192, "Fruits/Orange.png");
		fruits[4].setFruits(renderer, 288, 192, "Fruits/Kiwi.png");
		fruits[5].setFruits(renderer, 864,  96, "Fruits/Melon.png");
		fruits[6].setFruits(renderer, 864, 144, "Fruits/Cherries.png");
		fruits[7].setFruits(renderer, 576, 192, "Fruits/Apple.png");
		fruits[8].setFruits(renderer, 432, 192, "Fruits/Melon.png");
		for (int i = 0; i < 9; i++)
		{
			fruits[i].set_clips();
		}

		Stone* stone = new Stone[7];
		stone[0].init_stone(renderer, 480, 432, 192, 480, "Stones/Spike_Idle.png");
		stone[1].init_stone(renderer, 576, 144, 432, 288, "Stones/Spike_Idle.png");
		stone[2].init_stone(renderer, 768,  48,  48, 240, "Stones/Spike_Idle.png");
		stone[3].init_stone(renderer, 288, 192, 192, 240, "Stones/Spike_Idle.png");
		stone[4].init_stone(renderer,  48,  96,  48, 864, "Stones/Spike_Idle.png");
		stone[5].init_stone(renderer, 720, 336, 336, 432, "Stones/Spike_Idle.png");
		stone[6].init_stone(renderer, 816,  48,  48, 192, "Stones/Spike_Idle.png");
		stone[0].set_clips();

		Spike* spike = new Spike[5];
		spike[0].set_spike(renderer, 196, 464, 0, "Spikes/spike_bottom.png");
		spike[1].set_spike(renderer,  48, 192, 1, "Spikes/spike_right.png");
		spike[2].set_spike(renderer, 176, 144, 2, "Spikes/spike_left.png");
		spike[3].set_spike(renderer, 436, 320, 0, "Spikes/spike_bottom.png");
		spike[4].set_spike(renderer, 672, 384, 1, "Spikes/spike_right.png");

		bool name_check = true;


		TextScore score(450, 20, 105);
		score.initText(fontText, 20);
		score.setText("Score: ");
		score.createText(fontText, renderer, name_check);

		TextScore mark(560, 20, 45);
		mark.initText(fontText, 20);

		TextScore player(10, 20, 120);
		player.initText(fontText, 20);
		player.setText("Player: ");
		player.createText(fontText, renderer, name_check);

		TextScore name(130, 20, 15 * int(inputText.length()));
		name.initText(fontText, 20);
		name.setText(inputText);
		name.createText(fontText, renderer, name_check);

		int new_sco = -1;
		int score_save = 0;
		bool check_score = false;

		Heart* live = new Heart[10];
		for (int i = 0; i < 9; i++)
		{
			live[i].setHeart(renderer, 640 + 40 * i, 8);
			if (i >= 5)
				live[i].kill();
		}
		int number_dead = 0;

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
					sco += 100;
					score_save += 100;
					Mix_PlayChannel(-1, soundEffect[collect_sound], 0);
				}
				fruits[i].showImg(renderer);
			}


			for (int i = 0; i < 7; i++)
			{
				if (checkCollision(stone[i].getRect_stone(), character.getRect(), 4, 4))
				{
					Mix_PlayChannel(-1, soundEffect[hitRock_sound], 0);
					
					if (i == 2 || i == 5 || i == 6)
					{
						character.setPos(624, 192);
					}
					else character.setPos(0, 448);
					live[4 - number_dead].kill();
					number_dead++;
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (checkCollision_spike(spike[i].getRect_spike(), character.getRect(), i % 3, 4))
				{
					Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
					if (i == 4)
					{
						character.setPos(624, 192);
					}
					else character.setPos(0, 448);
					live[4 - number_dead].kill();
					number_dead++;
				}
			}

			if (sco == 0)
			{
				check_score = true;
				new_sco = sco;
				mark.setText("000");
			}
			if (sco != new_sco)
			{
				check_score = true;
				new_sco = sco;
				mark.setText(to_string(new_sco));
			}
			else
			{
				check_score = false;
			}
			mark.createText(fontText, renderer, check_score);
			score.show(renderer);
			mark.show(renderer);
			player.show(renderer);
			name.show(renderer);

			for (int i = 0; i < 9; i++)
			{
				live[i].show(renderer);
			}
			if (score_save == 300)
			{
				Mix_PlayChannel(-1, soundEffect[extra_life], 0);
				score_save = 0;
				number_dead--;
				live[4 - number_dead].live();
			}
			if (live[0].isKill() == true)
			{
				Game_Status = GAME_OVER;
				Mix_FreeMusic(game_music);
				game_music = NULL;
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				delete[]stone;
				delete[]fruits;
				delete[]spike;
				goto Game_over;
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
		for (int i = 0; i < 9; i++)
		{
			heart_game += live[i].get_heard();
		}
	}
	if (Game_Status == GAME_OVER)
	{
	Game_over:
		if (!put_data)
		{
			put_data = true;
			update_data(sco, heart_game, inputText);
		}
		Mix_PlayChannel(-1, soundEffect[lose_sound], 0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			return -1;
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
		if (!loadGameOver())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&e_end) != 0)
			{
				if (e_end.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (e_end.type == SDL_MOUSEBUTTONDOWN)
				{
					if (e_end.motion.x >= 500 && e_end.motion.x <= 575 && e_end.motion.y >= 390 && e_end.motion.y <= 460)
					{
						Mix_FreeChunk(soundEffect[lose_sound]);
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						goto Play;
					}
				}
			}
			game_over.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}

	if (!put_data) update_data(sco, heart_game, inputText);

	close();
	return 0;
}