#include "App.h"
#include "c1CutSceneVibration.h"
#include "m1Input.h"
#include "m1Render.h"

c1CutsceneVibration::c1CutsceneVibration(uint start, uint duration) :c1CutsceneAction(start, duration)
{
	durations = duration;
	vibrate = true;
}
c1CutsceneVibration::~c1CutsceneVibration()
{

}
void c1CutsceneVibration::Execute(float dt)
{
	if (vibrate == true)
	{
		App->input->ControllerVibration(1.0F, durations);
		App->render->CameraTremble(0.83f, 1.5F);
		vibrate = false;
	}	
}