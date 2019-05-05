#ifndef __P2TIMER_H__
#define __P2TIMER_H__

#include "p2Defs.h"

class p2Timer
{
public:

	// Constructor
	p2Timer();

	void Start();
	uint32 Read() const;
	float ReadSec() const;
	bool IsRunning() const;

private:
	uint32	started_at;
	bool running = false;
};

#endif //__p2Timer_H__