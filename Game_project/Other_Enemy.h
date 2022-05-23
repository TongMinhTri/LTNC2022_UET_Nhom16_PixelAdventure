#pragma once
#ifndef OTHER_ENEMY_H
#define OTHER_ENEMY_H
#include "BaseData.h"
#include "Bullet.h"
using namespace std;

#define w_ 44;
#define h_ 30;

class Other_Enemy
{
private:
	int x;
	int y;
	int frame = 0;
	int number_frclips;
	SDL_Rect* frame_clips = new SDL_Rect[28];
	int frame_w;
	int frame_h;
	int speed = 4;
	double speedx = 0.6;
	double speedy = 0.4;
	double v_x = 0;
	double v_y = 0;
	int x_val;
	int y_val;
	int limit_x;
	int limit_y;
	int status;
protected:
	SDL_Rect enemy;
	SDL_Rect test;
	SDL_Texture* img_right, * img_left, * object;
public:
	Other_Enemy();
	~Other_Enemy();
	enum Direction_Type
	{
		RIGHT,
		LEFT,
	};
	void inita_enemy(SDL_Renderer* renderer, int x, int y, int limitx, int limity, int k, int Status, int w, int h);
	SDL_Texture* LoadIMG(string path, SDL_Renderer* renderer);
	void setIMG(SDL_Renderer* renderer, string k);
	void setPos(int x, int y);
	void show_frame(SDL_Renderer* renderer);
	SDL_Rect getRect_enemy();
	void set_clips();
	void enemy_move(SDL_Renderer* renderer);
	void enemy_move_normal(SDL_Renderer* renderer);
	void set_speedx(double a) { speedx = a; }
	void Free();
	int getRect_x()
	{
		return enemy.x;
	}
	int getRect_y()
	{
		return enemy.y;
	}
	int getDirection();
};

#endif // OTHER_ENEMY_H