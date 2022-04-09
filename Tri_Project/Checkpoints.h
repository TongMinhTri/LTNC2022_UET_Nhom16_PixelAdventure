#pragma once
#ifndef CHECKPOINTS_H
#define CHECKPOINTS_H
#include "BaseData.h"
using namespace std;

class Checkpoints
{
private:
	int x;
	int y;
	int frame = 0;
	int k;
	SDL_Rect frame_clips[26];
	int frame_w;
	int frame_h;

protected:
	SDL_Rect points;
	SDL_Rect test;
	SDL_Texture* body;
public:
	Checkpoints();
	~Checkpoints();
	void set_checkpoints(SDL_Renderer* renderer, int x_, int y_, int k_, int framew, string path);
	void setImg(SDL_Renderer* renderer, string path);
	void showImg(SDL_Renderer* renderer);
	void setPos(int x_, int y_);//xet kich thuoc anh
	void set_clips();
	SDL_Rect getRect_points();
};
#endif // !STONE_H