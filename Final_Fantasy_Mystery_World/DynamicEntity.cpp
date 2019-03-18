#include "j1App.h"
#include "DynamicEntity.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include <list>

DynamicEntity::DynamicEntity(const int &x, const int &y) : Entity(x,y)
{

}

DynamicEntity::~DynamicEntity()
{

}

bool DynamicEntity::Update(float dt)
{



	return true;
}

void DynamicEntity::ChangeTurn(EntityType type)
{
	std::vector<Entity*> entities = App->entity_manager->GetEntities();
	switch (type) {
	case EntityType::PLAYER: {

		std::vector<Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
				(*item)->has_turn = true;
				has_turn = false;
			}
				
		}
		break; }
	case EntityType::ENEMY: {
		has_turn = false;
		std::vector<Entity*>::reverse_iterator item = entities.rbegin();
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
void DynamicEntity::PushBack()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		for (uint j = 0; j < data.animations[i].num_frames; ++j) {
			switch (data.animations[i].animType) {
			case State::IDLE:
				IdleLeft.PushBack(data.animations[i].frames[j]);
				break;
			case State::WALKING:
				GoLeft.PushBack(data.animations[i].frames[j]);
				break;
			default:
				break;
			}
		}
	}
}






