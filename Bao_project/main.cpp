#include "BoardGame.h"
#include "Ninja_Frog.h"
#include "Background.h"
#include "Time.h"
#include "Fruits.h"
using namespace BG;

const int frame_per_second = 20; //fps

void in_bgrnen(Background a, SDL_Renderer* renderer)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			a.show(renderer, 34 + j * 64, 27 + i * 64, 64, 64);
		}
	}
}

int main(int argc, char* argv[])
{
	//srand(time(NULL));
	init(window, renderer);
	Time* fps_timer = new Time();
	//Time* time = new Time();
	Background bgrnen(renderer, "Green.png");
	Background Background_A(renderer, "Terrain_Project/Background/Background_A.png");
	Background Background_B(renderer, "Terrain_Project/Background/Background_B.png");
	Background Background_C(renderer, "Terrain_Project/Background/Background_C.png");
	Background Background_D(renderer, "Terrain_Project/Background/Background_D.png");
	Background Background_E(renderer, "Terrain_Project/Background/Background_E.png");
	Background Background_F(renderer, "Terrain_Project/Background/Background_F.png");
	Background Background_G(renderer, "Terrain_Project/Background/Background_G.png");
	Background Background_H(renderer, "Terrain_Project/Background/Background_H.png");
	Background Background_I(renderer, "Terrain_Project/Background/Background_I.png");
	Background Background_K(renderer, "Terrain_Project/Background/Background_K.png");
	Background Background_L(renderer, "Terrain_Project/Background/Background_L.png");
	Background Background_M(renderer, "Terrain_Project/Background/Background_M.png");
	Background Background_N(renderer, "Terrain_Project/Background/Background_N.png");
	Background Background_O(renderer, "Terrain_Project/Background/Background_O.png");
	Background Background_P(renderer, "Terrain_Project/Background/Background_P.png");
	Background Background_Q(renderer, "Terrain_Project/Background/Background_Q.png");
	Background Background_R(renderer, "Terrain_Project/Background/Background_R.png");
	Background Background_U(renderer, "Terrain_Project/Thung_cam_to.png");
	Background Background_S(renderer, "Terrain_Project/Thung_cam_nho.png");
	Background Background_T(renderer, "Terrain_Project/Thung_cam_nho.png");

	Ninja_Frog ninja_frog(renderer);
	Fruits* apple  = new Fruits[6];
	Fruits* orange = new Fruits[14];
	Fruits* kiwi   = new Fruits[7];
	for (int i = 0; i < 6; i++)
	{
		int a;
		if ( i % 2 == 0) a = -5;
		else a = 5;
		apple[i].setFruits(renderer, 50+a, 56+i*22, "Fruits/Apple.png");
		apple[i].set_clips();
	}
	for (int i = 0; i < 7; i++)
	{
		orange[i].setFruits(renderer, 230+i*30, 50, "Fruits/Orange.png");
		orange[i].set_clips();
	}
	for (int i = 7; i < 14; i++)
	{
		orange[i].setFruits(renderer, 230+(i-7)*30, 100, "Fruits/Orange.png");
		orange[i].set_clips();
	}
	for (int i = 0; i < 3; i++)
	{
		kiwi[i].setFruits(renderer, 254+i*28, 184, "Fruits/Kiwi.png");
		kiwi[i].set_clips();
	}
	for (int i = 3; i < 7; i++)
	{
		kiwi[i].setFruits(renderer, 240+(i-3)*28, 197, "Fruits/Kiwi.png");
		kiwi[i].set_clips();
	}
	ninja_frog.set_clips();

	while (!quit)
	{
		fps_timer->start();
		//time->tick();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			ninja_frog.keyboard_input(event, renderer);
		}
		SDL_RenderClear(renderer);

		in_bgrnen(bgrnen, renderer);
		Background_A.show(renderer,   0,   0,  34, 288);
		Background_B.show(renderer,  34,   0, 383,  27);
		Background_C.show(renderer,  34, 251, 475,  37);
		Background_D.show(renderer, 466, 155,  46,  96);
		Background_E.show(renderer,  98, 155, 368,  32);
		Background_F.show(renderer,  98,  75,  96,  80);
		Background_G.show(renderer, 242,  75, 192,  32);
		Background_H.show(renderer, 482,  44,  30, 111);
		Background_I.show(renderer, 434, 219,  32,  33);
		Background_K.show(renderer, 417,   0,  95,  18);
		Background_L.show(renderer, 491,  18,  21,  26);
		Background_M.show(renderer, 417,  18,  47,   9);
		Background_N.show(renderer, 482,  28,   9,  16);
		Background_O.show(renderer, 482,  18,   9,   9);
		Background_P.show(renderer, 464,  18,  16,   9);
		Background_Q.show(renderer, 114, 219,  48,  32);
		Background_R.show(renderer,  98, 235,  16,  16);
		Background_U.show(renderer, 194, 187,  32,  32);
		Background_S.show(renderer, 226, 187,  16,  16);
		Background_T.show(renderer, 354, 187,  16,  16);
		ninja_frog.handle_move();
		ninja_frog.show_frame(renderer);
		for (int i = 0; i < 6; i++)
		{
			apple[i].show_frame(renderer, "Fruits/Apple.png");
		}
		for (int i = 0; i < 14; i++)
		{
			orange[i].show_frame(renderer, "Fruits/Orange.png");
		}
		for (int i = 0; i < 7; i++)
		{
			kiwi[i].show_frame(renderer, "Fruits/Kiwi.png");
		}
		SDL_RenderPresent(renderer);

		int real_time = fps_timer->get_ticks();
		int time_one_frame = 1000 / frame_per_second;
		if (real_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_time;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}
	}
	quitSDL(window, renderer);
	return 0;
}
