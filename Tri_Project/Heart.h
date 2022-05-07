#pragma once
#ifndef HEART_H
#define HEART_H
#include "BaseData.h"
using namespace std;

class Heart
{
private:
	int x;
	int y;
	int size;
	int number;
	vector<int> life;
	bool dead = false;
protected:
	SDL_Rect test;
	SDL_Rect heart;
	SDL_Texture* body;
public:
	Heart();
	~Heart();
	void show(SDL_Renderer* renderer);
	void kill() { dead = true; }
	void live() { dead = false; }
	bool isKill() { return dead; }
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);
	void setHeart(SDL_Renderer* renderer, int a, int b);

};

#endif // !HEART_H