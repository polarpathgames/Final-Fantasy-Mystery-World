#include "App.h"
#include "c1CutsceneEntity.h"
#include "m1EntityManager.h"
#include "e1DynamicEntity.h"
#include "e1StaticEntity.h"
#include "m1Cutscene.h"
#include "m1Scene.h"

c1CutsceneEntity::c1CutsceneEntity(int pos_x, int pos_y, std::string name)
{
	if (strcmp(name.data(), "player") == 0) {
		entity_c = (e1Entity*)App->scene->player;
	}
	else if (strcmp(name.data(), "daughter") == 0) {
		entity_c = App->entity_manager->CreateEntity(e1Entity::EntityType::DAUGHTER, pos_x, pos_y, name);		
	}
	else if (strcmp(name.data(), "Daughter") == 0) {
		std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
		std::vector<e1Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::NPC) {
				entity_c = (*item);
				break;
			}
		}
	}
	else if (strcmp(name.data(), "icequeen") == 0) {
		entity_c = App->entity_manager->CreateEntity(e1Entity::EntityType::FROZEN, pos_x, pos_y, name);
		entity_c->allow_turn = false;
		static_cast<e1DynamicEntity*>(entity_c)->state = State::SLEEPING;
	}
	else if (strcmp(name.data(), "ability_flash") == 0) {
		entity_c = App->entity_manager->CreateEntity(e1Entity::EntityType::STATIC, pos_x, pos_y, name);
		
	}
	else if (strcmp(name.data(), "NPC_DAUGHTER") == 0) {
		std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
		std::vector<e1Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && static_cast<e1StaticEntity*>(*item)->static_type == e1StaticEntity::Type::NPC_DAUGHTER) {
				entity_c = (*item);
				break;
			}
		}
	}
	App->cutscene_manager->ent = entity_c;
}

c1CutsceneEntity::~c1CutsceneEntity()
{	
	//entity_c->to_delete;
}

e1Entity * c1CutsceneEntity::GetEntity()
{
	return entity_c;
}
