// ----------------------------------------------------
// p2PerfTimer.cpp
// Slow timer with microsecond precision
// ----------------------------------------------------

#include "p2PerfTimer.h"
#include "SDL\include\SDL_timer.h"

uint64 p2PerfTimer::frequency = 0;

// ---------------------------------------------
p2PerfTimer::p2PerfTimer()
{
	if(frequency == 0)
		frequency = SDL_GetPerformanceFrequency();

	Start();
}

// ---------------------------------------------
void p2PerfTimer::Start()
{
	started_at = SDL_GetPerformanceCounter();
}

// ---------------------------------------------
double p2PerfTimer::ReadMs() const
{
	return 1000.0 * (double(SDL_GetPerformanceCounter() - started_at) / double(frequency));
}

// ---------------------------------------------
uint64 p2PerfTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - started_at;
}

double p2PerfTimer::StartedAt()
{
	return started_at;
}


