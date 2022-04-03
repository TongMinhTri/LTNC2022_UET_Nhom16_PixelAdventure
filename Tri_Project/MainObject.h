#pragma once
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "BaseData.h"
#include "BaseObject.h"

class MainObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType
	{
		IDLE_RIGHT = 0,
		IDLE_LEFT = 1,
		WALK_RIGHT = 2,
		WALK_LEFT = 3,
		JUMP_RIGHT = 4,
		JUMP_LEFT = 5,
		FALL_RIGHT = 6,
		FALL_LEFT = 7,
	};

	SDL_Texture* LoadIMG(string path, SDL_Renderer* renderer);
	void showImage(SDL_Renderer* renderer);
	void setIMG(SDL_Renderer* renderer);
	void handleMovement(SDL_Event event, SDL_Renderer* renderer);
	void setClips();
	void updatePlayerPosition(Map& map_data);
	void checkCollisionS(Map& map_data);
	SDL_Rect getRect();
	void setPos(int x, int y);
private:
	SDL_Texture *img_run_right, *img_run_left, *img_idle_right, *img_idle_left, *img_jump_right, *img_jump_left, *img_fall_right, *img_fall_left, *object;
	SDL_Rect rect;
	SDL_Rect test;
	int x, y;
	int x_pos, y_pos;

	int frame_w, frame_h;

	SDL_Rect frame_clips[12]; //Luu frame
	Input input_type;
	int frame;
	int status;
	bool on_ground;
	bool jump;
	int move_stone = 0;
};

#endif // !MAIN_OBJECT_H
