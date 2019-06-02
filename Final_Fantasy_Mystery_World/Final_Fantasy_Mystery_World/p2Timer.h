#ifndef __P2TIMER_H__
#define __P2TIMER_H__

#include "p2Defs.h"

class p2Timer
{
public:

	// Constructor
	p2Timer(bool start = true);

	void Start();
	uint32 Read() const;
	float ReadSec() const;
	void Stop();
	bool IsRunning() const;

private:
	uint32	started_at = 0u;
	bool running = false;
};

#endif //__p2Timer_H__