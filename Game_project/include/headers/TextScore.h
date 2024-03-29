#pragma once
#ifndef TEXTSCORE_H
#define TEXTSCORE_H
#include "BaseData.h"
using namespace std;
class TextScore
{
private:
	string str;
	SDL_Color text_color;
	SDL_Surface* textSurface;
protected:
	SDL_Rect rect;
	SDL_Rect test;
	SDL_Texture* body;
public:
	enum TextColor {
		RED = 0,
		WHITE = 1,
		BLACK = 2,
	};
	TextScore();
	~TextScore();
	TextScore(int x, int y, int k);
	void init(int x, int y);
	void setPos(int x, int y);
	void initText(TTF_Font*& fontText, int k);
	void setText(string text)
	{
		str = text;
	}
	void set_W(int k)
	{
		rect.w = k;
	}
	void setColor(const int& type);
	void createText(TTF_Font* font, SDL_Renderer* renderer, bool check_score);
	void show(SDL_Renderer* renderer);
	void Free();
};

#endif // !TEXTSCORE_H