#include "App.h"
#include "c1CutsceneEntity.h"
#include "m1EntityManager.h"
#include "m1Scene.h"

c1CutsceneEntity::c1CutsceneEntity(int pos_x, int pos_y, std::string name)
{
	if (strcmp(name.data(), "player") == 0) {
		entity = (e1Entity*)App->scene->player;
	}
}

c1CutsceneEntity::~c1CutsceneEntity()
{
	
}

e1Entity * c1CutsceneEntity::GetEntity()
{
	return entity;
}
