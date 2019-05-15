#include "App.h"
#include "c1CutSceneFadeToBlack.h"
#include "m1FadeToBlack.h"

c1CutsceneFadeToBlack::c1CutsceneFadeToBlack(uint start, uint duration) : c1CutsceneAction(start, duration)
{
	durations = duration;
	fade = true;
}
c1CutsceneFadeToBlack::~c1CutsceneFadeToBlack()
{

}

void c1CutsceneFadeToBlack::Execute(float dt)
{
	if (fade == true)
	{
		App->fade_to_black->FadeToBlack(true,durations);
		fade = false;
	}
}