#pragma once
#ifndef SPIKE_H
#define STONE_H
#include "BaseData.h"
using namespace std;

class Spike
{
private:
	int x;
	int y;
protected:
	SDL_Rect tes;
	SDL_Rect spike;
	SDL_Texture* body;
public:
	Spike();
	~Spike();
	void set_spike(SDL_Renderer* renderer, int a, int b, int c, string path);
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);//xet kich thuoc anh
	void showImg(SDL_Renderer* renderer);
	SDL_Rect getRect_spike();
	void Free();
};


#endif // !SPIKE_H



