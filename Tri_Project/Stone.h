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
	SDL_Rect frame_clips[20];//luu 20 frame
	int frame_w = w_h;
	int frame_h = w_h;
	int speed = 4;
	double speedx = 1;
	double speedy = 0.4;
	double v_x = 0;
	double v_y = 0;
	int number_frame;
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
	void init_stone(SDL_Renderer* renderer, int x, int y, int limitx, int limity, string path, int k);
	void stone_move(SDL_Renderer* renderer);
	//void show(SDL_Renderer* renderer);
	void setImg(SDL_Renderer* renderer, string path);
	void show_frame_up(SDL_Renderer* renderer, double speed_run);
	void setPos(int x, int y);//xet kich thuoc anh
	SDL_Rect getRect_stone();
	void set_Stand(SDL_Renderer* renderer, int a, int b, string path);
	void set_clips();
	void Stone_Move_Circle(SDL_Renderer* renderer);
	void DoStone_Circle();
	void stone_move_up(SDL_Renderer* renderer);
	void show_stand(SDL_Renderer* renderer);
}

#endif // !STONE_H

;