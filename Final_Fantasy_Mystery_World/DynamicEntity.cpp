#include "j1App.h"
#include "DynamicEntity.h"
#include "EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "p2Log.h"
#include "EntityManager.h"
#include <list>

DynamicEntity::DynamicEntity() : Entity()
{

}

DynamicEntity::~DynamicEntity()
{

}

void DynamicEntity::ChangeTurn(EntityType type)
{
	std::list<Entity*> entities = App->entity_manager->GetEntities();
	switch (type) {
	case EntityType::PLAYER: {

		std::list<Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
				(*item)->has_turn = true;
				has_turn = false;
			}
				
		}
		break; }
	case EntityType::ENEMY: {
		has_turn = false;
		std::list<Entity*>::reverse_iterator item = entities.rbegin();
		if ((*item) == this) {
			for (; item != entities.rend(); ++item) {
				if ((*item) != nullptr && (*item)->type == EntityType::ENEMY)
					(*item)->has_turn = false;
				if ((*item) != nullptr && (*item)->type == EntityType::PLAYER)
					(*item)->has_turn = true;
			}
		}
		break;  }
	default:
		break;
	}

}







