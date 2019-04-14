#include "App.h"
#include "c1CutsceneMoveEntity.h"
#include "m1Cutscene.h"
#include "c1CutsceneEntity.h"


c1CutsceneMoveEntity::c1CutsceneMoveEntity(uint start, uint duration, float speed_x, float speed_y, std::string entity) :c1CutsceneAction(start, duration)
{
	player_speed = {(int)speed_x, (int)speed_y };
	entity_name = entity;
}

void c1CutsceneMoveEntity::Execute(float dt)
{
	c1CutsceneEntity* element = nullptr;
	double start = App->cutscene_manager->GetTimer() - start_time;

	element = (c1CutsceneEntity*)App->cutscene_manager->elements.find(entity_name)->second;

	if (start < duration_time)
	{
		element->GetEntity()->position+= { (int)(player_speed.x * dt), (int)(player_speed.y * dt) };
		if (duration_time - start < 100)
		{
			element->GetEntity()->position = { 0,0 };
		}
	}
}
