#pragma once
#ifndef TEXT_H
#define TEXT_H

#include "BaseData.h"
using namespace std;

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(std::string path, SDL_Renderer* renderer);

	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* renderer);
	void free();
	void render(int x, int y, SDL_Renderer *renderer);
	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};

#endif // !TEXT_H



