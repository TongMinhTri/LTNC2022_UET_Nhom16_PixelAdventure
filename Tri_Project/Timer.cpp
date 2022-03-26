#include "Timer.h"

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

void Time::stop()
{
	is_paused = false;
	is_started = false;
}

void Time::pause()
{
	if (is_started && is_paused == false)
	{
		is_paused = true;
		pause_tick = SDL_GetTicks() - start_tick;
	}
}

void Time::resume()
{
	if (is_paused)
	{
		is_paused = false;
		start_tick = SDL_GetTicks() - pause_tick;
		pause_tick = 0;
	}
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

bool Time::is_start()
{
	return is_started;
}

bool Time::is_pause()
{
	return is_paused;
}

