#ifndef __P2PERFTIMER_H__
#define __P2PERFTIMER_H__

#include "p2Defs.h"

class p2PerfTimer
{
public:

	// Constructor
	p2PerfTimer();

	void Start();
	double ReadMs() const;
	uint64 ReadTicks() const;
	double StartedAt();

private:
	uint64	started_at;
	static uint64 frequency;
};

#endif //__P2PERFTIMER_H__