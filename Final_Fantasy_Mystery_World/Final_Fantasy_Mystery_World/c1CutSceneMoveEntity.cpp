#include "App.h"
#include "c1CutsceneMoveEntity.h"
#include "m1Cutscene.h"
#include "c1CutsceneEntity.h"
#include "e1DynamicEntity.h"


c1CutsceneMoveEntity::c1CutsceneMoveEntity(uint start, uint duration, float speed_x, float speed_y, std::string entity, Direction init_dir, Direction end_dir) :c1CutsceneAction(start, duration)
, end_direction(end_dir)
{
	player_speed = {(int)speed_x, (int)speed_y };
	ent = static_cast<e1DynamicEntity*>(((c1CutsceneEntity*)App->cutscene_manager->elements.find(entity)->second)->GetEntity());
	if (init_dir != Direction::NONE)
		ent->ChangeAnimation(init_dir, State::IDLE);
}

c1CutsceneMoveEntity::~c1CutsceneMoveEntity()
{
	ent->ChangeAnimsInCutscene(player_speed.x, player_speed.y, 2, ent->position.x, ent->position.y);
}

void c1CutsceneMoveEntity::Execute(float dt)
{
	double start = App->cutscene_manager->GetTimer() - start_time;

	if (start < duration_time)
	{
		ent->position+= { (int)(player_speed.x * dt), (int)(player_speed.y * dt) };
		ent->ChangeAnimsInCutscene(player_speed.x, player_speed.y, 1, ent->position.x, ent->position.y);
	}
	else {
		if (end_direction != Direction::NONE)
			ent->ChangeAnimation(end_direction, ent->state);
	}
	
}