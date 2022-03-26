#pragma once
#ifndef TIME_H
#define TIME_H

#include <SDL_timer.h>
#include "BoardGame.h"

class Time
{
public: 
	Time();
	~Time();
	void start(); 
	void stop();
	void paused();
	void unpaused();

	int get_ticks();
	bool is_started();
	bool is_paused();

private:
	int start_tick; // tra ve time tu khi chay 
	int paused_tick;// thoi diem dung 
	bool is_paused_;// danh dau dang dung
	bool is_started_;// danh dau dang chay
};

#endif // !TIME_H