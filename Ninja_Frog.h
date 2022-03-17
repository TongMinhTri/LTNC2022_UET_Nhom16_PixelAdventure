#pragma once
#include "Object.h"
class Ninja_Frog: public Object
{
private:
	int x;
	int y;
	int width_frame;
	int height_frame;
	SDL_Rect frame_clips[12];//12 hinh 
	Input input_type; // bien luu trang thai
	int frame;// bien chi so frame
	int status;//2 trang thai left right

public:
	enum WalkType {
		Walk_right = 0,
		Walk_left = 1,
	};
	Ninja_Frog();
 	Ninja_Frog(SDL_Renderer *renderer);
	~Ninja_Frog();
	void move(SDL_Event e);
	void set_clips();
	void show_frame(SDL_Renderer *renderer);
};

