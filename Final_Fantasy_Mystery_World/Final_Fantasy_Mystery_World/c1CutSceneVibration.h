#ifndef __C1CUTSCENEVIBRATION_H__
#define __C1CUTSCENEVIBRATION_H__

#include "c1CutSceneAction.h"

class c1CutsceneVibration : public c1CutsceneAction
{
public:
	c1CutsceneVibration(uint start, uint duration);
	~c1CutsceneVibration();

	void Execute(float dt);
protected:
	uint durations;
	bool vibrate;
};

#endif
