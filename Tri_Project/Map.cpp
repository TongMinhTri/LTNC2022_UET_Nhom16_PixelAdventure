#include "Map.h"

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

// Ham load cac loai map vao mang tile_map
// Nguon tham khao: https://www.youtube.com/watch?v=ma-h2RxBBaY&t=508s

void GameMap::loadTiles(SDL_Renderer* renderer)
{
	char file_img[30]; // Mang luu tru ten file
	FILE* p = NULL;
	for (int i = 0; i < mapNums; i++)
	{
		sprintf_s(file_img, "Maps/map%d.png", i); // Chuyen xau "Maps/map%d.png" vao mang file_img (VD: i = 1 se chuyen hinh anh co ten map1.png vao file_img)

		fopen_s(&p, file_img, "rb"); // Mo file
		if (p == NULL) // Neu khong mo duoc file
		{
			continue;
		}

		fclose(p);
		tile_map[i].loadImg(file_img, renderer); // Cac hinh anh duoc load san va cho de render
	}
}


void GameMap::DrawMap(SDL_Renderer* renderer)
{

	int id_x = 0, id_y = 0;

	for (int i = 0; i < SCREEN_HEIGHT; i += TILE_SIZE)
	{
		id_x = 0;
		for (int j = 0; j < SCREEN_WIDTH; j += TILE_SIZE)
		{
			int value = firstMap.tile[id_y][id_x];
			if (value > 0)
			{
				tile_map[value].SetRect(j, i);
				tile_map[value].renderImg(renderer);
			}
			id_x++;
		}
		id_y++;
	}

}

bool TileMap::loadImg(string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	object = newTexture;

	return object != NULL;
}

void TileMap::renderImg(SDL_Renderer* renderer, const SDL_Rect* clip)
{
	SDL_Rect r = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(renderer, object, clip, &r);
}



GameMap2::GameMap2()
{
}

GameMap2::~GameMap2()
{
}

// Ham load cac loai map vao mang tile_map
// Nguon tham khao: https://www.youtube.com/watch?v=ma-h2RxBBaY&t=508s

void GameMap2::loadTiles(SDL_Renderer* renderer)
{
	char file_img[30]; // Mang luu tru ten file
	FILE* p = NULL;
	for (int i = 0; i < mapNums; i++)
	{
		sprintf_s(file_img, "Maps/map%d.png", i); // Chuyen xau "Maps/map%d.png" vao mang file_img (VD: i = 1 se chuyen hinh anh co ten map1.png vao file_img)

		fopen_s(&p, file_img, "rb"); // Mo file
		if (p == NULL) // Neu khong mo duoc file
		{
			continue;
		}

		fclose(p);
		tile_map[i].loadImg(file_img, renderer); // Cac hinh anh duoc load san va cho de render
	}
}


void GameMap2::DrawMap(SDL_Renderer* renderer)
{

	int id_x = 0, id_y = 0;

	for (int i = 0; i < SCREEN_HEIGHT; i += TILE_SIZE)
	{
		id_x = 0;
		for (int j = 0; j < SCREEN_WIDTH; j += TILE_SIZE)
		{
			int value = secondMap.tile[id_y][id_x];
			if (value > 0)
			{
				tile_map[value].SetRect(j, i);
				tile_map[value].renderImg(renderer);
			}
			id_x++;
		}
		id_y++;
	}

}
