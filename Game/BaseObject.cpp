#include "BaseObject.h"

BaseOject::BaseOject()
{
	object = NULL;
	rect.x = rect.y = rect.w = rect.h = 0;
}

BaseOject::~BaseOject() { Free(); }

bool BaseOject::loadImg(string path, SDL_Renderer* ren)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newTexture = SDL_CreateTextureFromSurface(ren, loadedSurface);
		if (newTexture != NULL)
		{
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	object = newTexture;

	return object != NULL;
}

void BaseOject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect r = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderCopy(des, object, clip, &r);
}

void BaseOject::Free()
{
	if (object != NULL)
	{
		SDL_DestroyTexture(object);
		object = NULL;
		rect.w = rect.h = 0;
	}
}
