#pragma once
#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include "BaseData.h"
using namespace std;

class BaseOject
{
public:
	BaseOject();
	~BaseOject();
	void SetRect(const int& x, const int& y)
	{
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect GetRect() const { return rect; }
	SDL_Texture* GetOject() const { return object; }

	virtual bool loadImg(string path, SDL_Renderer* ren);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

protected:
	SDL_Texture* object;
	SDL_Rect rect;
};

#endif // !BASE_OBJECT_H
