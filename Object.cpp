#include "Object.h"

Object::Object()
{
	rect.x = 200;
	rect.y = 200;
	rect.w = 32;
	rect.h = 32;
	body = NULL;
}

Object::Object(SDL_Renderer* renderer, std::string path)
{
	rect.x = 200;
	rect.y = 200;
	rect.w = 32;
	rect.h = 32;
	body = BG::loadTexture(renderer, path);
}

Object::~Object()
{
	

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

void Object::Gety( int y)
{
	rect.y += y;
}

void Object::Getx( int x )
{
	rect.x += x;
}
