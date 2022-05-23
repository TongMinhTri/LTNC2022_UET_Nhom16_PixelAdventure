#include "Text.h"
LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{

	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image! SDL_image Error: " << path.c_str() << IMG_GetError();
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			cout << "Unable to create texture from! SDL Error: " << path.c_str() << SDL_GetError();
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* Renderer)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
		if (mTexture != NULL)
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Renderer* renderer)
{
	SDL_Rect* clip = NULL;
	double angle = 0.0;
	SDL_Point* center = NULL;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}