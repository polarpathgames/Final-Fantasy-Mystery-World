#include "j1App.h"
#include "DynamicEntity.h"
#include "j1EntityManager.h"
#include "j1Render.h"
#include "j1Scene.h"
#include "Enemy.h"
#include "Player.h"
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
		
		bool player_turn = false;
		while (item != entities.rend()) {
			if ((*item) != nullptr && (*item)->type == Entity::EntityType::ENEMY) {
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
			case AnimationState::IDLE_LEFT:
				IdleLeft.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_RIGHT:
				IdleRight.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_UP:
				IdleUp.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_DOWN:
				IdleDown.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_UP_LEFT:
				IdleUpLeft.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_DOWN_LEFT:
				IdleDownLeft.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_UP_RIGHT:
				IdleUpRight.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::IDLE_DOWN_RIGHT:
				IdleDownRight.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_LEFT:
				GoLeft.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_RIGHT:
				GoRight.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_UP:
				GoUp.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_DOWN:
				GoDown.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_UP_RIGHT:
				GoUpRight.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_DOWN_RIGHT:
				GoDownRight.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_UP_LEFT:
				GoUpLeft.PushBack(data.animations[i].frames[j]);
				break;
			case AnimationState::WALKING_DOWN_LEFT:
				GoDownLeft.PushBack(data.animations[i].frames[j]);
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

void DynamicEntity::RestTimeAfterAttack(float time_finish)
{
	if (time_attack <= SDL_GetTicks() - time_after_attack) {
		ChangeTurn(type);
		state = State::IDLE;
	}
}

void DynamicEntity::CheckAttackEfects(const Entity::EntityType & type, const Direction & direction, const int & attack_damage)
{
	std::vector<Entity*> entities = App->entity_manager->GetEntities();
	std::vector<Entity*>::iterator item = entities.begin();
	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == type) {
			iPoint origin = actual_tile;
			iPoint destination = (*item)->actual_tile;
			bool has_succeeded = false;
			switch (direction) {
			case Direction::DOWN_LEFT: {
				origin += {0, 1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::DOWN_RIGHT: {
				origin += {1, 0};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::DOWN: {
				origin += {1, 1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::UP: {
				origin += {-1, -1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::UP_LEFT: {
				origin += {-1, 0};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::UP_RIGHT: {
				origin += {0, -1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			case Direction::LEFT: {
				origin += {-1, 1};
				if (destination == origin) {
					has_succeeded = true; 
				}
			} break;
			case Direction::RIGHT: {
				origin += {1, -1};
				if (destination == origin) {
					has_succeeded = true;
				}
			} break;
			default:
				LOG("There is no valid direction to attack");
				break;
			}
			if (has_succeeded) {
				if (type == Entity::EntityType::ENEMY) {
					Enemy* enemy_attacked = (Enemy*)(*item);
					enemy_attacked->stats.live -= attack_damage;
					if (enemy_attacked->stats.live <= 0) {
						App->entity_manager->DeleteEntity((*item));
					}
				}
				else if (type == Entity::EntityType::PLAYER) {
					Player* player_attacked = (Player*)(*item);
					player_attacked->stats.live -= attack_damage;
					if (player_attacked->stats.live <= 0) {
						App->entity_manager->DeleteEntity((*item));
					}
				}
			}
		}
	}



}




