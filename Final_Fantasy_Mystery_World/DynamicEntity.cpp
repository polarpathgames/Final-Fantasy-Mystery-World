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



void DynamicEntity::ChangeTurn(EntityType type)
{
	std::vector<Entity*> entities = App->entity_manager->GetEntities();
	switch (type) {
	case EntityType::PLAYER: {
		has_turn = false;
		std::vector<Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
				(*item)->has_turn = true;
			}
				
		}
		break; }
	case EntityType::ENEMY: {
		has_turn = false;
		std::vector<Entity*>::reverse_iterator item = entities.rbegin();
		
		bool player_turn = false;
		while (item != entities.rend()) {
			if ((*item)->type == Entity::EntityType::ENEMY) {
				if ((*item) != this) {
					break;
				}
				else {
					player_turn = true;
					break;
				}
			}
			++item;
		}
		if (player_turn) {
			item = entities.rbegin();
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

bool DynamicEntity::NextTileFree(const Direction & dir) const
{
	bool ret = true;
	std::vector<Entity*> entities = App->entity_manager->GetEntities();
	std::vector<Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type != Entity::EntityType::SENSOR) {
			iPoint origin = actual_tile;
			iPoint destination = (*item)->actual_tile;

			switch (dir) {
			case Direction::DOWN:
				origin += {1, 1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::UP:
				origin += {-1, -1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::LEFT:
				origin += {-1, 1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::RIGHT:
				origin += {1, -1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::DOWN_LEFT:
				origin += {0, 1};
				if (destination == origin)
					ret = false;
				break;
			case Direction::DOWN_RIGHT:
				origin += {1, 0};
				if (destination == origin)
					ret = false;
				break;
			case Direction::UP_LEFT:
				origin += {-1, 0};
				if (destination == origin)
					ret = false;
				break;
			case Direction::UP_RIGHT:
				origin += {0, -1};
				if (destination == origin)
					ret = false;
				break;
			}
		}
	}

	return ret;
}




