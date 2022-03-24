#include "Map.h"

GameMap::GameMap()
{
	game_map.xpos = game_map.ypos = 0;
	game_map.xstart = game_map.ystart = 0;
}

GameMap::~GameMap()
{
}

void GameMap::loadMap(const char* path)
{
	FILE* p = NULL;
	fopen_s(&p, path, "rb");
	if (p == NULL)
	{
		return;
	}
	game_map.xpos = game_map.ypos = 0;

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			fscanf_s(p, "%d", &game_map.tile[i][j]);
			int value = game_map.tile[i][j];
			if (value > 0)
			{
				if (j > game_map.xpos)
				{
					game_map.xpos = j;
				}

				if (i > game_map.ypos)
				{
					game_map.ypos = i;
				}
			}
		}
	}

	game_map.xpos = (game_map.xpos + 1) * TILE_SIZE;
	game_map.ypos = (game_map.ypos + 1) * TILE_SIZE;

	game_map.xstart = game_map.ystart = 0;
	game_map.file_name = path;
	fclose(p);

}

void GameMap::loadTiles(SDL_Renderer* renderer)
{
	char file_img[30];
	FILE* p = NULL;
	for (int i = 0; i < map_type_num; i++)
	{
		sprintf_s(file_img, "Maps/map%d.png", i);

		fopen_s(&p, file_img, "rb");
		if (p == NULL)
		{
			continue;
		}

		fclose(p);
		tile_map[i].loadImg(file_img, renderer);
	}
}

void GameMap::DrawMap(SDL_Renderer* renderer)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int map_x = 0;
	int map_y = 0;

	x1 = (game_map.xstart % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	y1 = (game_map.ystart % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	map_x = game_map.xstart / TILE_SIZE;
	map_y = game_map.ystart / TILE_SIZE;


	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		map_x = game_map.xstart / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			int value = game_map.tile[map_y][map_x];
			if (value > 0)
			{
				tile_map[value].SetRect(j, i);
				tile_map[value].Render(renderer);
			}
			map_x++;
		}
		map_y++;
	}

}
