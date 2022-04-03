#pragma once
#ifndef FRUITS_H
#define FRUITS_H
#include "BaseObject.h"
using namespace std;
#define w_h 48;
class Fruits
{
private:
	int x;
	int y;
	SDL_Rect frame_clips[17]{};//luu 17 frame
	int frame{};// bien chi so frame
	int frame_w = w_h;
	int frame_h = w_h;
	bool alive;
protected:
	SDL_Rect tes;
	SDL_Rect fruits;
	SDL_Texture* body;
public:
	Fruits();
	~Fruits();
	void kill() { alive = false; }
	void set_clips();// Khoi tao cac frame_clips
	void show_frame(SDL_Renderer* renderer);// In ra cac frame tuong ung voi su kien
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);//xet kich thuoc anh
	SDL_Rect getRect_fruits();
	void setFruits(SDL_Renderer* renderer, int a, int b, string path);
	bool get_alive() { return alive; }
};

#endif // !FRUITS_H


