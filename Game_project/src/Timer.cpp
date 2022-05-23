#include "Timer.h"

// Cac ham xu ly thoi gian va FPS
// Nguon tham khao: https://www.youtube.com/watch?v=qhqtxum_uA0

Time::Time()
{
	start_tick = pause_tick = 0;
	is_paused = is_started = false;
}

Time::~Time()
{
}

void Time::start()
{
	is_started = true;
	is_paused = false;
	start_tick = SDL_GetTicks();
}

int Time::get_ticks()
{
	if (is_started)
	{
		if (is_paused)
		{
			return pause_tick;
		}
		else
		{
			return SDL_GetTicks() - start_tick;
		}
	}

	return 0;
}


