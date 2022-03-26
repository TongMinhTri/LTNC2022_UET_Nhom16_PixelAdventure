#include "Object.h"

Object::Object()
{
	rect.x = 434;
	rect.y = 187;
	rect.w = 32;
	rect.h = 32;
	body = NULL;
}

Object::~Object()
{
	

}

Object::Object(SDL_Renderer* renderer, std::string path)
{
	rect.x = 434;
	rect.y = 197;
	rect.w = 32;
	rect.h = 32;
	body = BG::loadTexture(renderer, path);
}



void Object::show(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, body, NULL, &rect);
}

void Object::setImg(SDL_Renderer* renderer, string path)
{
	body = BG::loadTexture(renderer, path);
}


void Object::setPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void Object::Gety( int a )
{
	rect.y += a;
}

void Object::Getx( int a )
{
	rect.x += a;
}
