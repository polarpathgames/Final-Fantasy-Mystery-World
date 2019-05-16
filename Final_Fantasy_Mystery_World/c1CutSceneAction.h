#ifndef _C1CUTSCENEACTION_H_
#define _C1CUTSCENEACTION_H_
#include "p2Defs.h"
#include "p2PerfTimer.h"

class c1CutsceneAction {
public:

	c1CutsceneAction(uint start, uint duration)
	{
		start_time = start;
		duration_time = duration;
	};

	virtual ~c1CutsceneAction() {};

	virtual void Execute(float dt) {};

public:
	uint start_time;
	uint duration_time;
};

#endif // !