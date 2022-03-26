#pragma once
#ifndef NINJA_FROG_H
#define NINJA_FROG_H
#include "BoardGame.h"
using namespace std;

struct Input // kieu de ckeck input dau vao
{
	int left;
	int right;
	int up;
	int down;
	int jump;
	int idle_l;
	int idle_r;
	Input()
	{
		left = 0;
		right = 0;
		up = 0;
		down = 0;
		jump = 0;
		idle_l = 0;
		idle_r = 0;
	}
};

class Ninja_Frog
{
private:
	int x;
	int y;
	SDL_Rect frame_clips[11]{};//luu 12 frame
	Input input_type; // luu trang thai di chuyen
	int frame;// bien chi so frame
	int status;//2 trang thai left right
	bool dichuyen;
	set<int>direct;
protected:
	SDL_Rect ninja_frog;
	SDL_Texture* body;
public:
	enum WalkType {
		Walk_right = 0,
		Walk_left = 1,
		Idle_left = 2,
		Idle_right = 3,
		Jump = 4,
	};
	Ninja_Frog();
 	Ninja_Frog(SDL_Renderer *renderer);
	~Ninja_Frog();
	void set_clips();// Khoi tao cac frame_clips
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int a, int b);
	void keyboard_input(SDL_Event e, SDL_Renderer* renderer);//xu li su kien
	void show_frame(SDL_Renderer *renderer);// In ra cac frame tuong ung voi su kien
	void handle_move();
	string direct1 = "";
	vector<int> check;

};
// source: https://www.youtube.com/watch?v=mv3LJCB9JJM&list=PLR7NDiX0QsfQQ2iFXsXepwH46wf3D4Y4C&index=26

#endif // !NINJA_FROG_H
