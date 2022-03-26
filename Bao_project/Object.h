#pragma once
#include "BoardGame.h"
using namespace std;

struct Input_ // kieu de ckeck input dau vao
{
	int left;
	int right;
	int up;
	int down;
	int jump;
	int idle_l;
	int idle_r;
	Input_()
	{
		left = 0;
		right = 0;
		up = 0;
		down = 0;
		jump = 0;
		idle_l = 0;
		idle_r = 0;
	}
};

class Object
{
protected:
	SDL_Rect rect;
	SDL_Texture* body;
public:
	Object();
	Object(SDL_Renderer* renderer, string path);
	~Object();
	void show(SDL_Renderer* renderer);
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);//xet kich thuoc anh
	SDL_Rect getRect() const { return rect; }
	void Getx(int x);
	void Gety(int y);

};
