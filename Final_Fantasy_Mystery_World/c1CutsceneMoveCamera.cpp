#include "App.h"
#include "m1Render.h"
#include "c1CutsceneMoveCamera.h"
#include "m1Cutscene.h"


c1CutsceneMoveCamera::c1CutsceneMoveCamera(uint start, uint duration, int origin_x, int origin_y, int destination_x, int destination_y, float speed, bool stop_when_goal) :c1CutsceneAction(start, duration), 
	speed(speed), stop_when_goal(stop_when_goal)
{
	camera_origin.create(origin_x, origin_y);
	camera_destination.create(destination_x, destination_y);
}

void c1CutsceneMoveCamera::Execute(float dt)
{
	double start = App->cutscene_manager->GetTimer() - start_time;

	if (start < duration_time)
	{
		lerp_by += speed;
		iPoint position = l.lerp(camera_origin, camera_destination, lerp_by).AproximateToIntCast();
		App->render->camera.x = position.x;
		App->render->camera.y = position.y;

		if (stop_when_goal) {
			if (lerp_by >= 1.0f) {
				duration_time = 0u;
			}
		}
	}
}
