#include "BoardGame.h"
#include "Fall.h"
#include "Background.h"
using namespace BG;

void in_da_xam_doc_dai(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 0, 27, 34, 224);
}

void in_da_xam_ngang_tren_dai(Background a, SDL_Renderer* renderer)
{
	a.show(renderer, 25, 0, 392, 27);
}

void in_bgrMid(Background a,SDL_Renderer *renderer)
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
	srand(time(0));
	init(window, renderer);

	Background bgrmid(renderer,"Green.png");
	Background da_xam_ngang_tren_dai(renderer, "Terrain_Project/Da_xam/Da_xam_ngang_3_o_(48x9)/Da_xam_ngang_tren_dai.png");
	Background da_xam_doc_dai(renderer, "Terrain_Project/Da_xam/Da_xam_doc_dai.png");

	Fall fall(renderer);
	
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
		in_bgrMid(bgrmid, renderer);
		in_da_xam_ngang_tren_dai(da_xam_ngang_tren_dai, renderer);
		in_da_xam_doc_dai(da_xam_doc_dai, renderer);
		fall.show(renderer);
		SDL_RenderPresent(renderer);
	}
	quitSDL(window, renderer);
	return 0;
}