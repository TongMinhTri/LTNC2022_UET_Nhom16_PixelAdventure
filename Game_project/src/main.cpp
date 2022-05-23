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
#include "File_History.h"
#include "Update_dataplayers.h"
#include "Other_Enemy.h"

using namespace std;

BaseOject background;
BaseOject background2;
BaseOject instruction;
BaseOject game_over;
BaseOject menu;
BaseOject map_choose;
BaseOject win;
BaseOject map_pass1;
BaseOject map_pass2;
BaseOject character_choose;
BaseOject top_score;

LTexture gPromptTextTexture;
LTexture gInputTextTexture;

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

bool initRenderer()
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

bool loadBackground()
{
	bool bg = background.loadImg("Images/Background/Purple.png", renderer);
	if (!bg)
	{
		return false;
	}
	return true;
}

bool loadBackground2()
{
	bool bg2 = background2.loadImg("Images/Background/Yellow.png", renderer);
	if (!bg2)
	{
		return false;
	}
	return true;
}

bool loadInstruction()
{
	bool ins = instruction.loadImg("Images/Menu/instruction.png", renderer);
	if (!ins)
	{
		return false;
	}
	return true;
}

bool loadGameOver()
{
	bool end = game_over.loadImg("Images/Game over/game_over.png", renderer);
	if (!end)
	{
		return false;
	}
	return true;
}

bool loadMenu()
{
	bool home = menu.loadImg("Images/Menu/menu.png", renderer);
	if (!home)
	{
		return false;
	}
	return true;
}

bool loadMapChoose()
{
	bool choose = map_choose.loadImg("Images/Menu/map_choose.png", renderer);
	if (!choose)
	{
		return false;
	}
	return true;
}

bool loadCharacterChoose()
{
	bool check = character_choose.loadImg("Images/Character_choose/select.png", renderer);
	if (!check)
	{
		return false;
	}
	return true;
}

bool loadWin()
{
	bool check_win = win.loadImg("Images/Win/victory.png", renderer);
	if (!check_win)
	{
		return false;
	}
	return true;
}

bool loadMapPass1()
{
	bool check = map_pass1.loadImg("Images/Map_pass/map_pass1.png", renderer);
	if (!check)
	{
		return false;
	}
	return true;
}

