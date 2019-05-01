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
#include "Brofiler/Brofiler.h"
#include <list>

e1DynamicEntity::e1DynamicEntity(const int &x, const int &y) : e1Entity(x,y)
{

}

e1DynamicEntity::~e1DynamicEntity()
{

}

void e1DynamicEntity::ChangeTurn(EntityType type)
{
	BROFILER_CATEGORY("ChangeTurn", Profiler::Color::Yellow);

	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	switch (type) {
	case EntityType::PLAYER: {
		
		std::vector<e1Entity*>::iterator item = entities.begin();
		for (; item != entities.end(); ++item) {
			if ((*item) != nullptr && (*item)->type == EntityType::ENEMY && !(*item)->turn_done) {
				(*item)->has_turn = true;
				has_turn = false;
				(*item)->turn_done = true;
				break;
			}
				
		}
		break; }
	case EntityType::ENEMY: {
		has_turn = false;
		std::vector<e1Entity*>::iterator item = entities.begin();
		bool more_enemies = false;
		while (item != entities.end()) {
			if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY && !(*item)->turn_done) {
				(*item)->has_turn = true;
				(*item)->turn_done = true;
				more_enemies = true;
				break;
			}
			++item;
		}
		if (!more_enemies) {
			item = entities.begin();
			for (; item != entities.end(); ++item) {
				if ((*item) != nullptr && (*item)->type == EntityType::ENEMY) {
					(*item)->has_turn = false;
					(*item)->turn_done = false;
				}	
				if ((*item) != nullptr && (*item)->type == EntityType::PLAYER) {
					(*item)->has_turn = true;
				}
					
			}
		}
		break;  }
	default:
		break;
	}

}
void e1DynamicEntity::PushBack()
{
	BROFILER_CATEGORY("DynamicEntity Pushback", Profiler::Color::Yellow);

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
			case AnimationState::ABILITY_DOWN_LEFT_1:
				AbilitiDownLeft1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiDownLeft1.speed = data.animations[i].speed;
					AbilitiDownLeft1.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_RIGHT_1:
				AbilitiDownRight1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiDownRight1.speed = data.animations[i].speed;
					AbilitiDownRight1.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_RIGHT_1:
				AbilitiUpRight1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiUpRight1.speed = data.animations[i].speed;
					AbilitiUpRight1.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_1:
				AbilitiUp1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiUp1.speed = data.animations[i].speed;
					AbilitiUp1.loop = false;
				}
				break;
			case AnimationState::ABILITY_LEFT_1:
				AbilitiLeft1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiLeft1.speed = data.animations[i].speed;
					AbilitiLeft1.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_1:
				AbilitiDown1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiDown1.speed = data.animations[i].speed;
					AbilitiDown1.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_LEFT_1:
				AbilitiUpLeft1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiUpLeft1.speed = data.animations[i].speed;
					AbilitiUpLeft1.loop = false;
				}
				break;
			case AnimationState::ABILITY_RIGHT_1:
				AbilitiRight1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiRight1.speed = data.animations[i].speed;
					AbilitiRight1.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_LEFT_2:
				AbilitiDownLeft2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiDownLeft2.speed = data.animations[i].speed;
					AbilitiDownLeft2.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_RIGHT_2:
				AbilitiDownRight2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiDownRight2.speed = data.animations[i].speed;
					AbilitiDownRight2.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_RIGHT_2:
				AbilitiUpRight2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiUpRight2.speed = data.animations[i].speed;
					AbilitiUpRight2.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_2:
				AbilitiUp2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiUp2.speed = data.animations[i].speed;
					AbilitiUp2.loop = false;
				}
				break;
			case AnimationState::ABILITY_LEFT_2:
				AbilitiLeft2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiLeft2.speed = data.animations[i].speed;
					AbilitiLeft2.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_2:
				AbilitiDown2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiDown2.speed = data.animations[i].speed;
					AbilitiDown2.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_LEFT_2:
				AbilitiUpLeft2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiUpLeft2.speed = data.animations[i].speed;
					AbilitiUpLeft2.loop = false;
				}
				break;
			case AnimationState::ABILITY_RIGHT_2:
				AbilitiRight2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					AbilitiRight2.speed = data.animations[i].speed;
					AbilitiRight2.loop = false;
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
	BROFILER_CATEGORY("NextTileFree DynamicEntity", Profiler::Color::Yellow);
	bool ret = true;
	std::vector<e1Entity*> entities = App->entity_manager->GetEntities();
	std::vector<e1Entity*>::iterator item = entities.begin();

	for (; item != entities.end(); ++item) {
		if ((*item) != nullptr && (*item)->type == e1Entity::EntityType::ENEMY) {
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

void e1DynamicEntity::CheckBasicAttackEffects(const e1Entity::EntityType & type, const Direction & direction, const int & attack_damage)
{
	BROFILER_CATEGORY("DynamicEntity CheckBasicAttackEffects", Profiler::Color::Yellow);

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
					if (player_attacked->state != State::DEATH) {
						switch (this->direction) {
						case Direction::DOWN:
							player_attacked->current_animation = &player_attacked->IdleUp;
							player_attacked->direction = Direction::UP;
							break;
						case Direction::UP:
							player_attacked->current_animation = &player_attacked->IdleDown;
							player_attacked->direction = Direction::DOWN;
							break;
						case Direction::LEFT:
							player_attacked->current_animation = &player_attacked->IdleRight;
							player_attacked->direction = Direction::RIGHT;
							break;
						case Direction::RIGHT:
							player_attacked->current_animation = &player_attacked->IdleLeft;
							player_attacked->direction = Direction::LEFT;
							break;
						case Direction::UP_RIGHT:
							player_attacked->current_animation = &player_attacked->IdleDownLeft;
							player_attacked->direction = Direction::DOWN_LEFT;
							break;
						case Direction::DOWN_LEFT:
							player_attacked->current_animation = &player_attacked->IdleUpRight;
							player_attacked->direction = Direction::UP_RIGHT;
							break;
						case Direction::DOWN_RIGHT:
							player_attacked->current_animation = &player_attacked->IdleUpLeft;
							player_attacked->direction = Direction::UP_LEFT;
							break;
						case Direction::UP_LEFT:
							player_attacked->current_animation = &player_attacked->IdleDownRight;
							player_attacked->direction = Direction::DOWN_RIGHT;
							break;
						default:
							break;
						}
					}
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiDown1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiDown2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiUp1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiUp2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiRight1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiRight2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiLeft1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiLeft2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiUpRight1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiUpRight2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiDownRight1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiDownRight2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiDownLeft1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiDownLeft2;
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
			case Attacks::SPECIAL_1:
				current_animation = &AbilitiUpLeft1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &AbilitiUpLeft2;
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
	AbilitiDownLeft1.Reset();
	AbilitiDownRight1.Reset();
	AbilitiUpLeft1.Reset();
	AbilitiUpRight1.Reset();
	AbilitiLeft1.Reset();
	AbilitiDown1.Reset();
	AbilitiUp1.Reset();
	AbilitiRight1.Reset();
	AbilitiDownLeft2.Reset();
	AbilitiDownRight2.Reset();
	AbilitiUpLeft2.Reset();
	AbilitiUpRight2.Reset();
	AbilitiLeft2.Reset();
	AbilitiDown2.Reset();
	AbilitiUp2.Reset();
	AbilitiRight2.Reset();
	
}

void e1DynamicEntity::ChangeAnimsInCutscene(const int & x, const int & y, const int & anim_num, int & pos_x, int & pos_y)
{
	Animation* last_anim;
	last_anim = current_animation;

	if (anim_num == 1) {
		if (x != 0 && y != 0) {
			if (x > 0 && y > 0) {
				current_animation = &GoDownRight;
			}
			else if (x == -40 && y == -80) {
				current_animation = &GoUp;
			}
			else if (x < 0 && y < 0) {
				current_animation = &GoUpLeft;
			}
			else if (x > 0 && y < 0) {
				current_animation = &GoUpRight;
			}
			else if (x < 0 && y > 0) {
				current_animation = &GoDownLeft;
			}
		}
		if (x == 0 && y == 0) {
			if (last_anim == &GoDownRight) {
				current_animation = &IdleDownRight;
			}
			else if (last_anim == &GoUpLeft) {
				current_animation = &IdleUpLeft;
			}
			else if (last_anim == &GoUpRight) {
				current_animation = &IdleUpRight;
			}
			else if (last_anim == &GoDownLeft) {
				current_animation = &IdleDownLeft;
			}
		}
		
	}
	if (anim_num == 2) {
		if (x > 0 && y > 0) {
			current_animation = &IdleDownRight;
		}
		else if (x < 0 && y < 0) {
			current_animation = &IdleUpLeft;
		}
		else if (x > 0 && y < 0) {
			current_animation = &IdleUpRight;
		}
		else if (x < 0 && y > 0) {
			current_animation = &IdleDownLeft;
		}
	}
}