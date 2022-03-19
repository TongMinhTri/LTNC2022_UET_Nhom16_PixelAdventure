#pragma once
#include "Object.h"
class Ninja_Frog: public Object
{
private:
	int x;
	int y;
	SDL_Rect frame_clips[12];//luu 12 frame
	Input input_type; // luu trang thai di chuyen
	int frame;// bien chi so frame
	int status;//2 trang thai left right

public:
	enum WalkType {
		Walk_right = 0,
		Walk_left,
		Idle_left,
		Idle_right,
	};
	Ninja_Frog();
 	Ninja_Frog(SDL_Renderer *renderer);
	~Ninja_Frog();
	void set_clips();// Khoi tao cac frame_clips
	void move(SDL_Event e, SDL_Renderer* renderer);//xu li su kien
	void show_frame(SDL_Renderer *renderer);// In ra cac frame tuong ung voi su kien
};
// source: https://www.youtube.com/watch?v=mv3LJCB9JJM&list=PLR7NDiX0QsfQQ2iFXsXepwH46wf3D4Y4C&index=26

