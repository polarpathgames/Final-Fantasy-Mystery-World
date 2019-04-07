#include "App.h"
#include "e1DynamicEntity.h"
#include "m1EntityManager.h"
#include "m1Render.h"
#include "m1Scene.h"
#include "e1Enemy.h"
#include "e1Player.h"
#include "m1Map.h"
#include "p2Log.h"
#include "m1EntityManager.h"
#include <list>

e1DynamicEntity::e1DynamicEntity(const int &x, const int &y) : e1Entity(x,y)
{

}

e1DynamicEntity::~e1DynamicEntity()
{

}



void e1DynamicEntity::ChangeTurn(EntityType type)
{
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	switch (type) {
	case EntityType::PLAYER: {
		
		std::vector<e1Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
				(*item)->has_turn = true;
				has_turn = false;
			}
				
		}
		break; }
	case EntityType::ENEMY: {
		has_turn = false;
		std::vector<e1Entity*>::reverse_iterator item = entities.rbegin();
		
		bool player_turn = false;
		while (item != entities.rend()) {
			if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
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
void e1DynamicEntity::PushBack()
{
	for (uint i = 0; i < data.num_animations; ++i) {
		for (uint j = 0; j < data.animations[i].num_frames; ++j) {
			switch (data.animations[i].animType) {
			case AnimationState::IDLE_LEFT:
				IdleLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_RIGHT:
				IdleRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_UP:
				IdleUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleUp.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_DOWN:
				IdleDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleDown.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_UP_LEFT:
				IdleUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleUpLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_DOWN_LEFT:
				IdleDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleDownLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_UP_RIGHT:
				IdleUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleUpRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_DOWN_RIGHT:
				IdleDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					IdleDownRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_LEFT:
				GoLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_RIGHT:
				GoRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_UP:
				GoUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoUp.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_DOWN:
				GoDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoDown.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_UP_RIGHT:
				GoUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoUpRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_DOWN_RIGHT:
				GoDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoDownRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_UP_LEFT:
				GoUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoUpLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_DOWN_LEFT:
				GoDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					GoDownLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::BASIC_ATTACK_DOWN_LEFT:
				BasicAttackDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackDownLeft.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_UP_RIGHT:
				BasicAttackUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackUpRight.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_DOWN:
				BasicAttackDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackDown.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_DOWN_RIGHT:
				BasicAttackDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackDownRight.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_LEFT:
				BasicAttackLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackLeft.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_RIGHT:
				BasicAttackRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackRight.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_UP:
				BasicAttackUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackUp.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_UP_LEFT:
				BasicAttackUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					BasicAttackUpLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::DEATH_UP_LEFT:
				DeathUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathUpLeft.speed = data.animations[i].speed;
					DeathUpLeft.loop = false;
				}
				break;
			case AnimationState::DEATH_UP:
				DeathUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathUp.speed = data.animations[i].speed;
					DeathUp.loop = false;
				}
				break;
			case AnimationState::DEATH_LEFT:
				DeathLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathLeft.speed = data.animations[i].speed;
					DeathLeft.loop = false;
				}
				break;
			case AnimationState::DEATH_UP_RIGHT:
				DeathUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathUpRight.speed = data.animations[i].speed;
					DeathUpRight.loop = false;
				}
				break;
			case AnimationState::DEATH_DOWN_RIGHT:
				DeathDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathDownRight.speed = data.animations[i].speed;
					DeathDownRight.loop = false;
				}
				break;
			case AnimationState::DEATH_RIGHT:
				DeathRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathRight.speed = data.animations[i].speed;
					DeathRight.loop = false;
				}
				break;
			case AnimationState::DEATH_DOWN:
				DeathDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathDown.speed = data.animations[i].speed;
					DeathDown.loop = false;
				}
				break;
			case AnimationState::DEATH_DOWN_LEFT:
				DeathDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					DeathDownLeft.speed = data.animations[i].speed;
					DeathDownLeft.loop = false;
				}
				break;
			default:
				break;
			}
		}
	}
}

