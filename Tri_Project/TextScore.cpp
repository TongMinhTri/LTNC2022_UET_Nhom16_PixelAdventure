#include "TextScore.h"

TextScore::TextScore()
{
	rect.x = 400;
	rect.y = 10;
	rect.w = 100;
	rect.h = 30;
	setColor(2);
}

TextScore::~TextScore()
{
}

TextScore::TextScore(int x, int y, int k)
{
	setPos(x, y);
	rect.w = k;
	rect.h = 30;
	setColor(2);
}

void TextScore::initText(TTF_Font*& fontText)
{
	if (TTF_Init() == -10)
		cout << -1;
	fontText = TTF_OpenFont("SHOWG.ttf", 20);
	if (fontText == NULL)
		cout << "Font Error!" << endl;

}

void TextScore::setColor(const int& type)
{
	if (type == RED)
	{
		SDL_Color color = { 255,0,0 };
		text_color = color;
	}
	else if (type == WHITE) {
		SDL_Color color = { 255,255,255 };
		text_color = color;
	}
	else {
		SDL_Color color = { 0,0,0 };
		text_color = color;
	}
}

void TextScore::createText(TTF_Font* font, SDL_Renderer* renderer, bool check_score)
{
	if (check_score)
	{
		textSurface = TTF_RenderText_Blended(font, str.c_str(), text_color);
		body = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
	}
}

void TextScore::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
void TextScore::show(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, body, NULL, &rect);
}