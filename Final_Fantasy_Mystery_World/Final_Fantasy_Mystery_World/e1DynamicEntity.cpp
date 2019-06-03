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
	allow_turn = true;
}

e1DynamicEntity::~e1DynamicEntity()
{

}

void e1DynamicEntity::PushBack()
{
	BROFILER_CATEGORY("DynamicEntity Pushback", Profiler::Color::Yellow);

	for (uint i = 0; i < data.num_animations; ++i) {
		for (uint j = 0; j < data.animations[i].num_frames; ++j) {
			switch (data.animations[i].animType) {
			case AnimationState::IDLE_LEFT:
				anim.IdleLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_RIGHT:
				anim.IdleRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_UP:
				anim.IdleUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleUp.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_DOWN:
				anim.IdleDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleDown.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_UP_LEFT:
				anim.IdleUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleUpLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_DOWN_LEFT:
				anim.IdleDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleDownLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_UP_RIGHT:
				anim.IdleUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleUpRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::IDLE_DOWN_RIGHT:
				anim.IdleDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.IdleDownRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_LEFT:
				anim.GoLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_RIGHT:
				anim.GoRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_UP:
				anim.GoUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoUp.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_DOWN:
				anim.GoDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoDown.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_UP_RIGHT:
				anim.GoUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoUpRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_DOWN_RIGHT:
				anim.GoDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoDownRight.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_UP_LEFT:
				anim.GoUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoUpLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::WALKING_DOWN_LEFT:
				anim.GoDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.GoDownLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::BASIC_ATTACK_DOWN_LEFT:
				anim.BasicAttackDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackDownLeft.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_UP_RIGHT:
				anim.BasicAttackUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackUpRight.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_DOWN:
				anim.BasicAttackDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackDown.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_DOWN_RIGHT:
				anim.BasicAttackDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackDownRight.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_LEFT:
				anim.BasicAttackLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackLeft.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_RIGHT:
				anim.BasicAttackRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackRight.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_UP:
				anim.BasicAttackUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackUp.speed = data.animations[i].speed;;
				}
				break;
			case AnimationState::BASIC_ATTACK_UP_LEFT:
				anim.BasicAttackUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.BasicAttackUpLeft.speed = data.animations[i].speed;
				}
				break;
			case AnimationState::DEATH_UP_LEFT:
				anim.DeathUpLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathUpLeft.speed = data.animations[i].speed;
					anim.DeathUpLeft.loop = false;
				}
				break;
			case AnimationState::DEATH_UP:
				anim.DeathUp.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathUp.speed = data.animations[i].speed;
					anim.DeathUp.loop = false;
				}
				break;
			case AnimationState::DEATH_LEFT:
				anim.DeathLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathLeft.speed = data.animations[i].speed;
					anim.DeathLeft.loop = false;
				}
				break;
			case AnimationState::DEATH_UP_RIGHT:
				anim.DeathUpRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathUpRight.speed = data.animations[i].speed;
					anim.DeathUpRight.loop = false;
				}
				break;
			case AnimationState::DEATH_DOWN_RIGHT:
				anim.DeathDownRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathDownRight.speed = data.animations[i].speed;
					anim.DeathDownRight.loop = false;
				}
				break;
			case AnimationState::DEATH_RIGHT:
				anim.DeathRight.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathRight.speed = data.animations[i].speed;
					anim.DeathRight.loop = false;
				}
				break;
			case AnimationState::DEATH_DOWN:
				anim.DeathDown.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathDown.speed = data.animations[i].speed;
					anim.DeathDown.loop = false;
				}
				break;
			case AnimationState::DEATH_DOWN_LEFT:
				anim.DeathDownLeft.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.DeathDownLeft.speed = data.animations[i].speed;
					anim.DeathDownLeft.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_LEFT_1:
				anim.AbilityDownLeft1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityDownLeft1.speed = data.animations[i].speed;
					anim.AbilityDownLeft1.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_RIGHT_1:
				anim.AbilityDownRight1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityDownRight1.speed = data.animations[i].speed;
					anim.AbilityDownRight1.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_RIGHT_1:
				anim.AbilityUpRight1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityUpRight1.speed = data.animations[i].speed;
					anim.AbilityUpRight1.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_1:
				anim.AbilityUp1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityUp1.speed = data.animations[i].speed;
					anim.AbilityUp1.loop = false;
				}
				break;
			case AnimationState::ABILITY_LEFT_1:
				anim.AbilityLeft1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityLeft1.speed = data.animations[i].speed;
					anim.AbilityLeft1.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_1:
				anim.AbilityDown1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityDown1.speed = data.animations[i].speed;
					anim.AbilityDown1.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_LEFT_1:
				anim.AbilityUpLeft1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityUpLeft1.speed = data.animations[i].speed;
					anim.AbilityUpLeft1.loop = false;
				}
				break;
			case AnimationState::ABILITY_RIGHT_1:
				anim.AbilityRight1.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityRight1.speed = data.animations[i].speed;
					anim.AbilityRight1.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_LEFT_2:
				anim.AbilityDownLeft2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityDownLeft2.speed = data.animations[i].speed;
					anim.AbilityDownLeft2.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_RIGHT_2:
				anim.AbilityDownRight2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityDownRight2.speed = data.animations[i].speed;
					anim.AbilityDownRight2.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_RIGHT_2:
				anim.AbilityUpRight2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityUpRight2.speed = data.animations[i].speed;
					anim.AbilityUpRight2.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_2:
				anim.AbilityUp2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityUp2.speed = data.animations[i].speed;
					anim.AbilityUp2.loop = false;
				}
				break;
			case AnimationState::ABILITY_LEFT_2:
				anim.AbilityLeft2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityLeft2.speed = data.animations[i].speed;
					anim.AbilityLeft2.loop = false;
				}
				break;
			case AnimationState::ABILITY_DOWN_2:
				anim.AbilityDown2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityDown2.speed = data.animations[i].speed;
					anim.AbilityDown2.loop = false;
				}
				break;
			case AnimationState::ABILITY_UP_LEFT_2:
				anim.AbilityUpLeft2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityUpLeft2.speed = data.animations[i].speed;
					anim.AbilityUpLeft2.loop = false;
				}
				break;
			case AnimationState::ABILITY_RIGHT_2:
				anim.AbilityRight2.PushBack(data.animations[i].frames[j]);
				if (j == 0) {
					anim.AbilityRight2.speed = data.animations[i].speed;
					anim.AbilityRight2.loop = false;
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

bool e1DynamicEntity::RestTimeAfterAttack(float time_finish)
{
	bool ret = false;
	if (time_attack <= SDL_GetTicks() - time_after_attack) {
		turn_done = true;
		state = State::IDLE;
		ChangeAnimation(direction, state);
		ResetAnims();
		ret = true;
	}
	else {
		if (return_spline == nullptr || return_spline->to_delete) {
			ChangeAnimation(direction, state);
			return_spline = nullptr;
		}
		else {
			switch (direction)
			{
			case Direction::DOWN:
				current_animation = &anim.GoDown;
				break;
			case Direction::DOWN_LEFT:
				current_animation = &anim.GoDownLeft;
				break;
			case Direction::DOWN_RIGHT:
				current_animation = &anim.GoDownRight;
				break;
			case Direction::LEFT:
				current_animation = &anim.GoLeft;
				break;
			case Direction::RIGHT:
				current_animation = &anim.GoRight;
				break;
			case Direction::UP:
				current_animation = &anim.GoUp;
				break;
			case Direction::UP_LEFT:
				current_animation = &anim.GoUpLeft;
				break;
			case Direction::UP_RIGHT:
				current_animation = &anim.GoUpRight;
				break;
			default:
				break;
			}
		}
			
	}
	return ret;
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
							player_attacked->current_animation = &player_attacked->anim.IdleUp;
							player_attacked->direction = Direction::UP;
							break;
						case Direction::UP:
							player_attacked->current_animation = &player_attacked->anim.IdleDown;
							player_attacked->direction = Direction::DOWN;
							break;
						case Direction::LEFT:
							player_attacked->current_animation = &player_attacked->anim.IdleRight;
							player_attacked->direction = Direction::RIGHT;
							break;
						case Direction::RIGHT:
							player_attacked->current_animation = &player_attacked->anim.IdleLeft;
							player_attacked->direction = Direction::LEFT;
							break;
						case Direction::UP_RIGHT:
							player_attacked->current_animation = &player_attacked->anim.IdleDownLeft;
							player_attacked->direction = Direction::DOWN_LEFT;
							break;
						case Direction::DOWN_LEFT:
							player_attacked->current_animation = &player_attacked->anim.IdleUpRight;
							player_attacked->direction = Direction::UP_RIGHT;
							break;
						case Direction::DOWN_RIGHT:
							player_attacked->current_animation = &player_attacked->anim.IdleUpLeft;
							player_attacked->direction = Direction::UP_LEFT;
							break;
						case Direction::UP_LEFT:
							player_attacked->current_animation = &player_attacked->anim.IdleDownRight;
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

void e1DynamicEntity::ChangeAnimation(const Direction &dir, const State &states, Attacks attacks)
{
	switch (states) {
	case State::AFTER_ATTACK: {
		switch (dir) {
		case Direction::DOWN:
			current_animation = &anim.IdleDown;
			break;
		case Direction::UP:
			current_animation = &anim.IdleUp;
			break;
		case Direction::RIGHT:
			current_animation = &anim.IdleRight;
			break;
		case Direction::LEFT:
			current_animation = &anim.IdleLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &anim.IdleUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &anim.IdleDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &anim.IdleDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &anim.IdleUpLeft;
			break;
		default:
			LOG("No direction type found");
			break;
		}
	} break;
	case State::IDLE: {
		switch (dir) {
		case Direction::DOWN:
			current_animation = &anim.IdleDown;
			break;
		case Direction::UP:
			current_animation = &anim.IdleUp;
			break;
		case Direction::RIGHT:
			current_animation = &anim.IdleRight;
			break;
		case Direction::LEFT:
			current_animation = &anim.IdleLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &anim.IdleUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &anim.IdleDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &anim.IdleDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &anim.IdleUpLeft;
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
				current_animation = &anim.BasicAttackDown;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityDown1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityDown2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		}break;
		case Direction::UP: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackUp;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityUp1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityUp2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::RIGHT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackRight;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityRight1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityRight2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::LEFT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackLeft;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityLeft1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityLeft2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::UP_RIGHT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackUpRight;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityUpRight1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityUpRight2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::DOWN_RIGHT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackDownRight;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityDownRight1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityDownRight2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::DOWN_LEFT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackDownLeft;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityDownLeft1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityDownLeft2;
				break;
			default:
				LOG("No attack type found");
				break;
			}
		} break;
		case Direction::UP_LEFT: {
			switch (attacks) {
			case Attacks::BASIC:
				current_animation = &anim.BasicAttackUpLeft;
				break;
			case Attacks::SPECIAL_1:
				current_animation = &anim.AbilityUpLeft1;
				break;
			case Attacks::SPECIAL_2:
				current_animation = &anim.AbilityUpLeft2;
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
			current_animation = &anim.DeathDown;
			break;
		case Direction::UP:
			current_animation = &anim.DeathUp;
			break;
		case Direction::RIGHT:
			current_animation = &anim.DeathRight;
			break;
		case Direction::LEFT:
			current_animation = &anim.DeathLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &anim.DeathUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &anim.DeathDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &anim.DeathDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &anim.DeathUpLeft;
			break;
		default:
			LOG("No direction type found");
			break;
		}
	} break;
	case State::WALKING:
		switch (dir) {
		case Direction::DOWN:
			current_animation = &anim.GoDown;
			break;
		case Direction::UP:
			current_animation = &anim.GoUp;
			break;
		case Direction::RIGHT:
			current_animation = &anim.GoRight;
			break;
		case Direction::LEFT:
			current_animation = &anim.GoLeft;
			break;
		case Direction::UP_RIGHT:
			current_animation = &anim.GoUpRight;
			break;
		case Direction::DOWN_RIGHT:
			current_animation = &anim.GoDownRight;
			break;
		case Direction::DOWN_LEFT:
			current_animation = &anim.GoDownLeft;
			break;
		case Direction::UP_LEFT:
			current_animation = &anim.GoUpLeft;
			break;
		default:
			LOG("No direction type found");
			break;
		}
		break;
	default:
		LOG("No state type found");
		break;
	}




}

void e1DynamicEntity::ResetAnims()
{
	anim.BasicAttackDownLeft.Reset();
	anim.BasicAttackDown.Reset();
	anim.BasicAttackDownRight.Reset();
	anim.BasicAttackLeft.Reset();
	anim.BasicAttackRight.Reset();
	anim.BasicAttackUp.Reset();
	anim.BasicAttackUpLeft.Reset();
	anim.BasicAttackUpRight.Reset();
	anim.AbilityDownLeft1.Reset();
	anim.AbilityDownRight1.Reset();
	anim.AbilityUpLeft1.Reset();
	anim.AbilityUpRight1.Reset();
	anim.AbilityLeft1.Reset();
	anim.AbilityDown1.Reset();
	anim.AbilityUp1.Reset();
	anim.AbilityRight1.Reset();
	anim.AbilityDownLeft2.Reset();
	anim.AbilityDownRight2.Reset();
	anim.AbilityUpLeft2.Reset();
	anim.AbilityUpRight2.Reset();
	anim.AbilityLeft2.Reset();
	anim.AbilityDown2.Reset();
	anim.AbilityUp2.Reset();
	anim.AbilityRight2.Reset();
	
}

Animation* e1DynamicEntity::GetAnim(const AnimationState& anim_id) {
	switch (anim_id)
	{
	case AnimationState::IDLE_UP:
		return &anim.IdleUp;
		break;
	case AnimationState::IDLE_UP_LEFT:
		return &anim.IdleUpLeft;
		break;
	case AnimationState::IDLE_UP_RIGHT:
		return &anim.IdleUpRight;
		break;
	case AnimationState::IDLE_LEFT:
		return &anim.IdleLeft;
		break;
	case AnimationState::IDLE_DOWN_LEFT:
		return &anim.IdleDownLeft;
		break;
	case AnimationState::IDLE_DOWN:
		return &anim.IdleDown;
		break;
	case AnimationState::IDLE_DOWN_RIGHT:
		return &anim.IdleDownRight;
		break;
	case AnimationState::IDLE_RIGHT:
		return &anim.IdleRight;
		break;
	case AnimationState::WALKING_UP:
		return &anim.GoUp;
		break;
	case AnimationState::WALKING_UP_LEFT:
		return &anim.GoUpLeft;
		break;
	case AnimationState::WALKING_UP_RIGHT:
		return &anim.GoUpRight;
		break;
	case AnimationState::WALKING_LEFT:
		return &anim.GoLeft;
		break;
	case AnimationState::WALKING_DOWN_LEFT:
		return &anim.GoDownLeft;
		break;
	case AnimationState::WALKING_DOWN:
		return &anim.GoDown;
		break;
	case AnimationState::WALKING_DOWN_RIGHT:
		return &anim.GoDownRight;
		break;
	case AnimationState::WALKING_RIGHT:
		return &anim.GoRight;
		break;
	case AnimationState::BASIC_ATTACK_UP:
		return &anim.BasicAttackUp;
		break;
	case AnimationState::BASIC_ATTACK_UP_LEFT:
		return &anim.BasicAttackUpLeft;
		break;
	case AnimationState::BASIC_ATTACK_UP_RIGHT:
		return &anim.BasicAttackUpRight;
		break;
	case AnimationState::BASIC_ATTACK_LEFT:
		return &anim.BasicAttackLeft;
		break;
	case AnimationState::BASIC_ATTACK_DOWN_LEFT:
		return &anim.BasicAttackDownLeft;
		break;
	case AnimationState::BASIC_ATTACK_DOWN:
		return &anim.BasicAttackDown;
		break;
	case AnimationState::BASIC_ATTACK_DOWN_RIGHT:
		return &anim.BasicAttackDownRight;
		break;
	case AnimationState::BASIC_ATTACK_RIGHT:
		return &anim.BasicAttackRight;
		break;
	case AnimationState::DEATH_UP:
		return &anim.DeathUp;
		break;
	case AnimationState::DEATH_UP_LEFT:
		return &anim.DeathUpLeft;
		break;
	case AnimationState::DEATH_UP_RIGHT:
		return &anim.DeathUpRight;
		break;
	case AnimationState::DEATH_LEFT:
		return &anim.DeathLeft;
		break;
	case AnimationState::DEATH_DOWN_LEFT:
		return &anim.DeathDownLeft;
		break;
	case AnimationState::DEATH_DOWN:
		return &anim.DeathDown;
		break;
	case AnimationState::DEATH_DOWN_RIGHT:
		return &anim.DeathDownRight;
		break;
	case AnimationState::DEATH_RIGHT:
		return &anim.DeathRight;
		break;
	case AnimationState::ABILITY_UP_1:
		return &anim.AbilityUp1;
		break;
	case AnimationState::ABILITY_UP_LEFT_1:
		return &anim.AbilityUpLeft1;
		break;
	case AnimationState::ABILITY_UP_RIGHT_1:
		return &anim.AbilityUpRight1;
		break;
	case AnimationState::ABILITY_LEFT_1:
		return &anim.AbilityLeft1;
		break;
	case AnimationState::ABILITY_DOWN_LEFT_1:
		return &anim.AbilityDownLeft1;
		break;
	case AnimationState::ABILITY_DOWN_1:
		return &anim.AbilityDown1;
		break;
	case AnimationState::ABILITY_DOWN_RIGHT_1:
		return &anim.AbilityDownRight1;
		break;
	case AnimationState::ABILITY_RIGHT_1:
		return &anim.AbilityRight1;
		break;
	case AnimationState::ABILITY_UP_2:
		return &anim.AbilityUp2;
		break;
	case AnimationState::ABILITY_UP_LEFT_2:
		return &anim.AbilityUpLeft2;
		break;
	case AnimationState::ABILITY_UP_RIGHT_2:
		return &anim.AbilityUpRight2;
		break;
	case AnimationState::ABILITY_LEFT_2:
		return &anim.AbilityLeft2;
		break;
	case AnimationState::ABILITY_DOWN_LEFT_2:
		return &anim.AbilityDownLeft2;
		break;
	case AnimationState::ABILITY_DOWN_2:
		return &anim.AbilityDown2;
		break;
	case AnimationState::ABILITY_DOWN_RIGHT_2:
		return &anim.AbilityDownRight2;
		break;
	case AnimationState::ABILITY_RIGHT_2:
		return &anim.AbilityRight2;
		break;
	default:
		LOG("Any animation with id %i found", anim_id);
		break;
	}
	return nullptr;
}

void e1DynamicEntity::ChangeAnimsInCutscene(const int & x, const int & y, const int & anim_num, int & pos_x, int & pos_y)
{
	Animation* last_anim;
	last_anim = current_animation;

	if (anim_num == 1) {
		if (x != 0 && y != 0) {
			if (x > 0 && y > 0) {
				current_animation = &anim.GoDownRight;
			}
			else if (x == -40 && y == -80) {
				current_animation = &anim.GoUp;
			}
			else if (x < 0 && y < 0) {
				current_animation = &anim.GoUpLeft;
			}
			else if (x > 0 && y < 0) {
				current_animation = &anim.GoUpRight;
			}
			else if (x < 0 && y > 0) {
				current_animation = &anim.GoDownLeft;
			}
		}
		if (x == 0 && y == 0) {
			if (last_anim == &anim.GoDownRight) {
				current_animation = &anim.IdleDownRight;
			}
			else if (last_anim == &anim.GoUpLeft) {
				current_animation = &anim.IdleUpLeft;
			}
			else if (last_anim == &anim.GoUpRight) {
				current_animation = &anim.IdleUpRight;
			}
			else if (last_anim == &anim.GoDownLeft) {
				current_animation = &anim.IdleDownLeft;
			}
		}
		
	}
	if (anim_num == 2) {
		if (x > 0 && y > 0) {
			current_animation = &anim.IdleDownRight;
		}
		else if (x < 0 && y < 0) {
			current_animation = &anim.IdleUpLeft;
		}
		else if (x > 0 && y < 0) {
			current_animation = &anim.IdleUpRight;
		}
		else if (x < 0 && y > 0) {
			current_animation = &anim.IdleDownLeft;
		}
	}
}