#include "App.h"
#include "c1CutsceneMoveEntity.h"
#include "m1Cutscene.h"
#include "c1CutsceneEntity.h"
#include "e1DynamicEntity.h"
#include "p2Log.h"


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
	ent->ChangeAnimsInCutscene(player_speed.x, player_speed.y, 2);
	
}

void c1CutsceneMoveEntity::Execute(float dt)
{
	c1CutsceneEntity* element = nullptr;
	double start = App->cutscene_manager->GetTimer() - start_time;

	element = (c1CutsceneEntity*)App->cutscene_manager->elements.find(entity_name)->second;

	if (start < duration_time)
	{
		element->GetEntity()->position += { floor(player_speed.x * dt), floor(player_speed.y * dt) };
		LOG("( %.2f, %.2f)", element->GetEntity()->position.x, element->GetEntity()->position.y);
		e1DynamicEntity* ent = (e1DynamicEntity*)element->GetEntity();
		ent->ChangeAnimsInCutscene(player_speed.x, player_speed.y, 1);
	}	
}