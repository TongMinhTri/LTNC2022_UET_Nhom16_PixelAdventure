#pragma once
#ifndef HEART_H
#define HEART_H
#include "BaseData.h"
using namespace std;

class Heart
{
private:
	int x;
	int y;
	int size;
	int number;
<<<<<<< HEAD
	vector<int> life;
=======
	vector <int> life;
>>>>>>> 55a6b9e3ed8d1c1badec5ebe0a2a64ed73fab2f7
	bool dead = false;
protected:
	SDL_Rect test;
	SDL_Rect heart;
	SDL_Texture* body;
public:
	Heart();
	~Heart();
	void show(SDL_Renderer* renderer);
	void kill() { dead = true; }
	void live() { dead = false; }
	bool isKill() { return dead; }
	void setImg(SDL_Renderer* renderer, string path);
<<<<<<< HEAD
	void setPos(int x, int y);
=======
	void setPos(int x, int y); 
>>>>>>> 55a6b9e3ed8d1c1badec5ebe0a2a64ed73fab2f7
	void setHeart(SDL_Renderer* renderer, int a, int b);

};

<<<<<<< HEAD
#endif // !HEART_H
=======
#endif // !HEART_H
>>>>>>> 55a6b9e3ed8d1c1badec5ebe0a2a64ed73fab2f7
