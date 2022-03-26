#pragma once
#ifndef ROCKHEAD_H
#define ROCKHEAD_H
#include "Object.h"


class RockHead : public Object
{
private:
	int x;
	int y;
	int z;
	int x_val;
	int y_val;
	SDL_Rect frame_clips[4];//luu 4 frame
	Input_ input_type_; // luu trang thai di chuyen
	int frame;// bien chi so quan ly frame
	int status;
	
	int type_move;
	int animation_a;
	int animation_b;

public:
	enum TypeMove {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};
	RockHead();
	RockHead(SDL_Renderer* renderer,int x,int y);
	RockHead(SDL_Renderer* renderer, int x, int y, int z);
	~RockHead();
	void set_clips();// Khoi tao cac frame_clips
	//void move(SDL_Event e, SDL_Renderer* renderer);//xu li su kien
	void set_x_val(int& xval) { x_val = xval; }
	void set_y_val(int& yval) { y_val = yval; }

	void set_x(int& xpos) {	x = xpos; }
	void set_y(int& ypos) { y = ypos; }

	int get_x_pos() { return x; }
	int get_y_pos() { return y; }
	//void setmap(int& mp_x, int& mp_y) { map_x = mp_x; map_y = mp_y; }
	void show_frames(SDL_Renderer* renderer);
	void Doplayer_left();
	void Doplayer_up();
	void Doplayer_upandleft();
	void set_type_move(const int& typeMove)
	{
		type_move = typeMove;
	}
	void setAnimationPos(const int& pos_a, const int& pos_b)
	{
		animation_a = pos_a;
		animation_b = pos_b;
	}
	void set_input_left(const int& ipLeft)
	{
		input_type_.left = ipLeft;
	};
	void ImMoveType(SDL_Renderer* renderer);
	void ImMoveType_Up(SDL_Renderer* renderer);
	void ImMoveType_UpandLeft(SDL_Renderer* renderer);
};
#endif 