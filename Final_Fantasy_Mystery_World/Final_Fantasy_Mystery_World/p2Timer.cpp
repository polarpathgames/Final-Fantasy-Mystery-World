// ----------------------------------------------------
// p2Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "p2Timer.h"
#include "p2Log.h"
#include "SDL/include/SDL_timer.h"

// ---------------------------------------------
p2Timer::p2Timer(bool start)
{
	if (start) {
		Start();
		running = true;
	}
}

// ---------------------------------------------
void p2Timer::Start()
{
	started_at = SDL_GetTicks();
	running = true;
}

// ---------------------------------------------
uint32 p2Timer::Read() const
{
	if (running)
		return SDL_GetTicks() - started_at;
	else {
		LOG("timer not running");
		return 0u;
	}
}

// ---------------------------------------------
float p2Timer::ReadSec() const
{
	if (running)
		return float(SDL_GetTicks() - started_at) / 1000.0f;
	else {
		LOG("timer not running");
		return 0u;
	}
}

void p2Timer::Stop()
{
	running = false;
}

bool p2Timer::IsRunning() const
{
	return running;
}
