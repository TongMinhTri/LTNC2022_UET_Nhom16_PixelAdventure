#pragma once
#ifndef FRUITS_H
#define FRUITS_H
#include "BaseObject.h"
using namespace std;
#define w_h 48;
class Fruits
{
private:
	int x;
	int y;
	SDL_Rect frame_clips[17]{}; 
	int frame{};
	int frame_w = w_h;
	int frame_h = w_h;
	bool check_collect[9];
protected:
	SDL_Rect tes;
	SDL_Rect fruits;
	SDL_Texture* body;
public:
	bool alive;
	Fruits();
	~Fruits();
	void kill() { alive = false; }
	void set_clips();
	void showImg(SDL_Renderer* renderer);
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);
	SDL_Rect getRect_fruits();
	void setFruits(SDL_Renderer* renderer, int a, int b, string path);
	void Free();
};

#endif // !FRUITS_H


