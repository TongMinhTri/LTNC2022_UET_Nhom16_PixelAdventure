#pragma once
#ifndef BULLET_H
#define BULLET_H
#include "BaseData.h"
using namespace std;

class Bullet
{
private:
	int x_pos;
	int y_pos;
	bool isMove;
	int speed_bullet;
	SDL_Rect bullet;
	SDL_Rect test;
	SDL_Texture* body;
public:
	Bullet();
	~Bullet();
	void set_bullet(SDL_Renderer* renderer,int x_, int y_,string path);
	void fire_left();
	void fire_right();
	void setStatus(bool isMove_);
	bool is_move() { return isMove; }
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x_ ,int y_);
	SDL_Rect getRect_bullet();
	void show(SDL_Renderer* renderer);
	void Free();
};

#endif // BULLET_H