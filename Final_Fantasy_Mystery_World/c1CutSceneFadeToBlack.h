#ifndef __C1CUTSCENEFADETOBLACK_H__
#define __C1CUTSCENEFADETOBLACK_H__

#include "c1CutSceneAction.h"

class c1CutsceneFadeToBlack : public c1CutsceneAction
{
public:
	c1CutsceneFadeToBlack(uint start, uint duration, float fade_time);
	~c1CutsceneFadeToBlack();

	void Execute(float dt);
protected:
	bool fade;
	float durations;
	float time_fade = 0.0F;
};

#endif
