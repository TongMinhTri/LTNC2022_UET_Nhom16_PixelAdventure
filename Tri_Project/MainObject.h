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

	bool LoadIMG(string path, SDL_Renderer* renderer);
	void showImage(SDL_Renderer* renderer);
	void handleMovement(SDL_Event event, SDL_Renderer* renderer);
	void setClips();
	void updatePlayerPosition(Map& map_data);
	void checkCollisionS(Map& map_data);
private:
	SDL_Texture* object;
	SDL_Rect rect;

	int x, y;
	int x_pos, y_pos;

	int frame_w, frame_h;

	SDL_Rect frame_clips[12]; //Luu frame
	Input input_type;
	int frame;
	int status;
	bool on_ground;
	bool jump;
};

#endif // !MAIN_OBJECT_H
