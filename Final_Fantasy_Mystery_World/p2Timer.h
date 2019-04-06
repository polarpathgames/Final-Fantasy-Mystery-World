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

private:
	uint32	started_at;
};

#endif //__p2Timer_H__