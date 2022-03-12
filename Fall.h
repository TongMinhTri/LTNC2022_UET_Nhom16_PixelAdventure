#pragma once
#include "Object.h"
class Fall: public Object
{
private:
	int x;
	int y;
public:
	Fall(SDL_Renderer *renderer);
	~Fall();
	void move(SDL_Event e);
};

