#pragma once
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "BaseData.h"
#include "BaseObject.h"

class MainObject : public BaseOject
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

	bool LoadIMG(string path, SDL_Renderer* renderer);
	void show(SDL_Renderer* des);
	void handleEvents(SDL_Event event, SDL_Renderer* renderer);
	void setClips();
	void doPlayer(Map& map_data);
	void checkMap(Map& map_data);
private:
	int x, y;
	int x_pos, y_pos;

	int frame_w, frame_h;

	SDL_Rect frame_clip_run[12]; //Luu frame
	Input input_type;
	int frame;
	int status;
	bool on_ground;
	bool jump;
};

#endif // !MAIN_OBJECT_H
