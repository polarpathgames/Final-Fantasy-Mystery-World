#include "App.h"
#include "m1Render.h"
#include "c1CutsceneMoveCamera.h"
#include "m1CutScene.h"

c1CutsceneMoveCamera::c1CutsceneMoveCamera(uint start, uint duration, int speed_x, int speed_y) :c1CutsceneAction(start, duration)
{
	camera_speed.x = speed_x;
	camera_speed.y = speed_y;

}

void c1CutsceneMoveCamera::Execute(float dt)
{
	double start = App->cutscene_manager->GetTimer() - start_time;

	if (start < duration_time)
	{
		App->render->camera.x -= camera_speed.x * dt;
		App->render->camera.y -= camera_speed.y * dt;
	}
}
