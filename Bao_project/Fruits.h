#pragma once
#ifndef FRUITS_H
#define FRUITS_H
#include "BoardGame.h"
using namespace std;

class Fruits
{
private:
	int x;
	int y;
	SDL_Rect frame_clips[17]{};//luu 17 frame
	int frame{};// bien chi so frame
protected:
	SDL_Rect fruits;
	SDL_Texture* body;
public:
	Fruits();
	Fruits(SDL_Renderer* renderer,string path);
	~Fruits();
	void set_clips();// Khoi tao cac frame_clips
	void show_frame(SDL_Renderer* renderer, string );// In ra cac frame tuong ung voi su kien
	void setImg(SDL_Renderer* renderer, string path);
	void setPos(int x, int y);//xet kich thuoc anh
	void setFruits(SDL_Renderer* renderer, int a, int b, string path);
	void Getx( int a);
};

#endif // !FRUITS_H


