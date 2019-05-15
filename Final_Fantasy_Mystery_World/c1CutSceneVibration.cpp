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
		App->input->ControllerVibration(1.5F, durations);
		App->render->CameraTremble(1.0F, 10.3F);
		vibrate = false;
	}	
}