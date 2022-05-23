#pragma once
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "BaseData.h"
#include "BaseObject.h"

class MainObject
{
public:
	MainObject( int a, int b);
	~MainObject();

	enum WalkType
	{
		IDLE_RIGHT,
		IDLE_LEFT,
		WALK_RIGHT,
		WALK_LEFT,
		JUMP_RIGHT,
		JUMP_LEFT,
		FALL_RIGHT,
		FALL_LEFT,
	};

	SDL_Texture* LoadIMG(string path, SDL_Renderer* renderer);
	void showImage(SDL_Renderer* renderer);
	void setIMG(SDL_Renderer* renderer, string s);
	void handleMovement(SDL_Event event, SDL_Renderer* renderer, Mix_Chunk* soundEffect[]);
	void setClips();
	void updatePlayerPosition(Map& map_data);
	void updatePlayerPosition2(Map2& map_data);
	void checkCollisionS(Map& map_data);
	void checkCollisionS2(Map2& map_data);
	SDL_Rect getRect();
	void setPos(int x, int y);
	bool checkWin();
	void Free();
private:
	SDL_Texture *img_run_right, *img_run_left, *img_idle_right, *img_idle_left, *img_jump_right, *img_jump_left, *img_fall_right, *img_fall_left, *object;
	SDL_Rect rect;
	SDL_Rect test;
	int x, y;
	int x_pos, y_pos;

	int frame_w, frame_h;

	SDL_Rect frame_clips[12];
	Input input_type;
	int frame;
	int status;
	bool on_ground;
	bool jump;
	int move_stone = 0;
};

#endif // !MAIN_OBJECT_H
