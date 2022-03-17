#include "BoardGame.h"
#include "Ninja_Frog.h"
#include "Background.h"
using namespace BG;

void in_bgrnen(Background a,SDL_Renderer *renderer)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			a.show(renderer, 34 + j * 64, 27 + i * 64, 64, 64);
		}
	}
}

void in_Background_A(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 0, 0, 34, 288);
}

void in_Background_B(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 34, 0, 383, 27);
}

void in_Background_C(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 34, 251, 475, 37);
}

void in_Background_D(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 466, 155, 46, 96);
}

void in_Background_E(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 98, 155, 368, 32);
}

void in_Background_F(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 98, 75, 96, 80);
}

void in_Background_G(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 242, 75, 192, 32);
}

void in_Background_H(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 482, 44, 30, 111);
}

void in_Background_I(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 434, 219, 32, 33);
}

void in_Background_K(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 417, 0, 95, 18);
}

void in_Background_L(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 491, 18, 21, 26);
}

void in_Background_M(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 417, 18, 47, 9);
}

void in_Background_N(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 482, 28, 9, 16);
}

void in_Background_O(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 482, 18, 9, 9);
}

void in_Background_P(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 464, 18, 16, 9);
}


int main(int argc, char* argv[])
{
	srand(time(0));
	init(window, renderer);

	Background bgrnen(renderer,"Green.png");
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

	Ninja_Frog fall(renderer);
	
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			fall.move(event);
		}
		SDL_RenderClear(renderer);

		in_bgrnen(bgrnen, renderer);
		in_Background_A(Background_A, renderer);
		in_Background_B(Background_B, renderer);
		in_Background_C(Background_C, renderer);
		in_Background_D(Background_D, renderer);
		in_Background_E(Background_E, renderer);
		in_Background_F(Background_F, renderer);
		in_Background_G(Background_G, renderer);
		in_Background_H(Background_H, renderer);
		in_Background_I(Background_I, renderer);
		in_Background_K(Background_K, renderer);
		in_Background_L(Background_L, renderer);
		in_Background_M(Background_M, renderer);
		in_Background_N(Background_N, renderer);
		in_Background_O(Background_O, renderer);
		in_Background_P(Background_P, renderer);
		
		fall.show(renderer);

		SDL_RenderPresent(renderer);
	}
	quitSDL(window, renderer);
	return 0;
}