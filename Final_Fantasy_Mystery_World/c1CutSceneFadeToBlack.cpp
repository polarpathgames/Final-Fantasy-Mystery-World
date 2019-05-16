#include "App.h"
#include "c1CutSceneFadeToBlack.h"
#include "m1FadeToBlack.h"

c1CutsceneFadeToBlack::c1CutsceneFadeToBlack(uint start, uint duration, float fade_time) : c1CutsceneAction(start, duration)
{
	durations = duration;
	fade = true;
	time_fade = fade_time;
}
c1CutsceneFadeToBlack::~c1CutsceneFadeToBlack()
{

}

void c1CutsceneFadeToBlack::Execute(float dt)
{
	if (fade == true)
	{
		App->fade_to_black->FadeToBlack(time_fade);
		fade = false;
	}
}