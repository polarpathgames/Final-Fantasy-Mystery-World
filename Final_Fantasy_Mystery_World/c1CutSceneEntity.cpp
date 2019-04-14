#include "App.h"
#include "c1CutsceneEntity.h"
#include "m1EntityManager.h"

c1CutsceneEntity::c1CutsceneEntity(int pos_x, int pos_y, std::string name)
{
	entity = App->entity_manager->CreateEntity(e1Entity::EntityType::PLAYER, pos_x, pos_y, name.data());
}

c1CutsceneEntity::~c1CutsceneEntity()
{
	App->entity_manager->DeleteEntity(entity);
}

e1Entity * c1CutsceneEntity::GetEntity()
{
	return entity;
}
