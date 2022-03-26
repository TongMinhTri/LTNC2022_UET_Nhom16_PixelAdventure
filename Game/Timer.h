#pragma once
#include "BaseData.h"
#ifndef TIMER_H
#define TIMER_H

class Time
{
public:
	Time();
	~Time();

	void start();
	void stop();
	void pause();
	void resume();

	int get_ticks();

	bool is_start();
	bool is_pause();
private:
	int start_tick;
	int pause_tick;

	bool is_paused;
	bool is_started;
};

#endif // !TIMER_H
