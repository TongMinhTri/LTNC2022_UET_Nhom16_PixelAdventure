#include "Checkpoints.h"

Checkpoints::Checkpoints()
{
	x = 0;
	y = 0;
	points.x = points.y = points.h = points.w = 0;
	test.x = test.y = 0;
	test.w = test.h = 64;
	k = 0;
}

Checkpoints::~Checkpoints()
{
}
void Checkpoints::set_checkpoints(SDL_Renderer* renderer, int x_, int y_, int k_,int framew, string path)
{
	x = x_;
	y = y_;
	k = k_;
	setPos(x, y);
	frame = 0;
	frame_w = framew;
	frame_h = framew;
	points.w = framew;
	points.h = framew;
	test.x = test.y = 0;
	test.w = test.h = framew;
	setImg(renderer, path);
}
void Checkpoints::setImg(SDL_Renderer* renderer, string path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface != NULL)
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture != NULL)
		{
			points.w = loadedSurface->w;
			points.h = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	body = newTexture;
}
void Checkpoints::showImg(SDL_Renderer* renderer)
{
	frame++;
	if (frame >=k) frame = 0; // ngan cho frame ko qua k
	SDL_Rect* current_clips = &frame_clips[frame]; // rect nguon de in ra anh
	SDL_Rect renderquad = { x, y, frame_w, frame_h };
	SDL_RenderCopy(renderer, body, current_clips, &renderquad);
}
void Checkpoints::setPos(int x_, int y_)
{
	points.x = x_;
	points.y = y_;
}
void Checkpoints::set_clips()
{
	for (int i = 0; i < k; i++)
	{
		frame_clips[i].x = i * frame_w;
		frame_clips[i].y = 0;
		frame_clips[i].w = frame_w;
		frame_clips[i].h = frame_w;
	}
}
SDL_Rect Checkpoints::getRect_points()
{
	test.x = points.x;
	test.y = points.y;
	test.w = frame_w;
	test.h = frame_h;
	return test;
}
