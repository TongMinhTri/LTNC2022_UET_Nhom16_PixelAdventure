#pragma once
#include "BoardGame.h"
using namespace std;
class Background
{
protected:
	SDL_Rect rect;
	SDL_Texture* body;
public:
	Background();
	~Background();
	Background(SDL_Renderer* renderer, string path);
	void show(SDL_Renderer* renderer, int x, int y, int w, int h);
	void setImg(SDL_Renderer* renderer, string path);
	SDL_Rect getRect() const { return rect; }
};