bool loadMapPass2()
{
	bool check = map_pass2.loadImg("Images/Map_pass/map_pass2.png", renderer);
	if (!check)
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
	pass_music = Mix_LoadMUS("Adv-music/map_pass/map_pass.wav");
	soundEffect[jump_sound] = Mix_LoadWAV("Adv-SFX/jump.wav");
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

bool loadTop_Score()
{
	bool check = top_score.loadImg("Images/Rank/Rank.png", renderer);
	if (!check)
	{
		return false;
	}
	return true;
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

bool loadMedia()
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

int main(int argc, char* args[])
{
	int MAP[3] = { 0, 0, 0 };
	TextScore name[8];
	TextScore score[8];
	TextScore heart[8];
	TextScore r_status[8];
	for (int i = 0; i < 8; i++)
	{
		name[i].init(165, 185 + i * 41);
		name[i].initText(fontText, 20);

		score[i].init(570, 185 + i * 41);
		score[i].initText(fontText, 20);

		heart[i].init(705, 185 + i * 41);
		heart[i].set_W(15);
		heart[i].initText(fontText, 20);

		r_status[i].init(830, 185 + i * 41);
		r_status[i].initText(fontText, 20);
	}
	if (!init())
	{
		return -1;
	}
	if (!loadSound())
	{
		return -1;
	}
	if (!loadMedia())
	{
		return -1;
	}

	int Game_Status = MENU;
	int victory = 0;
	string inputText = "";
	string cha_select;
	int sco = 0;
	int heart_game = 0;
	bool put_data = false;

	Mix_PlayMusic(menu_music, -1);
	if (Game_Status == MENU)
	{
	Menu:
		if (Game_Status == GAME_OVER || Game_Status == WIN || Game_Status == MAP_CHOOSING || Game_Status == CHARACTER_CHOOSING || Game_Status == TOP_SCORE || Game_Status == INSTRUCTION)
		{
			if (!initRenderer())
			{
				return -1;
			}
			if (Game_Status == WIN || Game_Status == GAME_OVER)
			{
				victory_music = Mix_LoadMUS("Adv-music/victory/victory.wav");
				menu_music = Mix_LoadMUS("Adv-music/menu/menu.wav");
				Mix_PlayMusic(menu_music, -1);
			}
			Game_Status = MENU;
		}
		if (!loadMenu())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 431 && event.motion.x <= 529 && event.motion.y >= 299 && event.motion.y <= 340)
					{
						Game_Status = ENTER_NAME;
					}
					else if (event.motion.x >= 380 && event.motion.x <= 580 && event.motion.y >= 340 && event.motion.y <= 380)
					{
						Game_Status = INSTRUCTION;
					}
					else if (event.motion.x >= 437 && event.motion.x <= 525 && event.motion.y >= 380 && event.motion.y <= 420)
					{
						Game_Status = TOP_SCORE;
					}
				}
			}
			menu.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
			if (Game_Status == ENTER_NAME)
			{
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				menu.Free();
				goto Enter_name;
			}
			if (Game_Status == INSTRUCTION)
			{
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				menu.Free();
				goto Instruction;
			}
			if (Game_Status == TOP_SCORE)
			{
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				menu.Free();
				goto Top_Score;
			}
		}
	}
	if (Game_Status == ENTER_NAME)
	{
	Enter_name:
		if (!initRenderer())
		{
			return -1;
		}
		if (!loadMedia())
		{
			return -1;
		}
		bool quit = false;
		SDL_Color textColor = { 0, 128, 128 };
		gFontN = TTF_OpenFont("Fonts/SHOWG.ttf", 30);
		gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor, gFontN, renderer);

		//Enable text input
		SDL_StartTextInput();

		while (!quit)
		{
			bool renderText = false;

			while (SDL_PollEvent(&event) != 0)
			{
				//User requests quit
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				//Special key input
				else if (event.type == SDL_KEYDOWN)
				{
					//Handle backspace
					if (event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
					{
						//lop off character
						inputText.pop_back();
						renderText = true;
					}
					//Handle copy
					else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
					{
						SDL_SetClipboardText(inputText.c_str());
					}
					//Handle paste
					else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
					{
						inputText = SDL_GetClipboardText();
						renderText = true;
					}
					else if (event.key.keysym.sym == SDLK_RETURN && inputText[inputText.length() - 1] != ' ')
					{
						Game_Status = CHARACTER_CHOOSING;
					}
				}
				//Special text input event
				else if (event.type == SDL_TEXTINPUT)
				{
					//Not copy or pasting
					if (!(SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V')))
					{
						//Append character
						inputText += event.text.text;
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
					gInputTextTexture.loadFromRenderedText("", textColor, gFontN, renderer);
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

			if (Game_Status == CHARACTER_CHOOSING)
			{
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				gPromptTextTexture.free();
				gInputTextTexture.free();
				TTF_CloseFont(gFont);
				gFont = NULL;
				TTF_CloseFont(gFontN);
				gFontN = NULL;
				goto Character_choose;
			}
		}

		//Disable text input
		SDL_StopTextInput();
	}
	if (Game_Status == CHARACTER_CHOOSING)
	{
	Character_choose:
		if (!initRenderer())
		{
			return -1;
		}

		if (!loadCharacterChoose())
		{
			return -1;
		}

		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 117 && event.motion.x <= 247 && event.motion.y >= 472 && event.motion.y <= 510)
					{
						cha_select = "Mask Dude";
						character_choose.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						Game_Status = MAP_CHOOSING;
						goto Map_choose;
					}
					else if (event.motion.x >= 315 && event.motion.x <= 445 && event.motion.y >= 472 && event.motion.y <= 510)
					{
						cha_select = "Ninja Frog";
						character_choose.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						Game_Status = MAP_CHOOSING;
						goto Map_choose;
					}
					else if (event.motion.x >= 507 && event.motion.x <= 637 && event.motion.y >= 472 && event.motion.y <= 510)
					{
						cha_select = "Pink Man";
						character_choose.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						Game_Status = MAP_CHOOSING;
						goto Map_choose;
					}
					else if (event.motion.x >= 701 && event.motion.x <= 831 && event.motion.y >= 472 && event.motion.y <= 510)
					{
						cha_select = "Virtual Guy";
						character_choose.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						Game_Status = MAP_CHOOSING;
						goto Map_choose;
					}
					else if (event.motion.x >= 837 && event.motion.x <= 930 && event.motion.y >= 128 && event.motion.y <= 166)
					{
						inputText = "";
						character_choose.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						goto Menu;
					}
				}
			}
			character_choose.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	if (Game_Status == MAP_CHOOSING)
	{
	Map_choose:
		if (!initRenderer())
		{
			return -1;
		}

		if (!loadMapChoose())
		{
			return -1;
		}

		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 8 && event.motion.x <= 468 && event.motion.y >= 138 && event.motion.y <= 392)
					{
						Game_Status = PLAY;
					}
					else if (event.motion.x >= 491 && event.motion.x <= 951 && event.motion.y >= 138 && event.motion.y <= 392)
					{
						Game_Status = PLAY2;
					}
					else if (event.motion.x >= 30 && event.motion.x <= 109 && event.motion.y >= 52 && event.motion.y <= 92)
					{
						map_choose.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						goto Character_choose;
					}

				}
			}
			map_choose.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
			if (Game_Status == PLAY)
			{
				map_choose.Free();
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				Mix_FreeMusic(menu_music);
				menu_music = NULL;
				goto Play;
			}
			if (Game_Status == PLAY2)
			{
				map_choose.Free();
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				Mix_FreeMusic(menu_music);
				menu_music = NULL;
				goto Play2;
			}
		}

	}
	if (Game_Status == INSTRUCTION)
	{
	Instruction:
		if (!initRenderer())
		{
			return -1;
		}
		if (!loadInstruction())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 54 && event.motion.x <= 138 && event.motion.y >= 469 && event.motion.y <= 501)
					{
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						instruction.Free();
						goto Menu;
					}
				}
			}
			instruction.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	if (Game_Status == TOP_SCORE)
	{
	Top_Score:

		if (!initRenderer())
		{
			return -1;
		}
		if (!loadTop_Score())
		{
			return -1;
		}

		char c;
		int lines = 0;
		int max_name = 0;
		fstream f1("Big_Data.txt");
		f1.get(c);
		while (f1)
		{
			while (f1 && c != '\n')
			{
				f1.get(c);
			}
			lines++;
			f1.get(c);
		}
		f1.close();
		fstream f2("Big_Data.txt");
		Player* players = new Player[lines];
		int p = 0;
		int diem;
		int pos1 = 0, pos2 = 0;
		int space1 = 0;
		if (lines > 0)
		{
			while (!f2.eof())
			{
				string s;
				string s2 = "";
				getline(f2, s);
				diem = 0;
				for (int i = 3; i < s.length(); i++)
				{
					if (s[i] != ' ')
					{
						space1 = i;
						break;
					}
				}
				for (int i = space1; i < s.length(); i++)
				{
					if ((s[i] >= '1' && s[i] <= '9' || (s[i] == '0' && s[i + 1] == ' '))
						&& s[i + 4] == ' ' && s[i + 5] >= '0' && s[i + 5] <= '9' && (s[i + 7] == 'w' || s[i + 7] == 'l'))
					{
						pos1 = i;
						break;
					}
				}
				for (int i = space1; i < pos1 - 1; i++)
				{
					s2 += s[i];
				}
				if (s2.length() > 1)
				{
					players[p].init_name(s2);
					if (s[pos1 + 3] == ' ') diem = (int(char(s[pos1]) - '0')) * 100;
					else diem = (int(char(s[pos1 + 1]) - '0')) * 100 + (int(char(s[pos1]) - '0')) * 1000;
					players[p].init_score(diem);
					pos2 = pos1 + 5;
					players[p].init_heart(int(char(s[pos2]) - '0'));
					if (s[pos2 + 2] == 'w') players[p].init_win("win");
					else players[p].init_win("lose");
					p++;
				}
				if (int(s2.length()) > max_name) max_name = int(s2.length());
			}
			f2.close();
		}
		int o, scs, minus_scs = 0;
		o = lines;
		scs = 0;
		while (o >= 10)
		{
			scs++;
			o /= 10;
		}
		sort(players, players + lines, sort_data);
		int a = 8;
		int d = 45;
		for (int i = 0; i < min(a, lines); i++)
		{
			name[i].set_W(15 * players[i].get_length());
			name[i].setText(players[i].get_name());
			name[i].createText(fontText, renderer, true);

			d = 45;
			if (players[i].get_score() == 0) d = 15;
			else if (players[i].get_score() >= 1000 ) d = 60;
			score[i].set_W(d);
			score[i].setText(to_string(players[i].get_score()));
			score[i].createText(fontText, renderer, true);

			heart[i].setText(to_string(players[i].get_heart()));
			heart[i].createText(fontText, renderer, true);

			d = 45;
			if (players[i].get_win() == "lose") d = 60;
			r_status[i].set_W(d);
			r_status[i].setText(players[i].get_win());
			r_status[i].createText(fontText, renderer, true);
		}
		bool quit = false;

		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 845 && event.motion.x <= 930 && event.motion.y >= 5 && event.motion.y <= 50)
					{
						top_score.Free();
						delete[]players;
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						goto Menu;
					}
				}
			}
			top_score.Render(renderer, NULL);
			for (int i = 0; i < min(a, lines); i++)
			{
				name[i].show(renderer);
				score[i].show(renderer);
				heart[i].show(renderer);
				r_status[i].show(renderer);
			}
			SDL_RenderPresent(renderer);
		}

	}
	if (Game_Status == PLAY || Game_Status == GAME_OVER)
	{
	Play:
		if (MAP[2] == 0 && MAP[1] == 0) MAP[1] = 1;
		else if (MAP[2] == 1 && MAP[1] == 0) MAP[1] = 2;

		if (!initRenderer())
		{
			return -1;
		}

		if (Game_Status == GAME_OVER)
		{
			Game_Status = PLAY;
		}

		gameover_music = Mix_LoadMUS("Adv-music/lose/game_over.wav");
		game_music = Mix_LoadMUS("Adv-music/level/Level-04.wav");

		if (!loadBackground())
		{
			return -1;
		}

		Time timer;

		put_data = false;
		heart_game = 0;

		Mix_PlayMusic(game_music, -1);

		GameMap gm;
		gm.loadTiles(renderer);
		Map map_data = gm.getMap();


		Checkpoints* point = new Checkpoints[3];
		point[0].set_checkpoints(renderer, 912, 432, 8, 48, "Images/Checkpoints/End/End(48x48).png");
		point[1].set_checkpoints(renderer, 0, 416, 17, 64, "Images/Checkpoints/Start/Start (Moving) (64x64).png");
		point[2].set_checkpoints(renderer, 624, 144, 26, 48, "Images/Checkpoints/Checkpoint/Checkpoint (Flag Out) (48x48).png");
		for (int i = 0; i <= 2; i++)
			point[i].set_clips();

		MainObject character(864, 432);
		character.setIMG(renderer, cha_select);
		character.setClips();
		bool quit = false;

		Fruits* fruits = new Fruits[9];
		fruits[0].setFruits(renderer, 240, 336, "Images/Fruits/Cherries.png");
		fruits[1].setFruits(renderer, 288, 336, "Images/Fruits/Melon.png");
		fruits[2].setFruits(renderer, 192, 192, "Images/Fruits/Apple.png");
		fruits[3].setFruits(renderer, 240, 192, "Images/Fruits/Orange.png");
		fruits[4].setFruits(renderer, 288, 192, "Images/Fruits/Kiwi.png");
		fruits[5].setFruits(renderer, 864, 96, "Images/Fruits/Bananas.png");
		fruits[6].setFruits(renderer, 864, 144, "Images/Fruits/Cherries.png");
		fruits[7].setFruits(renderer, 576, 192, "Images/Fruits/Pineapple.png");
		fruits[8].setFruits(renderer, 432, 192, "Images/Fruits/Strawberry.png");
		for (int i = 0; i < 9; i++)
		{
			fruits[i].set_clips();
		}

		Stone* stone = new Stone[7];
		stone[1].init_stone(renderer, 576, 144, 432, 288, "Images/Stones/Spike_Idle.png", 1);
		stone[2].init_stone(renderer, 768, 48, 96, 240, "Images/Stones/Spike_Idle.png", 1);
		stone[3].init_stone(renderer, 288, 192, 192, 240, "Images/Stones/Spike_Idle.png", 1);
		stone[4].init_stone(renderer, 48, 96, 48, 864, "Images/Stones/Spike_Idle.png", 1);
		stone[5].init_stone(renderer, 720, 336, 336, 432, "Images/Stones/Spike_Idle.png", 1);
		stone[6].init_stone(renderer, 816, 48, 96, 192, "Images/Stones/Spike_Idle.png", 1);
		stone[0].set_clips();

		Spike* spike = new Spike[5];
		spike[0].set_spike(renderer, 196, 464, 0, "Images/Spikes/spike_bottom.png");
		spike[1].set_spike(renderer, 48, 192, 1, "Images/Spikes/spike_right.png");
		spike[2].set_spike(renderer, 176, 144, 2, "Images/Spikes/spike_left.png");
		spike[3].set_spike(renderer, 436, 320, 0, "Images/Spikes/spike_bottom.png");
		spike[4].set_spike(renderer, 672, 384, 1, "Images/Spikes/spike_right.png");

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
			live[i].setHeart(renderer, 620 + 40 * i, 8);
			if (i >= 5)
				live[i].kill();
		}
		int number_dead = 0;

		Other_Enemy trunk;
		trunk.inita_enemy(renderer, 224, 448, 224, 480, 14, 1, 64, 32);
		trunk.set_speedx(0.08);
		trunk.setIMG(renderer, "Trunk");
		trunk.set_clips();
		Bullet bullet;
		bullet.set_bullet(renderer,256, 456,"Images/Enemies/Trunk/Bullet.png");

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

			point[0].showImg(renderer);
			point[1].showImg(renderer);
			point[2].showImg(renderer);

			character.updatePlayerPosition(map_data);
			character.showImage(renderer);

			stone[1].DoStone_Circle();
			stone[1].Stone_Move_Circle(renderer);
			stone[2].stone_move_up(renderer);
			stone[3].DoStone_Circle();
			stone[3].Stone_Move_Circle(renderer);
			stone[4].stone_move(renderer);
			stone[5].stone_move_up(renderer);
			stone[6].stone_move_up(renderer);

			if (bullet.is_move() == false && trunk.getRect_x() == 224 
				|| bullet.is_move() == false && trunk.getRect_x() == 480 
				 || bullet.is_move() == false && trunk.getRect_x() == 349)
			{
				bullet.setPos(trunk.getRect_x() + 20, trunk.getRect_y() + 8);
			}
			trunk.enemy_move(renderer);
			
			if(trunk.getDirection() == 0)
			{ 
				bullet.fire_right();
			}
			if (trunk.getDirection() == 1)
			{
				bullet.fire_left();
			}

			bullet.show(renderer);
			
			for (int i = 0; i < 5; i++)
			{
				spike[i].showImg(renderer);
			}

			if (checkCollision_ghost(trunk.getRect_enemy(), character.getRect(), 12, 12))
			{
				Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
				character.setPos(0, 448);
				live[4 - number_dead].kill();
				number_dead++;
			}
				
			if (checkCollision_ghost(bullet.getRect_bullet(), character.getRect(), 2, 6))
				{
					Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
					character.setPos(0, 448);
					live[4 - number_dead].kill();
					number_dead++;
				}
		
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


			for (int i = 1; i < 7; i++)
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
				for (int i = 0; i < 9; i++)
				{
					heart_game += live[i].get_heart();
				}
				Mix_FreeMusic(game_music);
				game_music = NULL;
				for (int i = 0; i < 3; i++)
				{
					point[i].Free();
				}
				for (int i = 0; i < 7; i++)
				{
					stone[i].Free();
				}
				for (int i = 0; i < 9; i++)
				{
					fruits[i].Free();
				}
				for (int i = 0; i < 5; i++)
				{
					spike[i].Free();
				}
				for (int i = 0; i < 10; i++)
				{
					live[i].Free();
				}

				trunk.Free();
				bullet.Free();
				
				delete[]stone;
				delete[]fruits;
				delete[]spike;
				delete[]live;
				delete[]point;
				background.Free();
				character.Free();
				gm.free();
				score.Free();
				mark.Free();
				player.Free();
				name.Free();
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				goto Game_over;
			}
			else if (character.checkWin())
			{
				victory++;
				Mix_FreeMusic(game_music);
				game_music = NULL;
				for (int i = 0; i < 9; i++)
				{
					heart_game += live[i].get_heart();
				}
				for (int i = 0; i < 3; i++)
				{
					point[i].Free();
				}
				for (int i = 0; i < 7; i++)
				{
					stone[i].Free();
				}
				for (int i = 0; i < 9; i++)
				{
					fruits[i].Free();
				}
				for (int i = 0; i < 5; i++)
				{
					spike[i].Free();
				}
				for (int i = 0; i < 10; i++)
				{
					live[i].Free();
				}
				delete[]stone;
				delete[]fruits;
				delete[]spike;
				delete[]live;
				delete[]point;
				trunk.Free();
				bullet.Free();
				background.Free();
				character.Free();
				gm.free();
				score.Free();
				mark.Free();
				player.Free();
				name.Free();
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				if (victory == 2)
				{
					Game_Status = WIN;
					goto Win;
				}
				else
				{
					Game_Status = MAP_PASS_ONE;
					goto Map_pass_1;
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
	}
	if (Game_Status == MAP_PASS_ONE)
	{
	Map_pass_1:
		update_data1(sco, heart_game, inputText, "win");
		put_data = true;
		Mix_PlayMusic(pass_music, 1);
		if (!initRenderer())
		{
			return -1;
		}
		if (!loadMapPass1())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 478 && event.motion.x <= 542 && event.motion.y >= 427 && event.motion.y <= 491)
					{
						map_pass1.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						Game_Status = PLAY2;
						goto Play2;
					}
				}
			}
			map_pass1.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	if (Game_Status == PLAY2 || Game_Status == GAME_OVER)
	{
	Play2:
		if (MAP[1] == 0 && MAP[2] == 0) MAP[2] = 1;
		else if (MAP[1] == 1 && MAP[2] == 0) MAP[2] = 2;

		if (!initRenderer())
		{
			return -1;
		}

		if (Game_Status == GAME_OVER)
		{
			Game_Status = PLAY2;
		}

		gameover_music = Mix_LoadMUS("Adv-music/lose/game_over.wav");
		game_music = Mix_LoadMUS("Adv-music/level/Level-04.wav");

		if (!loadBackground2())
		{
			return -1;
		}

		Time timer;

		put_data = false;
		heart_game = 0;

		Mix_PlayMusic(game_music, -1);

		GameMap2 gm2;
		gm2.loadTiles(renderer);
		Map2 map_data2 = gm2.getMap();

		MainObject character(864, 432);
		character.setIMG(renderer, cha_select);
		character.setClips();
		bool quit = false;

		Checkpoints* point = new Checkpoints[3];
		point[0].set_checkpoints(renderer, 912, 432, 8, 48, "Images/Checkpoints/End/End(48x48).png");
		point[1].set_checkpoints(renderer, 0, 80, 17, 64, "Images/Checkpoints/Start/Start (Moving) (64x64).png");
		point[2].set_checkpoints(renderer, 672, 240, 26, 48, "Images/Checkpoints/Checkpoint/Checkpoint (Flag Out) (48x48).png");

		for (int i = 0; i <= 2; i++)
			point[i].set_clips();

		Stone* saw = new Stone[6];
		saw[0].init_stone(renderer, 48, 192, 192, 384, "Images/Saw/On (48x48).png", 8);
		saw[1].init_stone(renderer, 144, 432, 192, 432, "Images/Saw/On (48x48).png", 8);
		saw[2].init_stone(renderer, 240, 192, 192, 432, "Images/Saw/On (48x48).png", 8);
		saw[3].init_stone(renderer, 720, 48, 48, 240, "Images/Saw/On (48x48).png", 8);
		saw[4].init_stone(renderer, 816, 240, 48, 240, "Images/Saw/On (48x48).png", 8);
		saw[5].init_stone(renderer, 912, 48, 48, 240, "Images/Saw/On (48x48).png", 8);
		for (int i = 0; i <= 5; i++)
		{
			saw[i].set_clips();
		}
		Stone* stand_saw = new Stone[6];
		stand_saw[0].set_Stand(renderer, 69, 216, "Images/Stand/stand_192.png");
		stand_saw[1].set_Stand(renderer, 165, 216, "Images/Stand/stand_240.png");
		stand_saw[2].set_Stand(renderer, 261, 216, "Images/Stand/stand_240.png");
		stand_saw[3].set_Stand(renderer, 741, 72, "Images/Stand/stand_192.png");
		stand_saw[4].set_Stand(renderer, 837, 72, "Images/Stand/stand_192.png");
		stand_saw[5].set_Stand(renderer, 933, 72, "Images/Stand/stand_192.png");

		Spike* spike = new Spike[9];
		spike[0].set_spike(renderer, 144, 96, 1, "Images/Spikes/spike_right.png");
		spike[1].set_spike(renderer, 720, 144, 1, "Images/Spikes/spike_right.png");
		spike[2].set_spike(renderer, 580, 320, 0, "Images/Spikes/spike_bottom.png");
		spike[3].set_spike(renderer, 388, 320, 0, "Images/Spikes/spike_bottom.png");
		spike[4].set_spike(renderer, 532, 128, 0, "Images/Spikes/spike_bottom.png");
		spike[5].set_spike(renderer, 340, 128, 0, "Images/Spikes/spike_bottom.png");
		spike[6].set_spike(renderer, 244, 464, 0, "Images/Spikes/spike_bottom.png");
		spike[7].set_spike(renderer, 388, 464, 0, "Images/Spikes/spike_bottom.png");
		spike[8].set_spike(renderer, 772, 464, 0, "Images/Spikes/spike_bottom.png");

		Fruits* fruits = new Fruits[10];
		fruits[0].setFruits(renderer, 816, 240, "Images/Fruits/Cherries.png");
		fruits[1].setFruits(renderer, 912, 242, "Images/Fruits/Melon.png");
		fruits[2].setFruits(renderer, 0, 272, "Images/Fruits/Apple.png");
		fruits[3].setFruits(renderer, 0, 320, "Images/Fruits/Orange.png");
		fruits[4].setFruits(renderer, 336, 192, "Images/Fruits/Kiwi.png");
		fruits[5].setFruits(renderer, 432, 192, "Images/Fruits/Bananas.png");
		fruits[6].setFruits(renderer, 576, 48, "Images/Fruits/Cherries.png");
		fruits[7].setFruits(renderer, 624, 192, "Images/Fruits/Pineapple.png");
		fruits[8].setFruits(renderer, 528, 192, "Images/Fruits/Strawberry.png");
		fruits[9].setFruits(renderer, 384, 48, "Images/Fruits/Melon.png");
		for (int i = 0; i < 10; i++)
		{
			fruits[i].set_clips();
		}

		Other_Enemy* enemies = new Other_Enemy[6];
		enemies[0].inita_enemy(renderer, 288, 300, 288, 930, 28, 0, 44, 30);
		enemies[0].set_speedx(0.7);
		enemies[0].setIMG(renderer, "Ghost");
		enemies[1].inita_enemy(renderer, 153, 110, 153, 690, 14, 0, 32, 34);
		enemies[1].set_speedx(0.65);
		enemies[1].setIMG(renderer, "Chicken");
		enemies[2].inita_enemy(renderer, 686, 114, 153, 686, 12, 1, 36, 30);
		enemies[2].set_speedx(0.65);
		enemies[2].setIMG(renderer, "Pig");
		enemies[3].inita_enemy(renderer, 0, 192, 0, 928, 9, 1, 32, 32);
		enemies[3].set_speedx(0.85);
		enemies[3].setIMG(renderer, "Bird");
		enemies[4].inita_enemy(renderer, 868, 450, 336, 868, 10, 0, 44, 30);
		enemies[4].set_speedx(0.4);
		enemies[4].setIMG(renderer, "Slime");
		enemies[5].inita_enemy(renderer, 336, 392, 336, 928, 9, 1, 32, 32);
		enemies[5].set_speedx(0.4);
		enemies[5].setIMG(renderer, "Bird");
		for (int i = 0; i < 6; i++)
		{
			enemies[i].set_clips();
		}

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

			background2.Render(renderer, NULL);
			gm2.DrawMap(renderer);

			point[0].showImg(renderer);
			point[1].showImg(renderer);
			point[2].showImg(renderer);

			character.updatePlayerPosition2(map_data2);
			character.showImage(renderer);

			for (int i = 0; i < 6; i++)
			{
				enemies[i].enemy_move(renderer);
			}
		
			for (int i = 0; i < 6; i++)
			{
				stand_saw[i].show_stand(renderer);
			}
			for (int i = 0; i <= 5; i++)
			{
				if (i <= 2)
				{
					saw[i].show_frame_up(renderer, 0.8);
				}
				else
				{
					saw[i].show_frame_up(renderer, 0.4);
				}
				if (checkCollision(saw[i].getRect_stone(), character.getRect(), 4, 4))
				{
					Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
					if (i == 3) character.setPos(0, 96);
					else character.setPos(672, 240);
					live[4 - number_dead].kill();
					number_dead++;
				}
			}
			for (int i = 0; i < 9; i++)
			{
				spike[i].showImg(renderer);
			}

			for (int i = 0; i < 10; i++)
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

			int d = 1;
			for (int i = 0; i < 9; i++)
			{
				if (i > 1) d = 0;
				if (checkCollision_spike(spike[i].getRect_spike(), character.getRect(), d, 4))
				{
					Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
					if (i <= 1 || i == 4 || i == 5) character.setPos(0, 96);
					else character.setPos(672, 240);
					live[4 - number_dead].kill();
					number_dead++;
				}
			}

			int kc = 10;
			for (int i = 0; i < 6; i++)
			{
				if (i > 0) kc = 3;
				if (checkCollision_ghost(enemies[i].getRect_enemy(), character.getRect(), kc, 4) && i != 4)
				{
					Mix_PlayChannel(-1, soundEffect[hitSpike_sound], 0);
					if (i == 1 || i == 2) character.setPos(0, 96);
					else character.setPos(672, 240);
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
				for (int i = 0; i < 9; i++)
				{
					heart_game += live[i].get_heart();
				}
				Mix_FreeMusic(game_music);
				game_music = NULL;
				for (int i = 0; i < 3; i++)
				{
					point[i].Free();
				}
				for (int i = 0; i < 6; i++)
				{
					saw[i].Free();
				}
				for (int i = 0; i < 10; i++)
				{
					fruits[i].Free();
				}
				for (int i = 0; i < 9; i++)
				{
					spike[i].Free();
				}
				for (int i = 0; i < 9; i++)
				{
					live[i].Free();
				}
				for (int i = 0; i < 6; i++)
				{
					stand_saw[i].Free();
				}
				for (int i = 0; i < 6; i++)
				{
					enemies[i].Free();
				}
				delete[]saw;
				delete[]fruits;
				delete[]spike;
				delete[]live;
				delete[]point;
				delete[]stand_saw;
				delete[]enemies;
				background2.Free();
				character.Free();
				gm2.free();
				score.Free();
				mark.Free();
				player.Free();
				name.Free();
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				goto Game_over;
			}
			else if (character.checkWin())
			{
				victory++;
				Mix_FreeMusic(game_music);
				game_music = NULL;
				for (int i = 0; i < 9; i++)
				{
					heart_game += live[i].get_heart();
				}
				for (int i = 0; i < 3; i++)
				{
					point[i].Free();
				}
				for (int i = 0; i < 6; i++)
				{
					saw[i].Free();
				}
				for (int i = 0; i < 10; i++)
				{
					fruits[i].Free();
				}
				for (int i = 0; i < 9; i++)
				{
					spike[i].Free();
				}
				for (int i = 0; i < 9; i++)
				{
					live[i].Free();
				}
				for (int i = 0; i < 6; i++)
				{
					stand_saw[i].Free();
				}
				for (int i = 0; i < 6; i++)
				{
					enemies[i].Free();
				}
				delete[]saw;
				delete[]fruits;
				delete[]spike;
				delete[]live;
				delete[]point;
				delete[]stand_saw;
				delete[]enemies;
				background2.Free();
				character.Free();
				gm2.free();
				score.Free();
				mark.Free();
				player.Free();
				name.Free();
				SDL_DestroyRenderer(renderer);
				renderer = NULL;
				if (victory == 2)
				{
					Game_Status = WIN;
					goto Win;
				}
				else
				{
					Game_Status = MAP_PASS_TWO;
					goto Map_pass_2;
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
	}
	if (Game_Status == MAP_PASS_TWO)
	{
	Map_pass_2:
		put_data = true;
		update_data2(sco, heart_game, inputText, "win");
		Mix_PlayMusic(pass_music, 1);
		if (!initRenderer())
		{
			return -1;
		}
		if (!loadMapPass2())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 478 && event.motion.x <= 542 && event.motion.y >= 427 && event.motion.y <= 491)
					{
						map_pass2.Free();
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						Game_Status = PLAY;
						goto Play;
					}
				}
			}
			map_pass2.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	if (Game_Status == GAME_OVER)
	{
	Game_over:
		if (!put_data)
		{
			put_data = true;
			if (MAP[1] == 1 && MAP[2] == 0) update_data1(sco, heart_game, inputText, "lose");
			else if (MAP[2] == 1 && MAP[1] == 0) update_data2(sco, heart_game, inputText, "lose");
			else update_big_data(sco, heart_game, inputText, "lose");
		}
		sco = 0;
		Mix_PlayMusic(gameover_music, 1);
		if (!initRenderer())
		{
			return -1;
		}
		if (!loadGameOver())
		{
			return -1;
		}

		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 620 && event.motion.x <= 684 && event.motion.y >= 400 && event.motion.y <= 464)
					{
						game_over.Free();
						Mix_FreeMusic(gameover_music);
						gameover_music = NULL;
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						if (Game_Status == PLAY)
						{
							Game_Status = GAME_OVER;
							goto Play;
						}
						if (Game_Status == PLAY2)
						{
							Game_Status = GAME_OVER;
							goto Play2;
						}
					}
					else if (event.motion.x >= 368 && event.motion.x <= 432 && event.motion.y >= 400 && event.motion.y <= 464)
					{
						Game_Status = GAME_OVER;
						game_over.Free();
						inputText = " ";
						Mix_FreeMusic(gameover_music);
						gameover_music = NULL;
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						goto Menu;
					}
				}
			}
			game_over.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}
	if (Game_Status == WIN)
	{
	Win:
		update_big_data(sco, heart_game, inputText, "win");
		sco = 0;
		put_data = true;
		Mix_PlayMusic(victory_music, 1);
		if (!initRenderer())
		{
			return -1;
		}
		if (!loadWin())
		{
			return -1;
		}
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (event.motion.x >= 482 && event.motion.x <= 546 && event.motion.y >= 425 && event.motion.y <= 489)
					{
						victory = 0;
						inputText = " ";
						win.Free();
						Mix_FreeMusic(victory_music);
						gameover_music = NULL;
						SDL_DestroyRenderer(renderer);
						renderer = NULL;
						goto Menu;
					}
				}
			}
			win.Render(renderer, NULL);
			SDL_RenderPresent(renderer);
		}
	}

	if (!put_data)
	{
		put_data = true;
		if (MAP[1] == 1 && MAP[2] == 0) update_data1(sco, heart_game, inputText, "lose");
		else if (MAP[2] == 1 && MAP[1] == 0) update_data2(sco, heart_game, inputText, "lose");
		else if (MAP[2] * MAP[1] != 0) update_big_data(sco, heart_game, inputText, "lose");
	}

	close();
	return 0;
}