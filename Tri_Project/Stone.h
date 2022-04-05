#pragma once
#ifndef STONE_H
#define STONE_H
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
	int speed = 4;
	double speedx = 0.5;
	double speedy = 0.3;
	double v_x = 0;
	double v_y = 0;

	int x_val;
	int y_val;
	int limit_x;
	int limit_y;
	Input input_type;
protected:
	SDL_Rect stone;
	SDL_Rect test;
	SDL_Texture* body;
public:
	Stone();
	~Stone();
	Stone(SDL_Renderer* renderer,int x,int y,int limitx,int limity ,string path);
	void stone_move(SDL_Renderer* renderer, Map& map_data);
	//void show(SDL_Renderer* renderer);
	void setImg(SDL_Renderer* renderer, string path);
	void show_frame(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);//xet kich thuoc anh
	SDL_Rect getRect_stone();
	void set_Stone(SDL_Renderer* renderer, int a, int b, string path);
	void set_clips();
	void Stone_Move_Circle(SDL_Renderer* renderer,Map& map_data);
	void DoStone_Circle();


	void stone_move_up(SDL_Renderer* renderer, Map& map_data);
}

#endif // !STONE_H

;