bool e1DynamicEntity::NextTileFree(const Direction & dir) const
{
	bool ret = true;
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type != e1Entity::EntityType::SENSOR) {
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

void e1DynamicEntity::RestTimeAfterAttack(float time_finish)
{
	if (time_attack <= SDL_GetTicks() - time_after_attack) {
		ChangeTurn(type);
		state = State::IDLE;
		ChangeAnimation(direction, state);
		ResetAnims();
	}
	else {
		if (target_position == position)
			ChangeAnimation(direction, state);
		else {
			switch (direction)
			{
			case Direction::DOWN:
				current_animation = &GoDown;
				break;
			case Direction::DOWN_LEFT:
				current_animation = &GoDownLeft;
				break;
			case Direction::DOWN_RIGHT:
				current_animation = &GoDownRight;
				break;
			case Direction::LEFT:
				current_animation = &GoLeft;
				break;
			case Direction::RIGHT:
				current_animation = &GoRight;
				break;
			case Direction::UP:
				current_animation = &GoUp;
				break;
			case Direction::UP_LEFT:
				current_animation = &GoUpLeft;
				break;
			case Direction::UP_RIGHT:
				current_animation = &GoUpRight;
				break;
			default:
				break;
			}
		}
			
	}
}

void e1DynamicEntity::CheckBasicAttackEfects(const e1Entity::EntityType & type, const Direction & direction, const int & attack_damage)
{
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();
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
				if (type == e1Entity::EntityType::ENEMY) {
					e1Enemy* enemy_attacked = (e1Enemy*)(*item);
					enemy_attacked->GetHitted(attack_damage);
				}
				else if (type == e1Entity::EntityType::PLAYER) {
					e1Player* player_attacked = (e1Player*)(*item);
					player_attacked->GetHitted(attack_damage);
				}
			}
		}
	}
}

void e1DynamicEntity::ChangeAnimation(Direction &dir, State &states, Attacks attacks)
{
	switch (states) {
	case State::AFTER_ATTACK: {
		switch (dir) {
		case Direction::DOWN:
			current_animation = &IdleDown;
			break;
		case Direction::UP:
			current_animation = &IdleUp;
			break;
		case Direction::RIGHT:
			current_animation = &IdleRight;
			break;
		case Direction::LEFT:
			current_animation = &IdleLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &IdleUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &IdleDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &IdleDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &IdleUpLeft;
			break;
		default:
			LOG("No direction type found");
			break;
		}
	} break;
	case State::IDLE: {
		switch (dir) {
		case Direction::DOWN:
			current_animation = &IdleDown;
			break;
		case Direction::UP:
			current_animation = &IdleUp;
			break;
		case Direction::RIGHT:
			current_animation = &IdleRight;
			break;
		case Direction::LEFT:
			current_animation = &IdleLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &IdleUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &IdleDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &IdleDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &IdleUpLeft;
			break;
		default:
			LOG("No direction type found");
			break;
		}
	} break;
	case State::ATTACKING: {
		switch (dir) {
		case Direction::DOWN: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackDown;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		}break;
		case Direction::UP: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackUp;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::RIGHT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackRight;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::LEFT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackLeft;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::UP_RIGHT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackUpRight;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::DOWN_RIGHT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackDownRight;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::DOWN_LEFT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackDownLeft;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::UP_LEFT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &BasicAttackUpLeft;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		default:
			LOG("No direction type found");
			break;
		}
	} break;
	case State::DEATH: {
		switch (dir) {
		case Direction::DOWN:
			current_animation = &DeathDown;
			break;
		case Direction::UP:
			current_animation = &DeathUp;
			break;
		case Direction::RIGHT:
			current_animation = &DeathRight;
			break;
		case Direction::LEFT:
			current_animation = &DeathLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &DeathUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &DeathDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &DeathDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &DeathUpLeft;
			break;
		default:
			LOG("No direction type found");
			break;
		}
	} break;
	default:
		LOG("No state type found");
		break;
	}




}

void e1DynamicEntity::ResetAnims()
{
	BasicAttackDownLeft.Reset();
	BasicAttackDown.Reset();
	BasicAttackDownRight.Reset();
	BasicAttackLeft.Reset();
	BasicAttackRight.Reset();
	BasicAttackUp.Reset();
	BasicAttackUpLeft.Reset();
	BasicAttackUpRight.Reset();
	
	
}




