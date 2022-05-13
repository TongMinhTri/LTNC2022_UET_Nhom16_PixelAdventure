#pragma once
#ifndef MAP_H
#define MAP_H

#include "BaseData.h"
#include "BaseObject.h"
#define mapNums 20

class TileMap
{
public:
	TileMap() 
	{
		object = NULL;
		rect.x = rect.y = rect.w = rect.h = 0;
	}
	~TileMap() { ; }
	bool loadImg(string path, SDL_Renderer* renderer);
	void SetRect(const int& x, const int& y)
	{
		rect.x = x;
		rect.y = y;
	}
	void renderImg(SDL_Renderer* renderer, const SDL_Rect* clip = NULL);
protected:
	SDL_Texture* object;
	SDL_Rect rect;
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	//void loadMap(const char* path); // Doc thong tin tu file Map_data
	void loadTiles(SDL_Renderer* renderer); // Load hinh anh cho tile map
	void DrawMap(SDL_Renderer* renderer); // Fill hinh anh vao cac vi tri
	Map getMap() const { return firstMap; }

private:
	Map firstMap; // Chua thong tin ve ban do: trang thai, vi tri va chi so cua cac o tile map
	TileMap tile_map[mapNums]; // Mang luu tru cac loai hinh anh cho ban do
};

class GameMap2
{
public:
	GameMap2();
	~GameMap2();

	//void loadMap(const char* path); // Doc thong tin tu file Map_data
	void loadTiles(SDL_Renderer* renderer); // Load hinh anh cho tile map
	void DrawMap(SDL_Renderer* renderer); // Fill hinh anh vao cac vi tri
	Map2 getMap() const { return secondMap; }

private:
	Map2 secondMap; // Chua thong tin ve ban do: trang thai, vi tri va chi so cua cac o tile map
	TileMap tile_map[mapNums]; // Mang luu tru cac loai hinh anh cho ban do
};

#endif // !MAP_H
