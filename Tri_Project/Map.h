#pragma once
#ifndef MAP_H
#define MAP_H

#include "BaseData.h"
#include "BaseObject.h"
#define map_type_num 20

class TileMap : public BaseOject
{
public:
	TileMap() { ; }
	~TileMap() { ; }
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	void loadMap(const char* path);
	void loadTiles(SDL_Renderer* renderer);
	void DrawMap(SDL_Renderer* renderer);
	Map getMap() const { return game_map; }

private:
	Map game_map;
	TileMap tile_map[map_type_num];
};

#endif // !MAP_H
