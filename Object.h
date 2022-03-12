#pragma once
#include "BoardGame.h"
using namespace std;
class Object
{
protected:
	SDL_Rect rect;
	SDL_Texture* body;
public:
	Object();
	Object(SDL_Renderer *renderer, string path);
	~Object();
	void show(SDL_Renderer *renderer);
	void setImg(SDL_Renderer *renderer,string path);
	void setPos(int x, int y);//xet kich thuoc anh
	SDL_Rect getRect() const { return rect; }
	void Getx(int x);
	void Gety(int y);

};

