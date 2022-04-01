#pragma once
#ifndef STONE
#define STONE

#include "BaseObject.h"
#include "BaseData.h"

#define w_h 48;
class Stone
{
private:
	int x;
	int y;
	int state = 0;
	int frame = 0;
	SDL_Rect frame_clips[4]{};//luu 17 frame
	int frame_w = w_h;
	int frame_h = w_h;
	int speed = 3;
protected:
	SDL_Rect stone;
	SDL_Rect test;
	SDL_Texture* body;
public:
	Stone();
	~Stone();
	void stone_move(SDL_Renderer* renderer, Map& map_data);
	//void show(SDL_Renderer* renderer);
	void setImg(SDL_Renderer* renderer, string path);
	void show_frame(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);//xet kich thuoc anh
	SDL_Rect getRect_stone();
	void set_Stone(SDL_Renderer* renderer, int a, int b, string path);
	void set_clips();
}

#endif // !STONE

;

