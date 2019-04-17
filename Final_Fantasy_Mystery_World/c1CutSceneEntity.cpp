#include "App.h"
#include "c1CutsceneEntity.h"
#include "m1EntityManager.h"
#include "m1Scene.h"

c1CutsceneEntity::c1CutsceneEntity(int pos_x, int pos_y, std::string name)
{
	if (strcmp(name.data(), "player") == 0) {
		entity_c = (e1Entity*)App->scene->player;
	}
	else if (strcmp(name.data(), "daughter") == 0) {
		entity_c = App->entity_manager->CreateEntity(e1Entity::EntityType::DAUGHTER, 195, 349, name);
		
	}
}

c1CutsceneEntity::~c1CutsceneEntity()
{
	entity_c->to_delete = true;
}

e1Entity * c1CutsceneEntity::GetEntity()
{
	return entity_c;
}
