#include "App.h"
#include "c1CutSceneMoveEntity.h"
#include "m1Cutscene.h"
#include "c1CutSceneEntity.h"
#include "e1DynamicEntity.h"
#include "m1Map.h"
#include "p2Math.h"


c1CutsceneMoveEntity::c1CutsceneMoveEntity(uint start, uint duration, int origin_tile_x, int origin_tile_y, int destination_tile_x, int destination_tile_y, bool stop_on_goal, std::string entity_name) :c1CutsceneAction(start, duration), stop_on_goal(stop_on_goal)
{
	entity = (c1CutsceneEntity*)App->cutscene_manager->elements.find(entity_name)->second;

	origin = App->map->MapToWorldCentered(origin_tile_x, origin_tile_y);
	destination = App->map->MapToWorldCentered(destination_tile_x, destination_tile_y);
	
	origin -= entity->GetEntity()->pivot;
	destination -= entity->GetEntity()->pivot;
	
}

c1CutsceneMoveEntity::~c1CutsceneMoveEntity()
{
	
}

void c1CutsceneMoveEntity::Execute(float dt)
{
	double start = App->cutscene_manager->GetTimer() - start_time;

	if (start < duration_time)
	{
		lerp_by += speed;
		entity->GetEntity()->position = lerp(origin,destination,lerp_by).AproximateToIntCast();

		if (stop_on_goal &&lerp_by >= 1.0F) {
			duration_time = 0u;
		}
	}
	
}
