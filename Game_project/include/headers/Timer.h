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
	int get_ticks();

private:
	int start_tick;
	int pause_tick;

	bool is_paused;
	bool is_started;
};

#endif // !TIMER_H
