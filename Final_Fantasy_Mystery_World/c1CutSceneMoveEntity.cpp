#include "App.h"
#include "c1CutsceneMoveEntity.h"
#include "m1Cutscene.h"
#include "c1CutsceneEntity.h"
#include "e1DynamicEntity.h"


c1CutsceneMoveEntity::c1CutsceneMoveEntity(uint start, uint duration, float speed_x, float speed_y, std::string entity) :c1CutsceneAction(start, duration)
{
	player_speed = {(int)speed_x, (int)speed_y };
	entity_name = entity;
}

c1CutsceneMoveEntity::~c1CutsceneMoveEntity()
{
	c1CutsceneEntity* element = nullptr;
	element = (c1CutsceneEntity*)App->cutscene_manager->elements.find(entity_name)->second;
	e1DynamicEntity* ent = (e1DynamicEntity*)element->GetEntity();
	ent->ChangeAnimsInCutscene(player_speed.x, player_speed.y, 2, ent->position.x, ent->position.y);
	
}

void c1CutsceneMoveEntity::Execute(float dt)
{
	c1CutsceneEntity* element = nullptr;
	double start = App->cutscene_manager->GetTimer() - start_time;

	element = (c1CutsceneEntity*)App->cutscene_manager->elements.find(entity_name)->second;

	if (start < duration_time)
	{
		element->GetEntity()->position+= { (int)(player_speed.x * dt), (int)(player_speed.y * dt) };
		e1DynamicEntity* ent = (e1DynamicEntity*)element->GetEntity();
		ent->ChangeAnimsInCutscene(player_speed.x, player_speed.y, 1, ent->position.x, ent->position.y);
	}
	
}
