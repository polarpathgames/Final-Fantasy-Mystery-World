#include "App.h"
#include "m1CutScene.h"
#include "c1CutSceneDeleteEntity.h"



c1CutSceneDeleteEntity::c1CutSceneDeleteEntity(uint start, uint duration, std::string name) :c1CutsceneAction(start, duration)
{
	names = name;
}
c1CutSceneDeleteEntity::~c1CutSceneDeleteEntity()
{

}

void c1CutSceneDeleteEntity::Execute(float dt)
{

	if (strcmp(names.data(), "daughter") == 0)
	{
		App->cutscene_manager->ent->to_delete = true;
	}
	else if (strcmp(names.data(), "icequeen") == 0)
	{
		App->cutscene_manager->ent->to_delete = true;
	}
		
}